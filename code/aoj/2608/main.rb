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

# io.set_input('inputs/4.txt')

class Node
  attr_accessor :neighbors
  def initialize
    @neighbors = Set.new
  end

  def connect(n)
    @neighbors << n
  end
end

n, m, s, t = io.ints
s -= 1
t -= 1
nodes = Array.new(n) { Node.new }
m.times do
  x, y = io.ints
  x -= 1
  y -= 1
  nodes[x].connect(y)
  nodes[y].connect(x)
end

min_dist = INF
nodes_by_dist_from_start = Hash.new { |h, k| h[k] = Set.new }
nodes_by_dist_from_end = Hash.new { |h, k| h[k] = Set.new }
[s, t].each do |start|
  visited = Array.new(n, false)
  q = []
  q << [start, 0]
  while !q.empty?
    i, d = q.shift
    next if visited[i]
    visited[i] = true
    min_dist = d if start == s && i == t
    nodes_by_dist_from_start[d] << i if start == s
    nodes_by_dist_from_end[d] << i if start == t
    nodes[i].neighbors.each do |j|
      q.push([j, d+1])
    end
  end
end

ans = 0
(0...min_dist).each do |i|
  j = min_dist - i - 2
  ans += nodes_by_dist_from_start[i].size * nodes_by_dist_from_end[j].size
end

puts ans

# vim: foldmethod=marker
