import sys
import random

random.seed(1337)

n = 10**5 
R = 10**9

print(n, R)

S = [0] * n
W = [0] * n

S[random.randrange(n)] = 1
S[random.randrange(n)] = 1
for i in range(n - 2):
    W[random.randrange(i + 1)] += 1

for i in range(n):
    print(S[i], W[i])
