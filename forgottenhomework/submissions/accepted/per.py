#!/usr/bin/env python3
MOD = 10**9 + 7

def inv(x): return pow(x, MOD-2, MOD)
def add(P, Q):
    return [(P[i] if i < len(P) else 0) + (Q[i] if i < len(Q) else 0)
            for i in range(max(len(P), len(Q)))]
def mul(c, P):   return [c*p % MOD for p in P]
def shift(i, P): return [0]*i + P

(n, i, j) = map(int, input().split())
seq = [i==j] + list(map(int, input().split()))
coeffs = [1]
corr = [1]
m = 0

for i in range(2*n):
    m += 1
    disc = sum(c*x for (c, x) in zip(coeffs, seq[i::-1])) % MOD
    if disc:
        new_corr = mul(inv(disc), coeffs)
        coeffs = add(coeffs, shift(m, mul(-disc, corr)))
        if len(new_corr) <= i//2 + 1:
            corr = new_corr
            m = 0

print(-sum(c*x for (c, x) in zip(coeffs[1:], seq[-1::-1])) % MOD)
