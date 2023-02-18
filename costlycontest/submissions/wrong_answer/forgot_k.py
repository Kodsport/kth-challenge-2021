#!/usr/bin/python3

n,m,k,t = [int(x) for x in input().split()]
S = [int(x) for x in input().split()]
D = [int(x) for x in input().split()]

is_possible = [0] * (t + 1)
is_possible[0] = 1
for d in D:
    for i in reversed(range(t + 1 - d)):
        is_possible[i + d] |= is_possible[i]

fastest = min(S)
optimal_diff_sum = max(i for i in range(t + 1) if is_possible[i] and i * fastest <= t)

print(sum(1 for s in S if optimal_diff_sum * s <= t))
