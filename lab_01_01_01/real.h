#ifndef MY_REAL
#define MY_REAL

#include <stdio.h>

#include "struct.h"
#include "errors.h"

int is_real(real_t string, num_t *real, size_t *man_r);
int read_real(real_t s);

#endif