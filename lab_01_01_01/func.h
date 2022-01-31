#ifndef MY_FUNC
#define MY_FUNC

#include "real.h"
#include "int_num.h"

void zeros_in_massive(num_t *num);
int normalization(num_t *data, size_t *n);
int move_num_end(num_t *data, size_t *n);
void move_digits(num_t *num, int size, int offset);
int division(num_t *real, num_t *integer, num_t *result, int size);

#endif