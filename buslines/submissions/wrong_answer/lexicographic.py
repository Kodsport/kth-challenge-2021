#!/usr/bin/env python3
(n, m) = map(int, input().split())
if m < n-1 or m > (n*(n-1))//2:
    print(-1)
else:
    ans = []
    for i in range(1, n+1):
        for j in range(i+1, n+1):
            if len(ans) == m:
                break
            ans.append((i, j))
    for e in ans:
        print(*e)