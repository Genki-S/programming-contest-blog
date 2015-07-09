# Header {{{

def assert(p)
  raise 'Assertion Failed' unless p
end

# Requires {{{
require 'set'
# }}}

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

# io.set_input('inputs/2.txt')
# io.set_output('my_outputs/2.txt')

while true
  n = io.int
  break if n == 0
  bigger_chars = Hash.new { |h, k| h[k] = Set.new }
  prev_word = ''
  ok = true
  n.times do |i|
    word = io.gets
    [prev_word.length, word.length].min.times do |j|
      if prev_word[j] == word[j]
        next
      elsif bigger_chars[word[j]].include?(prev_word[j])
        ok = false and break
      else
        bigger_chars[prev_word[j]] << word[j]
        # Update dependencies
        ('a'..'z').each do |c|
          q = bigger_chars[c].to_a
          while !q.empty?
            tc = q.pop
            bigger_chars[c] << tc
            q += (bigger_chars[tc] - bigger_chars[c]).to_a
          end
        end
        break
      end
    end
    if prev_word.start_with?(word) && prev_word != word
      ok = false
    end
    prev_word = word
  end
  io.puts ok ? 'yes' : 'no'
end

# vim: foldmethod=marker
