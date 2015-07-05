x, y = gets.split.map(&:to_i)
k = gets.to_i
if y >= k
  puts x + k
else
  puts (x + y) - (k - y)
end
