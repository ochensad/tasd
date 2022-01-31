#ifndef B_TREE_T
#define B_TREE_T

#include "errors.h"
#include "struct.h"
#include "tree.h"
#include <stdio.h>

tree_node_t *create_tree_balance(FILE *f, tree_node_t *tree);

#endif