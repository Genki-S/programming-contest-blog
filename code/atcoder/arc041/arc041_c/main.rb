n, l = gets.split.map(&:to_i)
x, d = [], []
n.times do
  _x, _d = gets.split
  x << _x.to_i - 1
  d << _d
end

ans = 0
disabled = Array.new(n, false)
p = Array.new(n, 1) # potential
(1...n).each do |i|
  if d[i-1] == 'R' && d[i] == 'R'
    ans += p[i-1] * (x[i] - x[i-1] - 1)
    p[i] += p[i-1]
    disabled[i-1] = true
  end
end
(n-2).downto(0).each do |i|
  if d[i+1] == 'L' && d[i] == 'L'
    ans += p[i+1] * (x[i+1] - x[i] - 1)
    p[i] += p[i+1]
    disabled[i+1] = true
  end
end

if d[0] == 'L'
  ans += x[0] * p[0]
  disabled[0] = true
end
if d[n-1] == 'R'
  ans += (l - x[n-1] - 1) * p[n-1]
  disabled[n-1] = true
end

(0...n).each do |i|
  next if disabled[i]
  next if d[i] != 'R'

  raise unless d[i+1] == 'L'
  dist = x[i+1] - x[i] - 1
  ans += [p[i] * dist, p[i+1] * dist].max
end

puts ans
