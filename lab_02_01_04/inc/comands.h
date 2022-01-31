#ifndef COMAND
#define COMAND

#include "records.h"
#include "errors.h"
#include "sort.h"
#include <string.h>
#include <time.h>

int load_table(char *file_name, size_t max_size, table_t *table);
int print_table(table_t *table);
int add_car(table_t *table);
int delite_cars(table_t *table);
int print_task(table_t *table);
int print_keys(table_t *table);
void get_keys(table_t *table);
int print_sorted_keys_table(table_t *table);
int timer_sort(table_t *table);

#endif