#!/bin/bash
g++ longestv1.cpp -o lcs -O2 -fopenmp
g++ sequence.cpp -o sequence -O1
sh run.sh
