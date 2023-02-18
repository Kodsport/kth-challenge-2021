import random

N = 15000-1
L = list(range(1, N+1))
for i in range(10):
    L[random.randint(0, N - 1)] = random.randint(1, 15000)
random.shuffle(L)
print(N)
print(*L)
