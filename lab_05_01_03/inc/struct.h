#ifndef MY_STRUCT
#define MY_STRUCT

#include <stdint.h>

#define MAX_TURN_LEN 1000

typedef struct
{
    double time;
    int type;
    int value;
}elem_t;

typedef struct
{
    elem_t *arr;
    elem_t *head;
    elem_t *tail;
    int size;
    int max_size;
} array_turn_t;

typedef struct node_turn
{
    elem_t data;
    struct node_turn *next;
} node_turn_t;

typedef struct
{
    node_turn_t *head;
    node_turn_t *tail;
    size_t size;
} list_turn_t;

typedef struct
{
    node_turn_t **arr;
    size_t size;
} arr_free_areas_t;

#endif