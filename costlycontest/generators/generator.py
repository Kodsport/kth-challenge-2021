#!/usr/bin/python3

import sys
import random

MAX_N = 10**5
MAX_M = 100
MAX_S = 10**5
MAX_D = 10**5
MAX_T = 10**5

for CASE in range(1, 109):
    filename = "../data/secret/%03drandom" % CASE
    random.seed(CASE)

    if CASE <= 20:
        t = MAX_T
        k = 1
        S = [random.randint(1, MAX_S) for _ in range(MAX_N)]
        D = [random.randint(1, MAX_D) for _ in range(MAX_M)]
    elif CASE <= 40:
        t = MAX_T
        k = 1
        S = [random.randint(100, MAX_S) for _ in range(MAX_N)]
        D = [random.randint(100, MAX_D) for _ in range(MAX_M)]
    elif CASE <= 60:
        t = MAX_T
        k = 10
        S = [random.randint(100, MAX_S) for _ in range(MAX_N)]
        D = [random.randint(100, MAX_D) for _ in range(MAX_M)]
    elif CASE <= 80:
        k = 1
        S = [random.randint(100, 101) for _ in range(MAX_N)]
        D = [random.randint(10, 100) for _ in range(10)]
        t = (sum(D) - max(D)) * 100 - 1
    elif CASE == 81:
        k = 500
        S = [random.randint(MAX_S - 1, MAX_S) for _ in range(MAX_N)]
        D = [random.randint(1, 1) for _ in range(100)]
        t = MAX_T - 1
    elif CASE == 82:
        k = 500
        S = [random.randint(MAX_S - 1, MAX_S) for _ in range(MAX_N)]
        D = [random.randint(1, 1) for _ in range(1)]
        t = MAX_T - 1
    elif CASE == 83:
        k = 500
        S = [random.randint(MAX_S - 1, MAX_S) for _ in range(MAX_N)]
        D = [random.randint(MAX_D, MAX_D) for _ in range(MAX_M)]
        t = MAX_T - 1
    elif CASE == 84:
        k = 999
        S = [random.randint(MAX_S - 1000, MAX_S) for _ in range(MAX_N)]
        D = [random.randint(1,1) for _ in range(MAX_M)]
        t = MAX_T - 1
    elif CASE <= 90:
        k = 1000
        S = [random.randint(MAX_S - 1000, MAX_S) for _ in range(MAX_N)]
        D = [random.randint(MAX_D, MAX_D) for _ in range(MAX_M)]
        t = MAX_T - 1
    elif CASE <= 95:
        k = 1
        S = [random.randint(MAX_S - 1000, MAX_S) for _ in range(MAX_N)]
        D = [random.randint(MAX_D, MAX_D) for _ in range(MAX_M)]
        t = 1
    elif CASE <= 100:
        k = 1
        S = [random.randint(99, 100) for _ in range(MAX_N)]
        D = [random.randint(1,1) for _ in range(MAX_M)]
        t = 100
    elif CASE <= 105:
        k = 1
        S = [random.randint(MAX_S - 100, MAX_S) for _ in range(MAX_N)]
        D = [1 << d for d in range(20) if (1 << d) <= MAX_D]
        while len(D) < 100:
            D.append(1)
        t = MAX_T
    elif CASE <= 108:
        k = 1
        lim = random.randint(1, MAX_N)
        S = [random.randint(1, lim) for _ in range(MAX_N)]
        logD = MAX_D.bit_length() - 1
        D = [1<<random.randint(0, logD) for _ in range(MAX_M)]
        t = MAX_T
        filename = "../data/secret/%03d-pow2difficulties" % CASE


    assert 1 <= len(S) <= MAX_N
    assert 1 <= len(D) <= MAX_M
    assert all(1 <= s <= MAX_S for s in S)
    assert all(1 <= d <= MAX_D for d in D)
    assert 1 <= k <= len(S)
    assert 1 <= t <= MAX_T

    sys.stdout = open(filename + '.in', 'w')
    print(len(S),len(D),k,t)
    print(*S)
    print(*D)
    sys.stdout = sys.__stdout__


    def solve(S,D,t,k):
        is_possible = [0] * (t + 1)
        is_possible[0] = 1
        for d in D:
            for i in reversed(range(t + 1 - d)):
                is_possible[i + d] |= is_possible[i]

        fastest = min(S)
        optimal_diff_sum = max(i for i in range(t + 1) if is_possible[i] and i * fastest <= t)

        if S.count(fastest) != sum(1 for s in S if optimal_diff_sum * s <= t):
            sys.stderr.write("Good test case found %d!\n" % CASE)

        return max(k, sum(1 for s in S if optimal_diff_sum * s <= t))

    sys.stdout = open(filename + '.ans', 'w')
    print('%d' % solve(S,D,t,k))
    sys.stdout = sys.__stdout__
