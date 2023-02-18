import random
random.seed(1337)

n = 15000 - 1
A = list(range(1, n + 1))
random.shuffle(A)

print(n)
print(*A)
