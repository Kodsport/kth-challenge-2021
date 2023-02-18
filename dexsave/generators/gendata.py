#!/usr/bin/env pypy
import os
import random
import sys

D_RANGE = (0, 30)
M_RANGE = (-10, 10)
MAX_MODS = 5
MOD_DIE_RANGE = (3, 10)
STATUSES = ['straight', 'advantage', 'disadvantage']

CASE = 1
DEST = os.path.join(os.path.dirname(__file__), '../data/secret')

def next_file(short_desc=None, long_desc=None):
    global CASE
    basename = os.path.join(DEST, '%03d' % CASE)
    CASE += 1
    if short_desc is not None:
        basename += '-' + short_desc
    if long_desc is not None:
        with open(basename+'.desc', 'w') as desc_out:
            desc_out.write(long_desc)
    return open(basename+'.in', 'w')

def format_die(x):
    return ' %sd%d' % ('+' if x > 0 else '-', abs(x))

def save_case(d, m, status, mods, short_desc=None, long_desc=None):
    out = next_file(short_desc=short_desc, long_desc=long_desc)
    out.write('%d %d\n' % (d, m))
    out.write('%s\n' % status)
    out.write('%d%s\n' % (len(mods), ''.join(map(format_die, mods))))
    out.close()


def gen_uniform_case(k, mod_die_range=MOD_DIE_RANGE, short_desc=None):
    d = random.randint(*D_RANGE)
    m = random.randint(*M_RANGE)
    status = random.choice(STATUSES)
    mods = [random.choice([-1,1])*random.randint(*mod_die_range) for _ in range(k)]
    save_case(d, m, status, mods, short_desc=short_desc)

def main():
    random.seed(23)

    for _ in range(5):
        gen_uniform_case(0)

    for _ in range(5):
        gen_uniform_case(1)

    for _ in range(10):
        k = random.randint(2, MAX_MODS)
        gen_uniform_case(k)

    gen_uniform_case(MAX_MODS, mod_die_range = (MOD_DIE_RANGE[1], MOD_DIE_RANGE[1]),
                     short_desc='maxsize')
    gen_uniform_case(MAX_MODS, mod_die_range = (MOD_DIE_RANGE[1], MOD_DIE_RANGE[1]),
                     short_desc='maxsize')
    gen_uniform_case(MAX_MODS, mod_die_range = (MOD_DIE_RANGE[1], MOD_DIE_RANGE[1]),
                     short_desc='maxsize')
    gen_uniform_case(MAX_MODS, mod_die_range = (MOD_DIE_RANGE[1], MOD_DIE_RANGE[1]),
                     short_desc='maxsize')


if __name__=='__main__':
    main()
