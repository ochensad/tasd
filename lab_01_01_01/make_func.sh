#!/bin/sh
rm ./*.exe ./*.o
gcc -Wall -Werror -Wpedantic -Wextra -Wvla  -O0 --coverage main.c func.c real.c int_num.o -o app.exe


cd func_tests

./all_test.sh

cd ..

echo "....COVERAGE...."

gcov main.c func.c real.c int_num.c
rm -f out.txt
