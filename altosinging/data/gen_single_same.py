import random

Notes = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B']

def tonote(n):
	return Notes[n % len(Notes)] + str(1 + n // len(Notes))

MX = len(Notes) * 10**9

lo = random.randint(0, MX)
hi = lo

N = random.randint(1, 1000)
print(N)
print(tonote(lo), tonote(hi))
print(*[tonote(lo) for _ in range(N)])
