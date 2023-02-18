#!/usr/bin/env python3

import sys

# Splitter for 'ABC123' into ['ABC', '123']
from itertools import groupby
numbers = '0123456789'
def splitter(s):
    return [''.join(g) for _, g in groupby(s, numbers.__contains__)]


Notes = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B']

n = int(input())
l,r = [Notes.index(c) + 12 * int(o) for c,o in map(splitter, input().split())]
A   = [Notes.index(c) + 12 * int(o) for c,o in map(splitter, input().split())]

# Transpose down as much as possible
Amin = min(A)
A = [a - Amin + l for a in A]
Amax = max(A)

# Assert there exists a solution
assert Amax <= r

sys.exit(42)
