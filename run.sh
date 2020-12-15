#!/bin/bash
LEN=1000
./sequence $LEN $LEN
# export OMP_NUM_THREADS=1

for i in {0..4..1}
do 
    echo $i
    export OMP_NUM_THREADS=$i
    sudo perf stat ./lcs text1.dat text2.dat $LEN $LEN
done