#ifndef MY_STACK_L
#define MY_STACK_L

#include "struct.h"
#include "menu.h"
#define MAX_LIST_LEN 1500

int get_stack_list(void);
void free_stack(el_stack_list_t **elem_stack_list);
int add_elems_list_random(el_stack_list_t **el, int n);
int count_del_list_elems(int *num, el_stack_list_t *el_stack);
void del_elems_list(el_stack_list_t **el, int n);
void print_list(el_stack_list_t **el);
int check_palindrom_list(el_stack_list_t **stack_cur, stack_list_t *arr);
#endif