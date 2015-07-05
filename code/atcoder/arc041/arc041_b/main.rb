n, m = gets.split.map(&:to_i)
b = []
n.times do
  b << gets.chomp.split('').map(&:to_i)
end

dy = [-1, 0, 1, 0]
dx = [0, 1, 0, -1]
a = Array.new(n) { Array.new(m, 0) }
1.upto(n-2) do |i|
  1.upto(m-2) do |j|
    min = dy.zip(dx).map { |d| b[i+d[0]][j+d[1]] }.min
    a[i][j] = min
    dy.zip(dx).map do |d|
      ni, nj = i+d[0], j+d[1]
      b[ni][nj] -= min
    end
  end
end

a.each do |line|
  puts line.join('')
end
