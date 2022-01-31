#include "compare.h"
#include <stdlib.h>

void print_result(int64_t start, int64_t end)
{
    printf("%lld тактов, %.10lf секунд\n", end - start, (double)(end - start) / HZ);  
}

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

int compare(char *file_name)
{
    int error_code;
    int64_t start = 0, end = 0;

    FILE *f;
    f = fopen(file_name, "r");
    if (f == NULL)
    {
        printf("Ошибка открытия файла\n");
        return ERROR_OPEN_FILE;
    }
    int num = 0;
    int comp_num_tree = 0;

    tree_node_t *root = NULL;
    int file_len = fill_tree_by_file(&root, file_name);
    if (file_len <= 0)
        return file_len;
    printf("\nРазмер дерева %d\n", file_len);

    int ang_tree_comp = 0;

    for (int i = 0; i < RUNS; i++)
    {
        num = rand() % (10000);

        start += tick();
        find_tree(root, num, &comp_num_tree);
        end += tick();
        ang_tree_comp += comp_num_tree;
        comp_num_tree = 0;
    }

    printf("\x1B[33m    Поиск элемента в ДДП\x1B[0m\n\n");
    printf("Среднее количество сравлений: %d\n", ang_tree_comp / RUNS);
    print_result(start / RUNS, end / RUNS);
    printf("\n");



    start = 0;
    end = 0;

    rewind(f);
    int b_lines = file_len;
    tree_node_t *balance_root = NULL;
    balance_root = create_tree_balance(f, balance_root);
    printf("\nРазмер сбалансированного дерева %d\n", b_lines);

    comp_num_tree = 0;
    int avg_b_tree_comp = 0;
    for (int i = 0; i < RUNS; i++)
    {
        num = rand() % (10000);

        start += tick();
        find_tree(balance_root, num, &comp_num_tree);
        end += tick();
        avg_b_tree_comp += comp_num_tree;
        comp_num_tree = 0;
    }

    printf("\x1B[33m    Поиск элемента в АВЛ\x1B[0m\n\n");
    printf("Среднее количество сравлений: %d\n", avg_b_tree_comp / RUNS);
    print_result(start / RUNS, end / RUNS);
    printf("\n");

    start = 0;
    end = 0;

    rewind(f);

    hash_table_t table;
    table.table = NULL;
    table.size = file_len;
    error_code = get_table(&table, file_name);
    if (error_code < 0)
        return error_code;
    printf("\nРазмер хеш-таблицы %d\n", table.size - 1);

    int comp_num = 0;
    int avg_table_comp = 0;
    for (int i = 0; i < RUNS; i++)
    {
        num = rand() % (10000);

        start += tick();
        find_table(table, num, &comp_num);
        end += tick();
        avg_table_comp += comp_num;
        comp_num = 0;
    }

    printf("\x1B[33m    Поиск элемента в хеш-таблице\x1B[0m\n\n");
    printf("Среднее количество сравлений: %d\n", avg_table_comp / RUNS);
    print_result(start / RUNS, end / RUNS);
    printf("\n");

    
    rewind(f);
    start = 0;
    end = 0;
    int n;
    int avg_file = 0;
    for (int i = 0; i < RUNS; i++)
    {
        start += tick();
        while (fscanf(f, "%d", &n) != EOF && n != num)
        {
            comp_num++;
        }
        end += tick();
        avg_file += comp_num;
        comp_num = 0;
        rewind(f);
    }

    printf("\x1B[33m    Поиск элемента в файле\x1B[0m\n\n");
    printf("Среднее количество сравлений: %d\n", avg_file / RUNS);
    print_result(start / RUNS, end / RUNS);
    printf("\n");


    printf("\x1B[33m    Занимаемая память\x1B[0m\n\n");
    printf("    ДДП - %zu\n", sizeof(tree_node_t) * file_len);
    printf("    АВЛ - %zu\n", sizeof(tree_node_t) * file_len);
    printf("    Хеш-таблицы - %zu\n", sizeof(table) + sizeof(table_node_t) * table.size + sizeof(table_node_t) * table.hash + sizeof(table.table) + sizeof(**table.table));

    rewind(f);
    while (fscanf(f, "%d", &num) != EOF)
        num++;
    long size_file = ftell(f);
    printf("    Файла - %lu\n\n", size_file);

    fclose(f);
    return OK;
}