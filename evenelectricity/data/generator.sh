#!/bin/bash
USE_SCORING=0
. ../testdata_tools/gen.sh

# ulimit -s unlimited

use_solution nils.cpp

compile gen_random.py

MAXN=100000
MAXW=1000000000

sample 1
#sample 2

tc small-01 gen_random n=1 r=10 maxW=10 maxS=10
tc small-02 gen_random n=2 r=10 maxW=10 maxS=10
tc small-03 gen_random n=10 r=10 maxW=10 maxS=10
tc small-04 gen_random n=10 r=10 maxW=10 maxS=10
tc small-05 gen_random n=10 r=10 maxW=10 maxS=10
tc small-06 gen_random n=10 r=10 maxW=10 maxS=10
tc random-01 gen_random n=$MAXN r=$MAXW maxW=$MAXW maxS=$MAXW
tc random-02 gen_random n=$MAXN r=$MAXW maxW=$MAXW maxS=$MAXW
tc random-03 gen_random n=$MAXN r=$MAXW maxW=$MAXW maxS=$MAXW
tc random-04 gen_random n=$MAXN r=$MAXW maxW=$MAXW maxS=$MAXW
tc random-05 gen_random n=$MAXN r=10 maxW=10 maxS=10
tc_manual ../manual_tests/big-01.in
tc_manual ../manual_tests/big-02.in
tc_manual ../manual_tests/big-03.in
tc_manual ../manual_tests/big-04.in
tc_manual ../manual_tests/big-05.in
tc_manual ../manual_tests/big-06.in
tc_manual ../manual_tests/big-07.in
tc_manual ../manual_tests/big-08.in
tc_manual ../manual_tests/big-09.in
tc droughts-01 gen_random n=$MAXN r=$MAXW maxW=$MAXW maxS=$MAXW dry=1
tc droughts-02 gen_random n=$MAXN r=$MAXN maxW=$MAXN maxS=$MAXN dry=2
tc droughts-03 gen_random n=$MAXN r=$MAXW maxW=$MAXW maxS=$MAXW dry=4
tc droughts-04 gen_random n=$MAXN r=$MAXN maxW=$MAXN maxS=$MAXN dry=10
tc droughts-05 gen_random n=$MAXN r=$MAXW maxW=$MAXW maxS=$MAXW dry=100
tc droughts-06 gen_random n=$MAXN r=$MAXN maxW=$MAXN maxS=$MAXN dry=10000
tc droughts-07 gen_random n=$MAXN r=$MAXW maxW=$MAXW maxS=$MAXW dry=30000
tc heatwaves-01 gen_random n=$MAXN r=50000 maxW=10000 maxS=10000 sun=1
tc heatwaves-02 gen_random n=$MAXN r=50000 maxW=10000 maxS=10000 sun=2
tc heatwaves-03 gen_random n=$MAXN r=50000 maxW=10000 maxS=10000 sun=4
tc heatwaves-04 gen_random n=$MAXN r=50000 maxW=10000 maxS=10000 sun=10
tc heatwaves-05 gen_random n=$MAXN r=50000 maxW=10000 maxS=10000 sun=100
tc heatwaves-06 gen_random n=$MAXN r=50000 maxW=10000 maxS=10000 sun=10000
tc heatwaves-07 gen_random n=$MAXN r=50000 maxW=10000 maxS=10000 sun=30000
tc heatwaves-08 gen_random n=$MAXN r=$MAXN maxW=$MAXN maxS=$MAXN dry=300 sun=600