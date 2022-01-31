#include "menu.h"
#include <stdio.h>

int read_file_name(char *name)
{
    int error_code;
    printf("\nВведите имя файла: ");
    error_code = scanf("%s", name);
    if (error_code != 1)
    {
        printf("Ошибка чтения имени файла\n");
        return ERROR_READING;
    }
    return OK;
}

int get_comand(int *comand)
{
    printf("Команды:\n"
            "1 - Печать бинарного дерева;\n"
            "2 - Печать сбалансированного бинарного дерева;\n"
            "3 - Печать хеш-таблицы;\n"
            "4 - Поиск указанного числа;\n"
            "5 - Сравнение операции поиска по времени и по памяти. Вывод количества сравнений.\n\n"
            "0 - Выход из программы\n");
    printf("\nВыбор: ");
    if (scanf("%d", comand) != 1)
    {
        printf("Ошибка при чтении команды\n");
        return ERROR_READING;
    }
    else if (*comand < 0 || *comand > 5)
    {
        printf("Ошибка недопустимая команда\n");
        return ERROR_COMAND;
    }
    printf("\n\n");
    return OK;
}

int find_comand(tree_node_t *root, tree_node_t *root_b, hash_table_t *table, char *file_name)
{
    //int error_code;
    int comp_num = 0;
    printf("\nВыбор структуры для поиска: \n"
            "1 - бинарное дерево\n"
            "2 - сбалансированное дерево\n"
            "3 - хеш-таблица\n"
            "4 - файл\n");
    int comand;
    if (scanf("%d", &comand) != 1 || comand < 1 || comand > 4)
    {
        printf("Ошибка чтения команды\n");
        return ERROR_READING;
    }

    int num;
    printf("\nВведите число: ");
    if (scanf("%d", &num) != 1)
    {
        printf("Ошибка чления числа\n");
        return ERROR_READING;
    }
    printf("     Число      | Кол-во сравнений |\n");
    if (comand == 1)
    {
        tree_node_t *find_node = find_tree(root, num, &comp_num);
        if (find_node == NULL)
        {
            printf("Число не найдено|%18d|\n", comp_num);
            return OK;
        }
        printf("%16d|%18d|\n", find_node->num, comp_num);
    }
    else if (comand == 2)
    {
        tree_node_t *find_node = find_tree(root_b, num, &comp_num);
        if (find_node == NULL)
        {
            printf("Число не найдено|%18d|\n", comp_num);
            return OK;
        }
        printf("%16d|%18d|\n", find_node->num, comp_num);
    }
    else if (comand == 3)
    {
        if (table->table == NULL)
        {
            printf("Таблица не заполнена\n");
            return OK;
        }
        int comp;
        printf("\nВведите максимальное количество сравнений: ");
        if (scanf("%d", &comp) != 1 || comp <= 0)
        {
            printf("\n");
            return OK;
        }

        table_node_t *find_no = find_table(*table, num, &comp_num);

        while (comp_num > comp)
        {
            *table = get_new_table(table);
            comp_num = 0;
            find_no = find_table(*table, num, &comp_num);
        }

        if (find_no == NULL)
        {
            printf("Число не найдено|%18d|\n", comp_num);
            return OK;
        }
        printf("%16d|%18d|\n", find_no->value, comp_num);
    }
    else if (comand == 4)
    {
        FILE *f;
        f = fopen(file_name, "r");
        if (f == NULL)
        {
            printf("\n");
            return ERROR_OPEN_FILE;
        }
        int n;
        while (fscanf(f, "%d", &n) != EOF && n != num)
        {
            comp_num++;
        }
        if (n != num)
        {
            printf("Число не найдено|%18d|\n", comp_num);
        }
        else
        {
            printf("%16d|%18d|\n", n, comp_num);
        }
        fclose(f);
    }
    return OK;
}