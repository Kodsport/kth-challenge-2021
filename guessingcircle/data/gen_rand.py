import random

def sol(L):
    N = 1000

    n = len(L)
    A = [int(x) - 1 for x in L]

    nhalf = n // 2
    L = [[0] * N for _ in range(N)]
    R = [[0] * N for _ in range(N)]

    for i in range(n):
        for j in range(n):
            ai = A[i]
            aj = A[j]

            if (i - j) % n <= nhalf:
                L[ai][aj] = R[aj][ai] = 1

    for i in range(N):
        for j in range(N):
            if L[i][j] == R[i][j] == 1:
                L[i][j] = R[i][j] = 0

    def bitmask(A):
        """ Transform boolean list A into a bitset (a big integer) """
        n = len(A)
        if n <= 63:
            x = 0
            for a in A:
                x = (x << 1) ^ a
            return x
        else:
            nhalf = n // 2
            return (bitmask(A[:-nhalf]) << nhalf) ^ bitmask(A[-nhalf:])

    L = [bitmask(l) for l in L]
    R = [bitmask(r) for r in R]

    Aset = sorted(set(A))
    unique = [0] * N
    for a in Aset:
        unique[a] = 1
        for b in range(a):
            if (unique[a] or unique[b]) and not (L[a] & R[b] or R[a] & L[b]):
                unique[a] = unique[b] = 0

    if any(unique):
        return True
    else:
        return False

N = 999
while True:
    L = list(range(1, N+1))
    for i in range(10):
        L[random.randint(0, N - 1)] = random.randint(1, 1000)
    random.shuffle(L)
    if sol(L): break
print(N)
print(*L)

