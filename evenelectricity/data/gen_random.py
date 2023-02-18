#!/usr/bin/python3

import sys
import random

default = {
    "n": 10,
    "r": 10**9,
    "maxW": 10**9,
    "maxS": 10**9,
    "dry": 0,
    "sun": 0,
}

def cmdlinearg(name):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    return default[name]

def main():

    random.seed(int(sys.argv[-1]))
    n = int(cmdlinearg("n"))
    r = int(cmdlinearg("r"))
    maxW = int(cmdlinearg("maxW"))
    maxS = int(cmdlinearg("maxS"))
    dry = int(cmdlinearg("dry"))
    sun = int(cmdlinearg("sun"))

    droughts = set(random.sample(range(0, n), dry))
    heatwaves = set(random.sample(range(0, n), sun))

    drought = 0
    heatwave = 0

    print(n, r)
    for i in range(n):
        if i in droughts:
            drought ^= 1
        if i in heatwaves:
            heatwave ^= 1
        if drought == 1:
            water = 0
            sun = 0
        elif heatwave == 1:
            water = 0
            sun = 10**9
        else:
            water = random.randint(0, maxW)
            sun = random.randint(0, maxS)
        print(water, sun)

    
    
if __name__ == "__main__":
    main()