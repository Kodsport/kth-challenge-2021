import random

N = 15000-1
print(N)
L = list(range(1, N + 1))
p = random.randint(0, N // 2)
L[p] = L[p + N // 2]
print(*L)
