import sys
import random

random.seed(1337)

n = 10**5 
R = 1

print(n, R)

S = [0] * n
W = [1] * n

W[random.randrange(n)] = 0

for i in range(n):
    print(S[i], W[i])
