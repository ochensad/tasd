#include "balance_tree.h"
#include <stdlib.h>
#include <stdio.h>

// нахождение высоты элемента
size_t height(tree_node_t *elem)
{
    if (elem)
        return elem->height;
    return 0;
}

// вычисление balance factor
int bfactor(tree_node_t *elem)
{
    return height(elem->right)-height(elem->left);
}

// восстановление высоты
void fix_height(tree_node_t *elem)
{
    size_t hl = height(elem->left);
    size_t hr = height(elem->right);
    if (hl > hr)
        elem->height = hl + 1;
    else
        elem->height = hr + 1;
}

// правый поворот
tree_node_t *rotate_right(tree_node_t *elem)
{
    tree_node_t *tmp = elem->left;
    elem->left = tmp->right;
    tmp->right = elem;
    fix_height(elem);
    fix_height(tmp);
    return tmp;
}

// левый поворот
tree_node_t *rotate_left(tree_node_t *elem)
{
    tree_node_t *tmp = elem->right;
    elem->right = tmp->left;
    tmp->left = elem;
    fix_height(elem);
    fix_height(tmp);
    return tmp;
}

// сама балансировка узла
tree_node_t *balance(tree_node_t *elem)
{
    fix_height(elem);
    if (bfactor(elem) == 2)
    {
        if (bfactor(elem->right) < 0)
            elem->right = rotate_right(elem->right);
        return rotate_left(elem);
    }
    if (bfactor(elem) == -2)
    {
        if (bfactor(elem->left) > 0)
            elem->left = rotate_left(elem->left);
        return rotate_right(elem);
    }
    return elem;
}

// вставка узла в АВЛ-дерево
tree_node_t *insert_balance(tree_node_t *tree, tree_node_t *node)
{
    int cmp;
    if (tree == NULL)
        return node;
    
    cmp = tree->num - node->num;

    if (cmp > 0)
    {
        tree->left = insert_balance(tree->left, node);
        tree = balance(tree);
    }
    else if (cmp < 0)
    {
        tree->right = insert_balance(tree->right, node);
        tree = balance(tree);
    }

    tree = balance(tree);
    return tree;
}

// создание АВЛ-дерева
tree_node_t *create_tree_balance(FILE *f, tree_node_t *tree)
{
    tree_node_t *node;
    int data;
    while (fscanf(f, "%d", &data) != EOF)
    {
        node = create_node(data);
        tree = insert_balance(tree, node);
    }
    rewind(f);
    return tree;
}