import sys
import random

random.seed(1337)

n = 10**5 
R = 10**9

print(n, R)

S = [10**9] * n
W = [10**4] * n

for i in range(n):
    W[random.randrange(i + 1)] += 1

for i in range(n):
    print(S[i], W[i])
