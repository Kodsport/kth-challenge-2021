N = 5000
print(N)
L = [3] + [1 + i % 2 for i in range(1, N)]
print(*L)
