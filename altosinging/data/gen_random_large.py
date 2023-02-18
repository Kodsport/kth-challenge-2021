import random

Notes = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B']

def tonote(n):
	return Notes[n % len(Notes)] + str(1 + n // len(Notes))

MX = len(Notes) * 10**9

lo = random.randint(0, MX)
hi = random.randint(lo, MX)

trange = hi - lo
tlo = random.randint(0, MX - trange)
thi = tlo + trange

N = 1000
print(N)
print(tonote(lo), tonote(hi))
print(*[tonote(random.randint(tlo, thi)) for _ in range(N)])
