#ifndef MENU_T
#define MENU_T

#include "errors.h"
#include "table.h"
#include "tree.h"

int read_file_name(char *name);
int get_comand(int *comand);
int find_comand(tree_node_t *root, tree_node_t *root_b, hash_table_t *table, char *file_name);
#endif