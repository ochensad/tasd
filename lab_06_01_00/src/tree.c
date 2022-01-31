#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

tree_node_t *create_node(const int elem)
{
    tree_node_t *node = malloc(sizeof(tree_node_t));

    if (node)
    {
        node->num = elem;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

tree_node_t *insert_tree(tree_node_t *tree, tree_node_t *node)
{
    int cmp;
    if (tree == NULL)
        return node;
    cmp = node->num - tree->num;

    if (cmp == 0)
        assert(0);
    else if (cmp < 0)
        tree->left = insert_tree(tree->left, node);
    else
        tree->right = insert_tree(tree->right, node);
    return tree;
}

int fill_tree_by_file(tree_node_t **tree, const char *filename)
{
    int error_code;
    FILE *f;

    f = fopen(filename, "r");
    if (!f)
    {
        printf("Ошибка при открытии файла\n");
        return ERROR_OPEN_FILE;
    }

    int value;
    int i = 0;
    for (; !feof(f); i++)
    {
        if ((error_code = fscanf(f, "%d", &value)) != 1)
        {
            printf("Ошибка при чтении из файла\n");
            return ERROR_READING_FILE;
        }

        tree_node_t *new_node = create_node(value);
        if (new_node == NULL)
        {
            printf("Ошибка выделения памяти\n");
            return ERROR_MEMORY;
        }

        *tree = insert_tree(*tree, new_node);
    }
    fclose(f);
    return i;
}

void print_tree(const tree_node_t *root, int step)
{
    if (root)
    {
        print_tree(root->right, step + 4);
        for (int i = 0; i < step; i++)
            printf(" ");
        if (root->num)
            printf("%d\n", root->num);
        print_tree(root->left, step + 4);
    }
}

tree_node_t* find_tree(tree_node_t *root, const int num, int *compare_num)
{
    int cmp;
    while (root != NULL)
    {
        cmp = num - root->num;
        *compare_num += 1;
        if (cmp == 0)
            return root;
        else if (cmp < 0)
            root = root->left;
        else if (cmp > 0)
            root = root->right;
    }
    return NULL;
}
