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

# io.set_input('inputs/3.txt')

commands = []
m, n = io.ints

m.times do
  conditions = []
  k = io.int
  k.times do
    skill, cond, thresh = io.strings
    skill = skill.to_i - 1
    thresh = thresh.to_i
    conditions << [skill, cond, thresh]
  end
  commands << conditions
end

skills = Array.new(n, 0)
ok = true
while ok
  skills = Array.new(n, 1e9)
  commands.each do |conditions|
    conditions.each do |condition|
      skill, cond, thresh = condition
      if cond == '<=' && skills[skill] > thresh
        skills[skill] = thresh
      end
    end
  end

  ok = false
  _s = commands.size
  commands.delete_if do |conditions|
    conditions.all? do |condition|
      skill, cond, thresh = condition
      (cond == '<=' && skills[skill] <= thresh) || (cond == '>=' && skills[skill] >= thresh)
    end
  end
  ok = true if commands.size < _s
end

if commands.size == 0
  puts 'Yes'
else
  puts 'No'
end

# vim: foldmethod=marker
