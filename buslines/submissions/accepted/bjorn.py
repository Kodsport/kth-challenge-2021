#!/usr/bin/env python3

n,m = [int(x) for x in input().split()]
Needed = [(1,i) for i in range(2, n+1)]
Extra = [(n,i) for i in range(2,n)]

if len(Needed) <= m <= len(Needed) + len(Extra):
    for u,v in (Needed + Extra)[:m]:
        print(u, v)
else:
    print(-1)
