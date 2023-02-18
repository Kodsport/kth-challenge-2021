import sys
import random

random.seed(1337)

n = 10**5 
R = 10**9 - 1

print(n, R)

S = [random.randint(0,10**9) for _ in range(n)]
W = [10**9] * n

for i in range(n):
    print(S[i], W[i])
