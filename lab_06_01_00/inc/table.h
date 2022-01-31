#ifndef TABLE_T
#define TABLE_T

#include "struct.h"
#include "errors.h"

int get_table(hash_table_t *table, char *file_name);
void print_table(hash_table_t table);
table_node_t *find_table(hash_table_t table, int num, int *comp_num);
hash_table_t get_new_table(hash_table_t *table);

#endif