#!/usr/bin/python3

import sys
inp = [int(x) for x in sys.stdin.read().split()]; ii = 0

n = inp[ii]; ii += 1
maxvol = inp[ii]; ii += 1

S = inp[ii + 0: ii + 2 * n: 2]
W = inp[ii + 1: ii + 2 * n: 2]
ii += 2 * n

# Check if a pair of (emin, emax) is possible
def checker(emin, emax):
    if emin > emax:
        return False

    waterl = 0
    waterr = 0
    for i in range(n):
        s = S[i]
        w = W[i]

        if s > emax:
            return False

        mindw = max(0, emin - s, waterl + w - (maxvol if i != n - 1 else 0))
        maxdw = emax - s

        if mindw > maxdw:
            return False

        waterl = max(waterl + w - maxdw, 0)
        waterr = min(waterr + w - mindw, maxvol)

        if waterl > waterr:
            return False
    return True

# Finds smallest x in [l,r] such that f(x) is True, assuming f(r) increasing boolean
def binary_searcher_from_right(f, l, r):
    while l < r:
        m = l + r >> 1
        if not f(m):
            l = m + 1
        else:
            r = m
    return l, f(l)

# Finds largest x in [l,r] such that f(x) is True, assuming f decreasing boolean
def binary_searcher_from_left(f, l, r):
    while l < r:
        m = l + r + 1 >> 1
        if not f(m):
            r = m - 1
        else:
            l = m
    return l, f(l)


# Binary search for optimal (emin, emax) pair

def param(emax):
    emin, possible = binary_searcher_from_left(lambda emin: checker(emin, emax), 0, 4 * 10**9)
    return possible

emax, possible = binary_searcher_from_right(param, 0, 4 * 10**9)
assert possible == True
emin, possible = binary_searcher_from_left(lambda emin: checker(emin, emax), 0, 4 * 10**9)
assert possible == True

print(emax - emin)
