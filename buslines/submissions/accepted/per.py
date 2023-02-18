#!/usr/bin/env python3

(n, m) = map(int, input().split())

E = []
used = [0]*(2*n)
for i in range(1, n):
    used[2*i+1] = 1
    E.append((i, i+1))

for i in [1, n]:
    for j in range(1, n):
        if j != i and len(E) < m and not used[i+j]:
            E.append((i, j))
            used[i+j] = 1

if len(E) != m:
    print(-1)
else:
    for (a, b) in E:
        print(a, b)
