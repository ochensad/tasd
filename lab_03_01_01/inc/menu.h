#ifndef MENU
#define MENU

#include "errors.h"
#include <stdio.h>

#define MIN_COMAND 0
#define MAX_COMAND 3
void print_menu(void);
int get_comand(int *comand);
#endif