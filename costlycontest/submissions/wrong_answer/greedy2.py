#!/usr/bin/python3

n,m,k,t = [int(x) for x in input().split()]
S = [int(x) for x in input().split()]
D = [int(x) for x in input().split()]

D.sort(reverse=True)

fastest = min(S)
optimal_diff_sum = 0
for d in D:
    if (optimal_diff_sum + d) * fastest > t:
        continue
    optimal_diff_sum += d

print(max(k, sum(1 for s in S if optimal_diff_sum * s <= t)))
