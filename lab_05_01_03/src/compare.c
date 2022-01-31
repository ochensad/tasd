#include "compare.h"
#include <stdio.h>
#include <stdlib.h>

void print_res(int64_t start, int64_t end)
{
    printf("%lld тактов, %.10lf секунд\n", end - start, (double)(end - start) / SEC);
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

int compare(void)
{
    int error_code;

    list_turn_t turn_l;
    turn_l.size = 0;
    turn_l.head = NULL;
    turn_l.tail = NULL;

    arr_free_areas_t f_arr;
    f_arr.arr = NULL;
    f_arr.size = 0;

    int64_t start = 0, end = 0;

    int flag = 1;
    int comand;

    printf("\nВведите количество элементов в очереди: ");
    int turn_size;

    if (scanf("%d", &turn_size) != 1 || turn_size <= 0)
    {
        printf("Ошибка чтения\n");
        return ERROR_READING;
    }

    array_turn_t turn_a;
    turn_a.size = 0;
    turn_a.arr = malloc(sizeof(elem_t) * turn_size);
    turn_a.max_size = turn_size;
    turn_a.head = turn_a.arr;
    turn_a.tail = turn_a.arr;


    while(flag)
    {
        error_code = read_comand(&comand);
        if (error_code)
        {
            free(f_arr.arr);
            free_list(&turn_l);
            free(turn_a.arr);
            return error_code;
        }

        if (comand == 1)
        {
            int elems_add;
            if ((error_code = count_add_elems_array_turn(&elems_add, turn_a.size)) != OK)
            {
                free(f_arr.arr);
                free_list(&turn_l);
                free(turn_a.arr);
                return error_code;
            }

            printf("\nМассив:");
            if ((error_code = add_elems_array_turn(&turn_a, elems_add)) != OK)
            {
                free(f_arr.arr);
                free_list(&turn_l);
                free(turn_a.arr);
                return error_code;
            }
            printf("\nСписок:");
            if ((error_code = add_elems_list_turn(&turn_l, elems_add)) != OK)
            {
                free(f_arr.arr);
                free_list(&turn_l);
                free(turn_a.arr);
                return error_code;
            }
        }
        else if (comand == 2)
        {
            int elems_add;
            if ((error_code = count_add_elems_array_turn(&elems_add, turn_a.size)) != OK)
            {
                free(f_arr.arr);
                free_list(&turn_l);
                free(turn_a.arr);
                return error_code;
            }

            array_turn_t buf_turn;
            buf_turn.size = 0;
            buf_turn.arr = malloc(sizeof(elem_t) * elems_add);
            buf_turn.max_size = elems_add;
            buf_turn.head = buf_turn.arr;
            buf_turn.tail = buf_turn.head;

            for (int i = 0; i < 10; i++)
            {
                start += tick();
                random_elems_array_turn(&buf_turn, elems_add);
                end += tick();
                del_elems_array_turn(&buf_turn, elems_add);
            }
            //print_arr(&buf_turn);
            free(buf_turn.arr);
            random_elems_array_turn(&turn_a, elems_add);
            print_res(start / RUNS, end / RUNS);
            printf("Затраченная память под очередь (массив) - %llu байт\n\n", 
                turn_size * sizeof(elem_t) + sizeof(array_turn_t));
            start = 0;
            end = 0;

            list_turn_t buf_list;
            buf_list.size = 0;
            buf_list.head = NULL;
            buf_list.tail = NULL;
            //printf("5");
            for (int i = 0; i < RUNS; i++)
            {
                start += tick();
                error_code = random_elems_list_turn(&buf_list, elems_add);
                //printf("8");
                end += tick();
                if (error_code)
                {
                    free(f_arr.arr);
                    free_list(&turn_l);
                    free_list(&buf_list);
                    free(turn_a.arr);
                    return error_code;
                }
                //printf("%d", error_code);
                del_elems_list_turn(&buf_list, elems_add);
            }
            error_code = random_elems_list_turn(&turn_l, elems_add);
            if (error_code)
            {
                free(f_arr.arr);
                free_list(&turn_l);
                free_list(&buf_list);
                free(turn_a.arr);
                return error_code;
            }

            print_res(start / RUNS, end / RUNS);
            printf("Затраченная память под очередь (список) - %llu байт\n\n", 
                turn_l.head == NULL ? 0 : 
                turn_l.size * sizeof(node_turn_t) + sizeof(list_turn_t) - sizeof(int64_t));

            start = 0;
            end = 0;
        }
        else if (comand == 3)
        {
            int elems_del;
            if ((error_code = count_del_elems_array_turn(&elems_del, turn_a.size)) != OK)
            {
                free(f_arr.arr);
                free_list(&turn_l);
                free(turn_a.arr);
                return error_code;
            }

            array_turn_t buf_turn;
            buf_turn.size = 0;
            buf_turn.arr = malloc(sizeof(elem_t) * elems_del);
            buf_turn.max_size = elems_del;
            buf_turn.head = buf_turn.arr;
            buf_turn.tail = buf_turn.head;

            for (int i = 0; i < RUNS; i++)
            {
                random_elems_array_turn(&buf_turn, elems_del);
                start += tick();
                del_elems_array_turn(&buf_turn, elems_del);
                end += tick();
            }
            //free(buf_turn.arr);
            del_elems_array_turn(&turn_a, elems_del);

            printf("Массив: ");
            print_res(start / RUNS, end / RUNS);
            start = 0;
            end = 0;

            error_code = get_array_of_freed_areas(&f_arr, elems_del, &turn_l);
            if (error_code)
            {
                free_list(&turn_l);
                free(turn_a.arr);
                free(f_arr.arr);
                return error_code;
            }

            list_turn_t buf_list;
            buf_list.size = 0;
            buf_list.head = NULL;
            buf_list.tail = NULL;

            for (int i = 0; i < RUNS; i++)
            {
                error_code = random_elems_list_turn(&buf_list, elems_del);
                if (error_code)
                {
                    free(f_arr.arr);
                    free_list(&turn_l);
                    free_list(&buf_list);
                    free(turn_a.arr);
                    return error_code;
                }
                start += tick();
                del_elems_list_turn(&buf_list, elems_del);
                end += tick();
            }

            del_elems_list_turn(&turn_l, elems_del);

            printf("Список: ");
            print_res(start / RUNS, end / RUNS);

            start = 0;
            end = 0;
        }
        else if (comand == 4)
            print_arr(&turn_a);
        else if (comand == 5)
            print_list(&turn_l);
        else if (comand == 6)
            print_f_arr(&f_arr);
        else if (comand == 0)
        {
            free(f_arr.arr);
            free_list(&turn_l);
            flag = 0;
        }
    }
    return OK;
}