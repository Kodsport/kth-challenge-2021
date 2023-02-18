#!/usr/bin/env python3

import sys

d, m = [int(x) for x in input().split()]

vantage = input()

num_mod, *modifiers = input().split()
num_mod = int(num_mod)
modifiers = [(+1 if x[0] == '+' else -1) * int(x[2:]) for x in modifiers]

assert len(modifiers) == int(num_mod)

memo = {}
def apply_modifiers(die, i):
    if (die,i) not in memo:
        if i < 0:
            memo[die, i] = float(die >= 0)
        else:
            mod = modifiers[i]
            mod_die = abs(mod)
            sign = mod // mod_die

            x = 0.0
            for res in range(1, mod_die + 1):
                x += apply_modifiers(die + sign * res, i - 1)
            memo[die, i] = 1.0 * x / mod_die
    return memo[die, i]

win_prob = 0.0
for d1 in range(1, 21):
    for d2 in range(1, 21):
        if vantage == 'straight':
            die = d1
        elif vantage == 'disadvantage':
            die = min(d1, d2)
        elif vantage == 'advantage':
            die = max(d1, d2)
        else:
            assert False

        if die == 1:
            continue

        if die == 20:
            win_prob += 1/400.0
            continue

        die += m - d
        win_prob += apply_modifiers(die, num_mod - 1) / 400.0

print(repr(win_prob))
