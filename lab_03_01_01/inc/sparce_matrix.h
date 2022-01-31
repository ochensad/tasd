#ifndef SPARCE_T
#define SPARCE_T

#include "errors.h"
#include "struct.h"

int read_matrix_size(int *rows, int *columns);
int sparce_addition(void);

int res_size(sparse_matrix_t *mat_1, sparse_matrix_t *mat_2);
void addition_matrix_sparce(sparse_matrix_t *res_mat, sparse_matrix_t *mat_1, sparse_matrix_t *mat_2);
int random_sparce_matrix(sparse_matrix_t *matrix);
void free_sparce_matrix(sparse_matrix_t *matrix);
int create_sparce_matrix(sparse_matrix_t *matrix);
void sort_matrix(sparse_matrix_t *matrix);
void print_sparce_matrix(sparse_matrix_t *matrix);
void addition_sparce(sparse_matrix_t *res, sparse_matrix_t *a, sparse_matrix_t *b);
void res_mat(sparse_matrix_t *res, sparse_matrix_t *a, sparse_matrix_t *b);
#endif