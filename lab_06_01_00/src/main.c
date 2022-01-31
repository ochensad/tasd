#include <stdio.h>
#include "errors.h"
#include "menu.h"
#include "tree.h"
#include "balance_tree.h"
#include "dot.h"
#include "table.h"
#include "compare.h"
#include <stdlib.h>
#define MAX_FILE_NAME_LEN 25



int main(void)
{
    int error_code;
    int comand;

    setbuf(stdout, NULL);

    char file_name[MAX_FILE_NAME_LEN + 1];
    error_code = read_file_name(file_name);
    if (error_code)
        return error_code;
    tree_node_t *root = NULL;
    int file_len = fill_tree_by_file(&root, file_name);

    if (file_len <= 0)
        return file_len;
    //int b_lines;
    FILE *f;
    f = fopen(file_name, "r");
    tree_node_t *balance_root = NULL;
    balance_root = create_tree_balance(f, balance_root);
    fclose(f);

    root = NULL;
    file_len = fill_tree_by_file(&root, file_name);
    print_tree_to_file(balance_root, "b_tree.gv");
    print_tree_to_file(root, "tree.gv");

    hash_table_t table;
    table.table = NULL;
    table.size = file_len;

    error_code = get_table(&table, file_name);
    if (error_code < 0)
        return error_code;
    
    int flag = 1;
    while (flag)
    {
        error_code = get_comand(&comand);
        if (error_code != OK)
            return error_code;
        
        if (comand == 1)
        {
            print_tree_to_file(root, "tree.gv");
            print_tree(root, 4);
            system("dot -Tpng tree.gv -o tree.png");
            system("start tree.png");
        }
        else if (comand == 2)
        {
            print_tree_to_file(balance_root, "b_tree.gv");
            print_tree(balance_root, 4);
            system("dot -Tpng b_tree.gv -o b_tree.png");
            system("start b_tree.png");
        }
        else if (comand == 3)
        {
            print_table(table);
            
        }
        else if (comand == 4)
        {
            find_comand(root, balance_root, &table, file_name);
        }
        else if (comand == 5)
        {
            compare("test_10.txt");
            compare("test_100.txt");
            compare("test_250.txt");
            compare("test_500.txt");
            compare("test_1000.txt");
        }
        else if (comand == 0)
            flag = 0;
    }
    
    return OK;
}