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

io.set_input('inputs/4.txt')

class Datum
  attr_reader :command, :skill, :cond, :thresh

  def initialize(comm, s, c, t)
    @command, @skill, @cond, @thresh = comm, s, c, t
  end

  def <=>(rhs)
    if @cond == rhs.cond
      if @thresh == rhs.thresh
        0
      else
        @thresh < rhs.thresh ? -1 : 1
      end
    else
      @cond == '>=' ? -1 : 1
    end
  end
end

data = []
m, n = io.ints
skills = Array.new(n, 0)
done = Array.new(m, false)

m.times do |i|
  k = io.int
  all_smaller = true
  k.times do
    s, c, t = io.strings
    s = s.to_i - 1
    t = t.to_i
    all_smaller = false unless c == '<='
    data << Datum.new(i, s, c, t)
  end
  done[i] = true if all_smaller
end
data.sort!

ok = true
data.size.times do |i|
  p skills
  comm = data[i].command
  break unless ok
  next if done[comm]
  done[comm] = true
  data.size.times do |j|
    d = data[j]
    next unless d.command == comm
    p d
    if d.cond == '>='
      if skills[d.skill] < d.thresh
        skills[d.skill] = d.thresh
      end
    else
      if skills[d.skill] > d.thresh
        ok = false and break
      end
    end
  end
end

puts ok ? 'Yes' : 'No'

# vim: foldmethod=marker
