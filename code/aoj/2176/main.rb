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

# }}}

# io.set_input('inputs/2.txt')
# io.set_output('my_outputs/1.txt')

while true
  n, d = io.intl
  break if n == 0

  missiles = Array.new(n) { [] }
  n.times do |i|
    c = io.intl
    c.shift
    missiles[i] = c
  end

  maxs, mins = 0, INF
  maxi, mini = nil, nil
  sums = Array.new(n) { [] }
  n.times do |i|
    sum = missiles[i].reduce(:+) || 0
    sums[i] = sum
    if sum > maxs
      maxs, maxi = sum, i
    end
    if sum < mins
      mins, mini = sum, i
    end
  end

  disposed = true
  while disposed
    disposed = false
    n.times do |i|
      next if missiles[i].empty?
      next if i == maxi
      nsum = sums[i] - missiles[i].last
      next if maxs - nsum > d

      sums[i] -= missiles[i].pop
      disposed = true
      if nsum < mins
        mini = i
        mins = nsum
      end
    end

    # Try removing from max sum country
    maxs2, maxi2 = 0, nil
    n.times do |i|
      next if i == maxi
      if sums[i] > maxs2
        maxs2, maxi2 = sums[i], i
      end
    end

    if maxi2.nil?
      missiles[maxi] = []
      break
    end

    ns = sums[maxi] - missiles[maxi].last
    if ns < mins
      next if maxs2 - ns > d
      mins, mini = ns, maxi
    end
    disposed = true
    _t = missiles[maxi].pop
    sums[maxi] -= _t
    maxs -= _t

    if maxs < maxs2
      maxs, maxi = maxs2, maxi2
    end
  end

  if missiles.all? { |m| m.empty? }
    io.puts "Yes"
  else
    io.puts "No"
  end
end

# vim: foldmethod=marker
