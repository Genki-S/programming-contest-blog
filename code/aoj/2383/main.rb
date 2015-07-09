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

  def intl
    splitl.map(&:to_i)
  end

  def splitl
    @input.gets.chomp.split(' ')
  end

  def gets
    @input.gets.chomp
  end

  def puts(*args)
    @output.puts(*args)
  end
end

io = MyIO.new
# }}}

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

io.set_input('inputs/4.txt')

MOD = 1_000_000_007

n, t = io.intl
levels = []
n.times do
  levels << io.gets.to_i
end
levels.sort!

ans = 1
1.upto(n-1) do |i|
  # insert levels[i] before one of levels[0...i]
  min_v = levels[i] - t
  lower, upper = lower_bound(levels[0...i], min_v), upper_bound(levels[0...i], min_v)
  ans = ans * (i - lower + 1) % MOD
end
puts ans

# vim: foldmethod=marker
