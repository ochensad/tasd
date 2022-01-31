#ifndef MY_STACK_A
#define MY_STACK_A

#include "struct.h"
#include "menu.h"


#define MAX_LEN 5000

int get_stack_array(void);
int count_add_elems(int *num, stack_array_t *stack);
int add_random_elems_array(int elems, stack_array_t *stack);
int del_elems_array(int elems, stack_array_t *stack);
int count_del_elems(int *num, stack_array_t *stack);
void print_array_stack(stack_array_t *stack);
int check_palindrom(stack_array_t *stack);
#endif