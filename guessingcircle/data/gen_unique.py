import random

N = 15000
print(N)
L = list(range(1, N + 1))
random.shuffle(L)
print(*L)
