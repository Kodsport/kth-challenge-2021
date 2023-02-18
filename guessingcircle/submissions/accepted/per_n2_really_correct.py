#!/usr/bin/env python3

def in_ival(l, x, r):
    if r < l: r += n
    if x < l: x += n
    return x <= r;

def overlap(I, J):
    (l1, r1) = I
    (l2, r2) = J
    if l1 == -1 or l2 == -1: return False
    if r1 < l2:
        l1 += n
        r1 += n
    if r2 < l1:
        l2 += n
        r2 += n
    if r1 < l2: return False
    (l, r) = (max(l2, l1), min(r1, r2))
    l %= n
    return (r-l+1) % n >= min_len[l]

def fix_ival(l, r):
    l %= n
    r %= n
    if r < l: r += n
    if r-l+1 < min_len[l]: return (-1, 0)
    return (l, r)

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
prev = [0]*n
next = [0]*n
for i in range(m):
    x = positions[i][-1]
    for y in positions[i]:
        prev[y] = x
        next[x] = y
        x = y

min_len = [n]*n
for l in range(n):
    for length in range(1, n):
        r = (l + length - 1) % n
        if in_ival(l, prev[l], r) or in_ival(l, next[r], r):
            min_len[l] = length
            break
for i in range(2*n, 0, -1):
    min_len[i%n] = min(min_len[i%n], min_len[(i+1)%n]+1)

excludeL = [(-1, 0)]*m
excludeR = [(-1, 0)]*m

for i in range(m):
    if len(positions[i]) == 1:
        x = positions[i][0]
        excludeL[i] = fix_ival(x - (n-1)//2, x - 1)
        excludeR[i] = fix_ival(x + 1, x + (n-1)//2)
    else:
        x = positions[i][-1]
        for y in positions[i]:
            if (y-x) % n > n//2 + 1:
                excludeL[i] = fix_ival(x + n//2 + 1, y - 1)
                excludeR[i] = fix_ival(x + 1, y - n//2 - 1)
                break
            x = y

ans = []
for (num, i) in num_idx.items():
    exL = excludeL[i]
    exR = excludeR[i]
    for j in range(m):
        if not (j == i or overlap(exL, excludeR[j]) or overlap(exR, excludeL[j])):
            break
    else:
        ans.append(num)

if not ans:
    print("none");
else:
    ans.sort()
    print(*ans)
