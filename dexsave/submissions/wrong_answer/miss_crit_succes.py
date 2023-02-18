#!/usr/bin/env python3

d20funs = {'straight': lambda x: x[0],
           'advantage': lambda x: max(x),
           'disadvantage': lambda x: min(x)}

(d, m) = map(int, input().split())
d20result = d20funs[input()]
mods = [(int(x[0]+'1'), int(x[2:])) for x in input().split()[1:]]

def calc_mods(cur, i):
    if i == len(mods):
        return 1.0*(cur >= 0)
    (sgn, die) = mods[i]
    p = 0.0
    for x in range(1, die+1):
        p += calc_mods(cur + sgn*x, i + 1) / die
    return p

p = 0.0
for a in range(1, 21):
    for b in range(1, 21):
        d20 = d20result((a, b))
        if False and d20 == 20: p += 1 / 400.0
        elif d20 > 1: p += calc_mods(d20 + m - d, 0) / 400.0

print('%.9lf' % p)
