#!/usr/bin/python3

"""
    A cubic solution sped up using bitset
    implemented using Python's big integers.
"""
N = 10000

n = int(input())
A = [int(x) - 1 for x in input().split()]
X = sorted(set(A))

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

import __pypy__
add = __pypy__.intop.int_add
def bitmask_inverse(mask, n=N):
    """ Transform a bitset (a big integer) into a boolean list"""
    if n <= 63:
        smallmask = add(mask, 0)
        return [(smallmask >> i) & 1 for i in reversed(range(n))]
    else:
        nhalf = n // 2
        upper = mask >> nhalf
        return bitmask_inverse(upper, n - nhalf) + bitmask_inverse(mask ^ (upper << nhalf), nhalf)

R = [bitmask(r) for r in R]
is_diff = [0] * N

for y in range(N):
    # Must answer right
    mask = R[y]
    # Must answer left
    left = L[y]
    for x in range(N):
        if left[x]:
            is_diff[x] |= mask

is_diff = list(map(bitmask_inverse, is_diff))
for x1 in range(N):
    for x2 in range(N):
        is_diff[x1][x2] |= is_diff[x2][x1]

out = []
for x1 in X:
    if all(is_diff[x1][x2] or x1 == x2 for x2 in X):
        out.append(x1)

if out:
    print(' '.join(str(x + 1) for x in out))
else:
    print('none')
