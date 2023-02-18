#!/usr/bin/env python3
import sys

BITS = 62
ALL = (1<<BITS)-1

n = int(input())
circle = list(map(int, input().split()))

num_idx = {}
positions = []
for (i, c) in enumerate(circle):
    if c not in num_idx:
        num_idx[c] = len(num_idx)
        positions.append([])
    positions[num_idx[c]].append(i)

m = len(num_idx)
fill = ALL ^ ((1<<(m%BITS)) - 1) if m % BITS else 0
words = (m+BITS-1)//BITS
possL = [[0]*words for _ in range(m)]
possR = [[0]*words for _ in range(m)]
for a in range(m):
    possL[a][words-1] |= fill
    possR[a][words-1] |= fill
    for b in range(m):
        for i in positions[a]:
            for j in positions[b]:
                dR = (j-i) % n
                dL = (i-j) % n
                if dL <= dR:
                    possL[a][b//BITS] |= 1<<(b%BITS)
                if dR <= dL:
                    possR[a][b//BITS] |= 1<<(b%BITS)


ans = []
for (num, idx) in num_idx.items():
    ok = 1
    L1 = possL[idx]
    R1 = possR[idx]
    for j in range(m):
        if j == idx: continue
        same = 1
        L2 = possL[j]
        R2 = possR[j]
        for k in range(words):
            same &= ((L1[k] & L2[k]) | (R1[k] & R2[k])) == ALL
            if not same: break
        ok &= not same
        if not ok: break
    if ok: ans.append(num);

if not ans:
    print("none");
else:
    ans.sort()
    print(*ans)
