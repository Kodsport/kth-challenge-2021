#!/usr/bin/env python3

Tones = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B']
Cost = ['#' in Tones[i] for i in range(12)]

def tone(x):
    if x[:2] in Tones:
        return int(x[2:])*12 + Tones.index(x[:2])
    return int(x[1:])*12 + Tones.index(x[:1])

n = int(input())
(lo, hi) = map(tone, input().split())
song = list(map(tone, input().split()))

shift_lo = lo - min(song)
shift_hi = hi - max(song) + 1

assert shift_lo <= shift_hi
mincost = 1<<30
ways = 0
for r in range(12):
    cost = sum(Cost[(x + r) % 12] for x in song)
    cnt = (shift_hi + (r - shift_hi) % 12 - (shift_lo + (r - shift_lo) % 12)) // 12
    if cnt:
        if cost < mincost:
            mincost = cost
            ways = 0
        if cost == mincost:
            ways += cnt
print(mincost, ways)
