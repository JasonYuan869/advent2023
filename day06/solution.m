% Part 1
inputs = [41 249; 77 1362; 70 1127; 96 1011];
outputs = zeros(4, 1);
for i = 1:4
  outputs(i) = processRace(inputs(i, 1), inputs(i, 2))
end
prod(outputs)

% Part 2
processRace(41777096, 249136211271011)

function count = processRace(time, distance)
  p = [-1 time -distance];
  r = roots(p);
  hi = floor(r(1));
  lo = floor(r(2));
  count = hi - lo;
end
