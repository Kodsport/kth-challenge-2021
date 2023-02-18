import sys
import random

random.seed(1337)

n = 10**5 
R = 1

print(n, R)

S = [10**9] * n
W = [10**9] * n

for i in range(n):
    W[random.randrange(i, n)] -= 1

for i in range(n):
    print(S[i], W[i])
