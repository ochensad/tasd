#ifndef TREE_T
#define TREE_T

#include "struct.h"
#include "errors.h"

int fill_tree_by_file(tree_node_t **tree, const char *filename);
void print_tree(const tree_node_t *root, int step);
tree_node_t* find_tree(tree_node_t *root, const int num, int *compare_num);
tree_node_t *create_node(const int elem);
#endif