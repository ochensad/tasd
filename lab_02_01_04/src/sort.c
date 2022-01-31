#include "../inc/sort.h"

int comp(const keys_t *a, const keys_t *b)
{
    return(a->key - b->key);
}

int sort_keys_qsort(table_t *table)
{

    qsort(table->keys, table->size, sizeof(keys_t), (int(*) (const void *, const void *)) comp);

    return OK;
}

int sort_keys_bubble(table_t *table)
{
    keys_t buf;
    for (size_t i = 0; i < table->size; i++)
        for (size_t j = i; j < table->size - 1; j++)
        {
            if (table->keys[j].key > table->keys[j + 1].key)
            {
                buf = table->keys[j];
                table->keys[j] = table->keys[j + 1];
                table->keys[j + 1] = buf;
            }
        }
    return OK;
}

int comp_t(const car_t *a, const car_t *b)
{
    return(a->price - b->price);
}

int sort_table_qsort(table_t *table)
{
    qsort(table->cars, table->size, sizeof(car_t), (int(*) (const void *, const void *)) comp_t);

    return OK;
}

int sort_table_bubble(table_t *table)
{
    car_t buf;
    for (size_t i = 0; i < table->size; i++)
        for (size_t j = 0; j < table->size - 1; j++)
        {
            if (table->cars[j].price > table->cars[j + 1].price)
            {
                buf = table->cars[j];
                table->cars[j] = table->cars[j + 1];
                table->cars[j + 1] = buf;
            }
        }
    
    return OK;
}