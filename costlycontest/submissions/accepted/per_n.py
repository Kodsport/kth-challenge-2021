#!/usr/bin/env python3
(n, m, k, t) = map(int, input().split())
skills = list(map(int, input().split()))
diffs = list(map(int, input().split()))
best = min(skills)
poss_diffs = {0}
for diff in diffs:
    poss_diffs |= set(x + diff for x in poss_diffs if x + diff <= t and t//(x+diff) >= best)
sep = min(t // diff for diff in poss_diffs if diff) if len(poss_diffs) > 1 else 1<<30
print(max(k, sum(1 for s in skills if s <= sep)))
