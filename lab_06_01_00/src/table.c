#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prime(int num)
{
    if (num <= 1)
        return 0;
    if (num % 2 == 0 && num > 2)
        return 0;
    
    for (int i = 3; i <= floor(sqrt(num)); i += 2)
        if (num % i == 0)
            return 0;
    return 1;
}

int get_prime(int num)
{
    while ((num > 2) && !is_prime(num))
        num--;
    return num;
}

int get_next_prime(int num)
{
    while ((num > 2) && !is_prime(num))
        num++;
    return num;
}

int hash_f(int size, int coef)
{
    int prime_num = get_prime(size + coef);
    //printf("~%d~", prime_num);
    //printf("%d", num % prime_num);
    return prime_num;
}

hash_table_t get_new_table(hash_table_t *table)
{
    hash_table_t new;
    new.table = NULL;
    new.size = table->size;
    new.hash = get_next_prime(table->hash + 1);

    new.table = malloc((new.hash) * sizeof(table_node_t*));

    for (int i = 0; i < new.hash; i++)
        (new.table)[i] = NULL;
    
    int max_collisions = 0;
    int key = 0;
    table_node_t *cur;

    for (int i = 0; i < table->hash; i++)
    {
        int cur_collisions = 0;

        cur = table->table[i];

        while (cur)
        {
            key = cur->value % new.hash;

            cur_collisions = 1;
            if (!(new.table)[key])
            {
                (new.table)[key] = malloc(sizeof(table_node_t));
                (new.table)[key]->value = cur->value;
                (new.table)[key]->next = NULL;
                cur_collisions = 1;
            }
            else
            {
                table_node_t *tmp = (new.table)[key];
                while (tmp->next)
                {
                    cur_collisions++;
                    tmp = tmp->next;
                }

                table_node_t *new_node = malloc(sizeof(table_node_t));
                new_node->next = NULL;
                new_node->value = cur->value;
                tmp->next = new_node;
            }

            if (cur_collisions > max_collisions)
                max_collisions = cur_collisions;
            cur = cur->next;
        }
    }

    return new;
}
int get_table(hash_table_t *table, char *file_name)
{
    FILE *f;
    f = fopen(file_name, "r");
    if (f == NULL)
    {
        printf("\n");
        return ERROR_OPEN_FILE;
    }
    table->hash = hash_f(table->size, 0);
    table->table = malloc((table->hash) * sizeof(table_node_t*));

    for (int i = 0; i < table->hash; i++)
        (table->table)[i] = NULL;
    
    int num = 0;
    int max_collisions = 0;
    int key = 0;
    

    while (fscanf(f, "%d", &num) != EOF)
    {
        int cur_collisions = 0;

        key = num % table->hash;

        cur_collisions = 1;
        if (!(table->table)[key])
        {
            (table->table)[key] = malloc(sizeof(table_node_t));
            (table->table)[key]->value = num;
            (table->table)[key]->next = NULL;
            cur_collisions = 1;
        }
        else
        {
            table_node_t *tmp = (table->table)[key];
            while (tmp->next)
            {
                cur_collisions++;
                tmp = tmp->next;
            }

            table_node_t *new = malloc(sizeof(table_node_t));
            new->next = NULL;
            new->value = num;
            tmp->next = new;
        }

        if (cur_collisions > max_collisions)
            max_collisions = cur_collisions;
    }
    fclose(f);
    return max_collisions;
}

void print_table(hash_table_t table)
{
    printf("\n\n  хеш    |   данные  \n");

    table_node_t *cur_list;

    printf("_______________________\n");
    for (int i = 0; i < table.hash; i++)
    {
        cur_list = table.table[i];

        if (cur_list)
            printf("%4d     | ", i);
        else
            printf("%4d     | \n", i);
        
        while (cur_list)
        {
            printf("\"%d\" ", cur_list->value);
            cur_list = cur_list->next;

            if (!cur_list)
                printf("\n");
        }
    }
}

table_node_t *find_table(hash_table_t table, int num, int *comp_num)
{
    int key = num % table.hash;
    table_node_t *cur;
    cur = table.table[key];
    while (cur)
    {
        *comp_num += 1;
        if (cur->value == num)
            return cur;
        cur = cur->next;
    }
    return cur;
}