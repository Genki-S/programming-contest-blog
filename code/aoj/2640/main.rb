# Header {{{
def assert(p)
  raise 'Assertion Failed' unless p
end

# Constants {{{
INF = 10**9
# }}}

# IO {{{
class MyIO
  def initialize
    @input = $stdin
    @output = $stdout
  end

  # @param filename [String]
  def set_input(filename)
    @input = File.open(filename, 'r')
  end

  def set_output(filename)
    @output = File.open(filename, 'w')
  end

  def int
    gets.to_i
  end

  def ints
    split.map(&:to_i)
  end

  def split
    @input.gets.chomp.split(' ')
  end
  alias_method :strings, :split

  def gets
    @input.gets.chomp
  end
  alias_method :string, :gets

  def puts(*args)
    @output.puts(*args)
  end
end

io = MyIO.new
# }}}

# Algorithms {{{

def lower_bound(arr, val)
  assert(arr.is_a?(Array))
  low, high = 0, arr.size
  while high - low > 1
    mid = (low + high) / 2
    if arr[mid] < val
      low = mid
    else
      high = mid
    end
  end
  if arr[low] >= val
    low
  else
    high
  end
end

def upper_bound(arr, val)
  assert(arr.is_a?(Array))
  low, high = 0, arr.size
  while high - low > 1
    mid = (low + high) / 2
    if arr[mid] <= val
      low = mid
    else
      high = mid
    end
  end
  if arr[low] > val
    low
  else
    high
  end
end

# }}}

# }}}

# io.set_input('inputs/3')

n, m = io.ints
field = Array.new(n)
n.times do |i|
  field[i] = io.string.split('')
  field[i] << '#'
  field[i].unshift '#'
end
field << Array.new(m+2, '#')
field.unshift Array.new(m+2, '#')

n += 2
m += 2
gy, gx, state = nil, nil, nil
n.times do |i|
  m.times do |j|
    if ['^', '>', 'v', '<'].include?(field[i][j])
      state = { y: i, x: j, dir: ['^', '>', 'v', '<'].index(field[i][j]), hand: :right, dist: 1 }
      field[i][j] = '.'
    end
    if field[i][j] == 'G'
      gy, gx = i, j
      field[i][j] = '.'
    end
  end
end

def rotate(dydx, dir)
  return dydx if dir == 0
  dy, dx = dydx
  dydx = [dx, dy * -1]
  rotate(dydx, dir-1)
end

dy = [-1, 0, 1, 0]
dx = [0, 1, 0, -1]
HAND_POSITIONS = [:front, :frontright, :right, :backright]
dydx_by_hand = { front: [-1, 0], frontright: [-1, 1], right: [0, 1], backright: [1, 1], dist: 1 }

@field = field
@memo = Array.new(n) { Array.new(m) { Array.new(4) { Hash.new(nil) } } }
@visit_count = Array.new(n) { Array.new(m, 0) }
@gy, @gx = gy, gx
@dy, @dx = dy, dx
@dydx_by_hand = dydx_by_hand
def dfs(y, x, d, hand, cells)
  # puts [y, x, d, hand, cells].to_s
  if y == @gy && x == @gx
    return cells + 1
  end
  return @memo[y][x][d][hand] if @memo[y][x][d][hand]

  cells += 1 if @visit_count[y][x] == 0
  @visit_count[y][x] += 1
  ret = 1e10

  # Move front
  if @field[y + @dy[d]][x + @dx[d]] == '.' && [:frontright, :right].include?(hand)
    ret = [ret, dfs(y+@dy[d], x+@dx[d], d, hand == :frontright ? :right : :backright, cells)].min
  end

  # Turn right
  if [:right, :backright].include?(hand)
    ret = [ret, dfs(y, x, (d+1)%4, hand == :right ? :front : :frontright, cells)].min
  end

  # Turn left
  if [:front, :frontright].include?(hand)
    ret = [ret, dfs(y, x, (d+4-1)%4, hand == :front ? :right : :backright, cells)].min
  end

  # Move hand
  HAND_POSITIONS.each do |next_hand|
    next if hand == next_hand
    _dy, _dx = rotate(@dydx_by_hand[next_hand], d)
    if hand == :backright && next_hand != :right
      rdy, rdx = rotate(@dydx_by_hand[:right], d)
      if @field[y + rdy][x + rdx] == '#' && @field[y + _dy][x + _dx] == '#'
        ret = [ret, dfs(y, x, d, next_hand, cells)].min
      end
    else
      if @field[y + _dy][x + _dx] == '#'
        ret = [ret, dfs(y, x, d, next_hand, cells)].min
      end
    end
  end

  @visit_count[y][x] -= 1
  @memo[y][x][d][hand] = ret
  ret
end

ans = dfs(state[:y], state[:x], state[:dir], state[:hand], 0)
if ans == 1e10
  puts -1
else
  puts ans
end

# vim: foldmethod=marker
