#!/bin/bash

g++ -Wall -pg matriz.cpp -o main

./main 14
gprof main gmon.out > analise-16K.txt

./main 15
gprof main gmon.out > analise-32K.txt

./main 17
gprof main gmon.out > analise-128K.txt

./main 18
gprof main gmon.out > analise-256K.txt

./main 20
gprof main gmon.out > analise-1M.txt

./main 24
gprof main gmon.out > analise-16M.txt

./main 26
gprof main gmon.out > analise-64M.txt

./main 27
gprof main gmon.out > analise-128M.txt
