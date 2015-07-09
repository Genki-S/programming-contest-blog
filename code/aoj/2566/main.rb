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

io.set_input('inputs/0.txt')

MOD = 1_000_000_007

while true
  a = io.gets
  break if a == '0'
  b, c = io.gets, io.gets

  # dp[pos][carried][carry] = combinations % MOD
  dp = Array.new(a.length) { Array.new(2) { Array.new(2, 0) } }
  a.reverse!
  b.reverse!
  c.reverse!
  a.length.times do |i|
    (0..9).each do |ad|
      next if (a[i] != '?' && a[i].to_i != ad) || (i == a.length - 1 && ad == 0)
      (0..9).each do |bd|
        next if (b[i] != '?' && b[i].to_i != bd) || (i == a.length - 1 && bd == 0)
        (0..9).each do |cd|
          next if (c[i] != '?' && c[i].to_i != cd) || (i == a.length - 1 && cd == 0)
          carried = nil
          if (ad + bd + 1) % 10 == cd
            carried = 1
          elsif (ad + bd) % 10 == cd
            carried = 0
          else
            next
          end
          next if i == 0 && carried == 1

          carry = ad + bd + carried >= 10 ? 1 : 0
          if i == 0
            dp[i][carried][carry] += 1
          else
            dp[i][carried][carry] = (dp[i][carried][carry] + dp[i-1][0][carried] + dp[i-1][1][carried]) % MOD
          end
        end
      end
    end
  end

  io.puts (dp[a.length - 1][0][0] + dp[a.length - 1][1][0]) % MOD
end

# vim: foldmethod=marker
