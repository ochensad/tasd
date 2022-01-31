#ifndef ARR_T
#define ARR_T

#include "struct.h"
#include "errors.h"

int count_add_elems_array_turn(int *num, int size);
int count_del_elems_array_turn(int *num, int size);
void del_elems_array_turn(array_turn_t *turn, int n);
void random_elems_array_turn(array_turn_t *turn, int n);
int add_elems_array_turn(array_turn_t *turn, int n);
void print_arr(array_turn_t *turn);

int push_turn_array(array_turn_t *turn, elem_t el);
int pop_turn_array(array_turn_t *turn, elem_t *el);
#endif