#ifndef MY_STRUCT
#define MY_STRUCT

typedef struct
{
    int **matrix;
    int rows;
    int columns;
} matrix_t;

typedef struct
{
    int *vect_a;
    int *vect_ja;
    int *linked_list_ia;
    int rows;
    int columns;
    int elems;
} sparse_matrix_t;

#endif