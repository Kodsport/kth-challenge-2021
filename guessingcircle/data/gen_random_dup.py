import random

N = 15000-1
print(N)
L = list(range(1, N + 1))
random.shuffle(L)
i = random.randint(0, N - 1)
j = random.randint(0, N - 1)
L[i] = L[j]
print(*L)
