import random
import sys

N = 15000-1
print(N)
L = list(range(1, N + 1))
random.shuffle(L)
dups = 0
while random.random() < 0.75:
    dups += 1
    i = random.randint(0, N - 1)
    j = random.randint(0, N - 1)
    L[i] = L[j]
sys.stderr.write("%d dups\n" % dups)
print(*L)
