#ifndef MY_SORT
#define MY_SORT

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "records.h"
#include "comands.h"

int sort_keys_qsort(table_t *table);
int sort_keys_bubble(table_t *table);
int sort_table_qsort(table_t *table);
int sort_table_bubble(table_t *table);

#endif