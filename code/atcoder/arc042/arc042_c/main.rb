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

# Data Structures {{{

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

# io.set_input('inputs/0')

class Snack
  attr_accessor :price, :satisfaction
  def initialize(p, s)
    @price, @satisfaction = p, s
  end
end

n, p = io.ints
snacks = []
n.times do
  a, b = io.ints
  snacks << Snack.new(a, b)
end

snacks.sort_by!{ |s| s.price }.reverse!

dp = Array.new(n+1) { Array.new(p+110, 0) }
ans = 0
(1..n).each do |i|
  (0...p+110).each do |j|
    pp = j - snacks[i-1].price
    next if pp < 0
    dp[i][j] = [dp[i-1][j], dp[i-1][pp] + snacks[i-1].satisfaction].max
    if j - snacks[i-1].price <= p
      ans = [ans, dp[i][j]].max
    end
  end
end

puts ans

# vim: foldmethod=marker
