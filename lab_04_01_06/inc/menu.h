#ifndef MY_MENU
#define MY_MENU

#include <stdio.h>
#include "errors.h"

#define MIN_COM 0
#define MAX_COM 5

int read_type(int *s_type);
int read_comand(int *comand);
void print_menu(void);
#endif