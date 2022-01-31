#ifndef MY_MATRIX
#define MY_MATRIX

#include "sparce_matrix.h"

int simple_addition(void);
int random_simple_matrix(matrix_t *matrix, int fill_size);
void addition_simple(matrix_t *res_matrix,matrix_t *matrix, matrix_t *matrix_2);
int create_simple_matrix(matrix_t *matrix);
void free_matrix(int **arr, int n);
#endif