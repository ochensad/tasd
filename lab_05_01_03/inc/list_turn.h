#ifndef LIST_T
#define LIST_T

#include "struct.h"
#include "errors.h"

int push_turn_list(list_turn_t *turn, elem_t el, size_t max_size);
int pop_turn_list(list_turn_t *turn, elem_t *el);
void free_list(list_turn_t *turn);
int add_elems_list_turn(list_turn_t *turn, int n);
void del_elems_list_turn(list_turn_t *turn, int n);
int random_elems_list_turn(list_turn_t *turn, int n);
int get_array_of_freed_areas(arr_free_areas_t *arr, int n, list_turn_t *turn);
void print_list(list_turn_t *turn);
void print_f_arr(arr_free_areas_t *arr);
#endif