#!/bin/sh
rm *.o *.exe
gcc -Wall -Werror -Wpedantic -Wextra -c main.c
gcc -Wall -Werror -Wpedantic -Wextra -c func.c
gcc -Wall -Werror -Wpedantic -Wextra -c real.c
gcc -Wall -Werror -Wpedantic -Wextra -c int_num.c
gcc main.o real.o func.o int_num.o -o app.exe
