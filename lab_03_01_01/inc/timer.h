#ifndef TIMER
#define TIMER

#include "matrix.h"
#include "sparce_matrix.h"

#define HZ 2300000000
#define NUMBER_OF_RUNS 3000

#define NUMBER_ROWS_1 10
#define NUMBER_COLUMNS_1 10

#define NUMBER_ROWS_2 50
#define NUMBER_COLUMNS_2 50

#define NUMBER_ROWS_3 100
#define NUMBER_COLUMNS_3 100

#define FILL_PERCENTAGE_1 10
#define FILL_PERCENTAGE_2 15
#define FILL_PERCENTAGE_3 50
#define FILL_PERCENTAGE_4 75
#define FILL_PERCENTAGE_5 95


int comparison_time_memory(void);

#endif