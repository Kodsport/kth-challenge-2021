#!/usr/bin/env python3
import bisect
import heapq

(n, m, k, t) = map(int, input().split())
skills = list(map(int, input().split()))
diffs = list(map(int, input().split()))

poss_diffs = {0}
for diff in diffs:
    poss_diffs |= set(x + diff for x in poss_diffs if x + diff <= t)
skill_separators = list(sorted(set(t // diff for diff in poss_diffs if diff)))
skill_separators.append(1<<30)
skill_separators = list(sorted(set(skill_separators[bisect.bisect_left(skill_separators, skill)]
                                   for skill in skills)))

best = [n]*(n+1)
best[n] = 0
for i in range(n-1, -1, -1):
    min_skill = skills[i]
    sep_idx = bisect.bisect_left(skill_separators, skills[i])
    winners = []
    for j in range(i, n):
        heapq.heappush(winners, -skills[j])
        min_skill = min(min_skill, skills[j])
        while sep_idx > 0 and skill_separators[sep_idx-1] >= min_skill:
            sep_idx -= 1
        while -winners[0] > skill_separators[sep_idx]:
            heapq.heappop(winners)
        best[i] = min(best[i], len(winners) + best[j+1])

print(max(k, best[0]))
