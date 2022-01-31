#ifndef MY_STRUCT
#define MY_STRUCT

typedef struct tree_node tree_node_t;
struct tree_node
{
    int num;
    int height;
    tree_node_t *left;
    tree_node_t *right;
};


typedef struct
{
    tree_node_t **buf;
    int size;
    int step;
}buf_t;

typedef struct table_node
{
    int value;
    struct table_node *next;
} table_node_t;

typedef struct
{
    table_node_t **table;
    int size;
    int hash;
} hash_table_t;

#endif