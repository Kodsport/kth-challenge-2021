#!/usr/bin/env python3

(n, r) = map(int, input().split())
days = [list(map(int, input().split())) for _ in range(n)]

def check_lb(e):
    cur = 0
    for (s, w) in days:
        cur += w
        if s < e: cur -= e-s
        if cur < 0: return False
        cur = min(r, cur)
    return True

def check_ub(e):
    cur = 0
    for (s, w) in days:
        cur += w
        if cur > r:
            s += cur - r
            cur = r
        if s > e: return False
        cur = max(0, cur - (e-s))
    return cur == 0

def find_thres(fun, sgn):
    lo = 0
    hi = 1<<31
    while hi - lo > 1:
        m = (lo+hi)//2
        if fun(m) ^ sgn: lo = m
        else: hi = m
    return lo + sgn

print(find_thres(check_ub, 1) - find_thres(check_lb, 0))
