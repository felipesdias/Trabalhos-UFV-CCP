#!/bin/bash

# Everything times out after 12h

g++ -Wall matriz.cpp -O0 -o main

echo 'For a 32k cache'

timeout 43200 valgrind --tool=cachegrind --D1=32768,8,32 ./main 13 > valgrind8kcache32.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 8k'
    exit
fi
echo 'Done 8k'

timeout 43200 valgrind --tool=cachegrind --D1=32768,8,32 ./main 14 > valgrind16kcache32.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 16k'
    exit
fi
echo 'Done 16k'

timeout 43200 valgrind --tool=cachegrind --D1=32768,8,32 ./main 15 > valgrind32kcache32.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 32k'
    exit
fi
echo 'Done 32k'

timeout 43200 valgrind --tool=cachegrind --D1=32768,8,32 ./main 16 > valgrind64kcache32.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 64k'
    exit
fi
echo 'Done 64k'

timeout 43200 valgrind --tool=cachegrind --D1=32768,8,32 ./main 17 > valgrind128kcache32.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 128k'
    exit
fi
echo 'Done 128k'

timeout 43200 valgrind --tool=cachegrind --D1=32768,8,32 ./main 18 > valgrind256kcache32.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 256k'
    exit
fi
echo 'Done 256k'

timeout 43200 valgrind --tool=cachegrind --D1=32768,8,32 ./main 19 > valgrind512kcache32.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 512k'
    exit
fi
echo 'Done 512k'

echo 'Now for a 16k cache'

timeout 43200 valgrind --tool=cachegrind --D1=16384,4,32 ./main 13 > valgrind8kcache16.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 8k'
    exit
fi
echo 'Done 8k'

timeout 43200 valgrind --tool=cachegrind --D1=16384,4,32 ./main 14 > valgrind16kcache16.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 16k'
    exit
fi
echo 'Done 16k'

timeout 43200 valgrind --tool=cachegrind --D1=16384,4,32 ./main 15 > valgrind32kcache16.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 32k'
    exit
fi
echo 'Done 32k'

timeout 43200 valgrind --tool=cachegrind --D1=16384,4,32 ./main 16 > valgrind64kcache16.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 64k'
    exit
fi
echo 'Done 64k'

timeout 43200 valgrind --tool=cachegrind --D1=16384,4,32 ./main 17 > valgrind128kcache16.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 128k'
    exit
fi
echo 'Done 128k'

timeout 43200 valgrind --tool=cachegrind --D1=16384,4,32 ./main 18 > valgrind256kcache16.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 256k'
    exit
fi
echo 'Done 256k'

timeout 43200 valgrind --tool=cachegrind --D1=16384,4,32 ./main 19 > valgrind512kcache16.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 512k'
    exit
fi
echo 'Done 512k'

echo 'Now for an 8k cache'

timeout 43200 valgrind --tool=cachegrind --D1=8192,2,32 ./main 13 > valgrind8kcache8.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 8k'
    exit
fi
echo 'Done 8k'

timeout 43200 valgrind --tool=cachegrind --D1=8192,2,32 ./main 14 > valgrind16kcache8.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 16k'
    exit
fi
echo 'Done 16k'

timeout 43200 valgrind --tool=cachegrind --D1=8192,2,32 ./main 15 > valgrind32kcache8.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 32k'
    exit
fi
echo 'Done 32k'

timeout 43200 valgrind --tool=cachegrind --D1=8192,2,32 ./main 16 > valgrind64kcache8.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 64k'
    exit
fi
echo 'Done 64k'

timeout 43200 valgrind --tool=cachegrind --D1=8192,2,32 ./main 17 > valgrind128kcache8.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 128k'
    exit
fi
echo 'Done 128k'

timeout 43200 valgrind --tool=cachegrind --D1=8192,2,32 ./main 18 > valgrind256kcache8.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 256k'
    exit
fi
echo 'Done 256k'

timeout 43200 valgrind --tool=cachegrind --D1=8192,2,32 ./main 19 > valgrind512kcache8.txt 2>&1
ret=$?
if [ "$ret" -eq 124 ]
then
    echo 'Timed out 512k'
    exit
fi
echo 'Done 512k'
