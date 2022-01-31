#include "dot.h"
#include <stdio.h>

void convert_node_to_dot(tree_node_t *node, FILE *f)
{
    if (node->left)
        fprintf(f, "%d -> %d;\n", node->num, node->left->num);
    if (node ->right)
        fprintf(f, "%d -> %d;\n", node->num, node->right->num);
}

void print_by_pred(tree_node_t *root, FILE *f)
{
    if (root == NULL)
        return;
    convert_node_to_dot(root, f);
    print_by_pred(root->left, f);
    print_by_pred(root->right, f);
}

void print_tree_to_file(tree_node_t *root, const char *file_name)
{
    FILE *f_out;
    f_out = fopen(file_name, "w");
    if (f_out == NULL)
    {
        printf("Ошибка при открытии файла для записи\n");
        return;
    }

    fprintf(f_out, "digraph tree {\n");
    print_by_pred(root, f_out);
    fprintf(f_out, "}\n");

    fclose(f_out);
}