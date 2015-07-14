require 'set'

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

class Heap
  def initialize
    @arr = []
  end

  def push(val)
    @arr << val
    @arr.first, @arr.last = @arr.last, @arr.first
    make_heap!
  end

  def top
    @arr.first
  end

  def pop
    ret = top
    @arr.first = @arr.pop
    make_heap!
    ret
  end

  private

  def make_heap!
    i = 0
    while i < @arr.size
      i = @arr.size # make it finish by default
      [left(i), right(i)].each do |j|
        if j < @arr.size && @arr[j] < @arr[i]
          @arr[i], @arr[j] = @arr[j], @arr[i]
          i = j
          break
        end
      end
    end
  end

  def left(i)
    i * 2 + 1
  end

  def right(i)
    i * 2 + 2
  end

  def parent(i)
    (i - 1) / 2
  end
end

class Data
  attr_reader :cost, :node

  def initialize(cost, node)
    @cost, @node = cost, node
  end

  def <(rhs)
    if @cost == rhs.cost
      @node < rhs.node
    else
      @cost < rhs.cost
    end
  end
end

io.set_input('inputs/1.txt')

n, m, s, t = io.ints
s -= 1
t -= 1
g = Array.new(n) { Array.new(n, false) }
m.times do
  x, y = io.ints
  g[x-1][y-1] = g[y-1][x-1] = true
end

paths = Array.new(n, 0)
cost = Array.new(n, INF)
visited = Array.new(n, false)
paths[s] = 1
cost[s] = 1
visited[s] = true
nodes = Set.new([s])
while !nodes.empty?
  nex = Set.new
  nodes.each do |i|
    visited[i] = true
    n.times do |j|
      next if i == j
      next unless g[i][j]
      next if visited[j]
      cost[j] = cost[i] + 1
      paths[j] += paths[i]
      nex << j
    end
  end
  nodes = nex
end

puts [0, cost[t] - 2].max * paths[t]

# vim: foldmethod=marker
