# Header {{{
require 'set'

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
      state = { y: i, x: j, dir: ['^', '>', 'v', '<'].index(field[i][j]), hand: :right, cells: Set.new([[i, j]]) }
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

class Heap
  def initialize(&comparator)
    @arr = []
    @comparator = comparator || lambda { |lhs, rhs| lhs < rhs }
  end

  def push(v)
    @arr << v
    last_i = @arr.size - 1
    @arr[0], @arr[last_i] = @arr[last_i], @arr[0]
    make_heap!
  end
  alias_method :<<, :push

  def pop
    if @arr.size == 1
      @arr.pop
    else
      ret = @arr.first
      @arr[0] = @arr.pop
      make_heap!
      ret
    end
  end

  def top
    @arr.first
  end

  def empty?
    @arr.empty?
  end

  private

  def make_heap!
    make_heap_at!(0)
  end

  def make_heap_at!(i)
    return unless @arr[i]
    l, r = left(i), right(i)
    if @arr[l] && !@comparator.call(@arr[i], @arr[l])
      @arr[i], @arr[l] = @arr[l], @arr[i]
      make_heap_at!(l)
    elsif @arr[r] && !@comparator.call(@arr[i], @arr[r])
      @arr[i], @arr[r] = @arr[r], @arr[i]
      make_heap_at!(r)
    end
  end

  def parent(i)
    (i - 1) / 2
  end

  def left(i)
    i * 2 + 1
  end

  def right(i)
    i * 2 + 2
  end
end

dy = [-1, 0, 1, 0]
dx = [0, 1, 0, -1]
HAND_POSITIONS = [:front, :frontright, :right, :backright]
dydx_by_hand = { front: [-1, 0], frontright: [-1, 1], right: [0, 1], backright: [1, 1] }
dp = Array.new(n) { Array.new(m) { Array.new(4) { Hash.new(nil) } } }
q = Heap.new { |rhs, lhs| rhs[:cells].size <=> lhs[:cells].size }
q.push(state)
while !q.empty?
  state = q.pop
  y, x, dir, hand, cells = state[:y], state[:x], state[:dir], state[:hand], state[:cells]
  next if dp[y][x][dir][hand]
  dp[y][x][dir][hand] = cells

  # Move front
  if field[y + dy[dir]][x + dx[dir]] == '.' && [:frontright, :right].include?(hand)
    q << { y: y + dy[dir], x: x + dx[dir], dir: dir, hand: hand == :frontright ? :right : :backright, cells: cells + Set.new([[y+dy[dir], x+dx[dir]]]) }
  end

  # Turn right
  if [:right, :backright].include?(hand)
    q << { y: y, x: x, dir: (dir + 1) % 4, hand: hand == :right ? :front : :frontright, cells: cells }
  end

  # Turn left
  if [:front, :frontright].include?(hand)
    q << { y: y, x: x, dir: (dir + 4 - 1) % 4, hand: hand == :front ? :right : :backright, cells: cells }
  end

  # Move hand
  HAND_POSITIONS.each do |next_hand|
    next if hand == next_hand
    _dy, _dx = rotate(dydx_by_hand[next_hand], dir)
    if (hand == :backright && next_hand != :right) || ([:front, :frontright].include?(hand) && next_hand == :backright)
      rdy, rdx = rotate(dydx_by_hand[:right], dir)
      if field[y + rdy][x + rdx] == '#' && field[y + _dy][x + _dx] == '#'
        q << { y: y, x: x, dir: dir, hand: next_hand, cells: cells }
      end
    else
      if field[y + _dy][x + _dx] == '#'
        q << { y: y, x: x, dir: dir, hand: next_hand, cells: cells }
      end
    end
  end
end

ans = nil
dp[gy][gx].each do |t|
  t.each do |k, v|
    ans ||= v.size
    ans = [ans, v.size].min
  end
end

puts ans ? ans : -1

# vim: foldmethod=marker
