#!/usr/bin/python3

"""
    A cubic solution sped up using bitset
    implemented using Python's big integers.
"""
N = 10000

n = int(input())
A = [int(x) - 1 for x in input().split()]

nhalf = n // 2
L = [[0] * N for _ in range(N)]
R = [[0] * N for _ in range(N)]

for i in range(n):
    for j in range(n):
        ai = A[i]
        aj = A[j]

        if (i - j) % n <= nhalf:
            L[ai][aj] = R[aj][ai] = 1

for i in range(N):
    for j in range(N):
        if L[i][j] == R[i][j] == 1:
            L[i][j] = R[i][j] = 0

def bitmask(A):
    """ Transform boolean list A into a bitset (a big integer) """
    n = len(A)
    if n <= 63:
        x = 0
        for a in A:
            x = (x << 1) ^ a
        return x
    else:
        nhalf = n // 2
        return (bitmask(A[:-nhalf]) << nhalf) ^ bitmask(A[-nhalf:])

L = [bitmask(l) for l in L]
R = [bitmask(r) for r in R]

Aset = sorted(set(A))
unique = [0] * N
for a in Aset:
    unique[a] = 1
    for b in range(a):
        if (unique[a] or unique[b]) and not (L[a] & R[b] or R[a] & L[b]):
            unique[a] = unique[b] = 0

if any(unique):
    print(' '.join(str(x + 1) for x in Aset if unique[x]))
else:
    print('none')
