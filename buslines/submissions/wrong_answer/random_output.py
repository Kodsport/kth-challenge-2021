#!/usr/bin/env python3

import random
(n, m) = map(int, input().split())
for _ in range(0, m):
    a = random.randint(1, n)
    b = random.randint(1, n)
    print(a, b)