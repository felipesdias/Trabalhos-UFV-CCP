#!/bin/bash

nvprof ./sum.out 25 512 1 0 > Analise-32M-R.txt 2>&1
nvprof ./sum.out 26 512 1 0 > Analise-64M-R.txt 2>&1
nvprof ./sum.out 27 512 1 0 > Analise-128M-R.txt 2>&1
nvprof ./sum.out 28 512 1 0 > Analise-256M-R.txt 2>&1

nvprof ./sum.out 25 512 1 1 > Analise-32M-I.txt 2>&1
nvprof ./sum.out 26 512 1 1 > Analise-64M-I.txt 2>&1
nvprof ./sum.out 27 512 1 1 > Analise-128M-I.txt 2>&1
nvprof ./sum.out 28 512 1 1 > Analise-256M-I.txt 2>&1
