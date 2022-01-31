rm *.o *.exe
gcc -Wall -Werror -Wpedantic -Wextra -g3 -c main.c
gcc -Wall -Werror -Wpedantic -Wextra -g3 -c func.c
gcc -Wall -Werror -Wpedantic -Wextra -g3 -c real.c
gcc -Wall -Werror -Wpedantic -Wextra -g3 -c int_num.c
gcc main.o real.o func.o int_num.o -o app.exe