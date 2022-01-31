#ifndef MY_STRUCT
#define MY_STRUCT

typedef struct
{
    int *arr;
    int size;
} stack_array_t;

typedef struct el_stack_list
{
    int el;
    int i_el;
    struct el_stack_list *next;
} el_stack_list_t;

typedef struct
{
    el_stack_list_t **arr;
    int size;
} stack_list_t;

#endif