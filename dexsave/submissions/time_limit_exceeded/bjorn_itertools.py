#!/usr/bin/env python3
from itertools import product

d20funs = {'straight': lambda x: x[0],
           'advantage': lambda x: max(x[0], x[1]),
           'disadvantage': lambda x: min(x[0], x[1])}

def get_die(x):
    sgn = int(x[0]+'1')
    return range(sgn, sgn*(int(x[2:])+1), sgn)

(d, m) = map(int, input().split())
d20result = d20funs[input()]
dice = [range(1, 21), range(1, 21)] + [get_die(x) for x in input().split()[1:]]

t = w = 0
for vals in list(product(*dice)):
    d20 = d20result(vals)
    w += d20 > 1 and (d20 == 20 or d20 + sum(vals[2:]) + m >= d)
    t += 1

print('%.9lf' % (w/t))
