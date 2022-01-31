#ifndef MY_MENU
#define MY_MENU

#include "errors.h"
#include <stdio.h>

#define MIN_COMAND 0
#define MAX_COMAND 12

void print_menu(void);
int get_comand(int *comand);
#endif