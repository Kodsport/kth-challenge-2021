#!/usr/bin/python3

import sys
import random

N = 3000
small = 200

MOD = 10**9 + 7
def mult_mat_vec(A, B):
    n = len(B)
    C = []
    for Ai in A:
        ans = 0
        for j in range(n):
            ans = (ans + Ai[j] * B[j]) % MOD
        C.append(ans)
    return C

def sequencer(mat, i, j):
    n = len(mat)

    vec = [0] * n
    vec[j] = 1

    sequence = []
    for _ in range(2 * n + 1):
        sequence.append(vec[i])
        vec = mult_mat_vec(mat,vec)
    
    return sequence

def generate(filename, n, i, j, A):
    assert 1 <= n <= N
    assert len(A) == len(A[0]) == n
    assert 0 <= i < n
    assert 0 <= j < n
    
    sequence = sequencer(A, i, j)

    assert len(sequence) == 2 * n + 1
    assert all(0 <= a < MOD for a in sequence)
    assert A[i][j] == sequence[1]
    assert sequence[0] == +(i == j)

    sys.stdout = open(filename + '.in', 'w')
    print(n, i + 1, j + 1)
    out = [a for a in sequence[1:-1]]
    print(*sequence[1:-1])
    
    for row in A:
        print(*row)

    sys.stdout = sys.__stdout__

    sys.stdout = open(filename + '.ans', 'w')
    print(sequence[-1])
    sys.stdout = sys.__stdout__

for CASE in range(1, 21):
    sys.stderr.write("Doing case %d\n" % CASE)
    if CASE == 1:
        # SAMPLE 1
        filename = '../data/sample/%d' % CASE
        n = 3
        i = 0
        j = 0
        A = [[0,1,1],[1,0,0],[1,0,0]]
    elif CASE == 2:
        # SAMPLE 2
        filename = '../data/sample/%d' % CASE
        n = 1
        i = 0
        j = 0
        A = [[2]]
    elif CASE == 3:
        # TRICKY CASE 1
        filename = '../data/secret/%03dtricky' % (CASE - 2)
        n = 2
        i = 0
        j = 1
        A = [[1,1],[0,1]]
    elif CASE == 4:
        # TRICKY CASE 2
        filename = '../data/secret/%03dtricky' % (CASE - 2)
        n = 2
        i = 0
        j = 0
        A = [[1,1],[1,0]]
    elif CASE == 5:
        filename = '../data/secret/%03drandom' % (CASE - 2)
        # RANDOM TESTCASE
        random.seed(CASE)
        n = N#random.randint(1, 100) 
        i = random.randrange(n)
        j = random.randrange(n)

        A = [[random.randrange(MOD) for _ in range(n)] for _ in range(n)]
    elif CASE == 6:
        filename = '../data/secret/%03drandom' % (CASE - 2)
        # RANDOM TESTCASE
        random.seed(CASE)
        n = N#random.randint(1, 100) 
        i = j = random.randrange(n)

        A = [[random.randrange(MOD) for _ in range(n)] for _ in range(n)]
        A[i][j] = 0
    elif CASE <= 10:
        filename = '../data/secret/%03drandom' % (CASE - 2)
        # RANDOM TESTCASE
        random.seed(CASE)
        n = random.randint(1, 3) 
        i = random.randrange(n)
        j = random.randrange(n)

        A = [[random.randrange(MOD) for _ in range(n)] for _ in range(n)]
    elif CASE <= 15:
        filename = '../data/secret/%03drandom' % (CASE - 2)
        # RANDOM TESTCASE
        random.seed(CASE)
        n = random.randint(1, small) 
        i = random.randrange(n)
        j = random.randrange(n)

        A = [[random.randrange(MOD) for _ in range(n)] for _ in range(n)]
    elif CASE > 15:
        filename = '../data/secret/%03drandom' % (CASE - 2)
        # RANDOM TESTCASE
        random.seed(CASE)
        n = random.randint(1, small) 
        i = j = random.randrange(n)

        A = [[random.randrange(MOD) for _ in range(n)] for _ in range(n)]
    else:
        assert False

    generate(filename, n, i, j, A)
