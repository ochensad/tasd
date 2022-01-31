#include <stdio.h>

#include "../inc/menu.h"
#include "../inc/comands.h"
#include "../inc/sort.h"

int main(void)
{
    printf("\nПрограмма для обработки таблицы машин\n");
    //Отмена буферизации для корректной работы printf
    setbuf(stdout, NULL);

    int error_code;
    int comand;
    char file[] = "data2000.txt";

    int flag = 1;
    table_t table;
    
    while (flag)
    {
        print_menu();

        error_code = get_comand(&comand);

        if (error_code)
            return error_code;
        
        if (comand == 1)
        {
            error_code = load_table(file, MAX_TABLE_SIZE, &table);

            if (error_code)
                flag = 0;
        }
        if (comand == 2)
        {
            error_code = print_table(&table);
            if (error_code)
                flag = 0;
        }
        if (comand == 3)
        {
            error_code = add_car(&table);
            if (error_code)
                flag = 0;
        }
        if (comand == 4)
        {
            error_code = delite_cars(&table);
            if (error_code)
                flag = 0;
        }
        if (comand == 5)
        {
            error_code = print_task(&table);
            if (error_code)
                flag = 0;
        }
        if (comand == 6)
        {
            error_code = print_keys(&table);
            if (error_code)
                flag = 0;
        }
        if (comand == 7)
        {
            error_code = sort_keys_qsort(&table);
            if (error_code)
                flag = 0;
        }
        if (comand == 8)
        {
            error_code = sort_keys_bubble(&table);
            if (error_code)
                flag = 0;
        }
        if (comand == 9)
        {
            error_code = sort_table_qsort(&table);
            if (error_code)
                flag = 0;
        }
        if (comand == 10)
        {
            error_code = sort_table_bubble(&table);
            if (error_code)
                flag = 0;
        }
        if (comand == 11)
        {
            error_code = print_sorted_keys_table(&table);
            if (error_code)
                flag = 0;
        }
        if (comand == 12)
        {
            error_code = timer_sort(&table);
            if (error_code)
                flag = 0;
        }
        else if (comand == 0)
            flag = 0;
    }

    return error_code;
}