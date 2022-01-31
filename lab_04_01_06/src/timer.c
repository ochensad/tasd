#include "../inc/timer.h"
#include <inttypes.h>
#include <stdint.h>

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

void print_result(int64_t start, int64_t end)
{
    printf("%lld тактов, %.10lf секунд\n", end - start, (double)(end - start)/HZ);  
}

void print_menu_time(void)
{
    printf("\n"
        "2. Добавить случайные элементы в стек;\n"
        "3. Удалить элементы из стека;\n"
        "4. Вывести текущее состояние стека;\n"
        "5. Проверить стек на палиндром;\n"
        "0. Выйти из программы.\n\n");
}

int read_number_action_time(int *number_action)
{
    int r;
    
    printf("Введите номер команды: ");
    r = scanf("%d", number_action);
    printf("\n");
    
    if (r != 1 )
    {
        printf("Не удалось прочитать номер команды\n");
        return ERROR_READING;
    }
    
    if ( *number_action < 0 || *number_action > 6)
    {
        return ERROR_COMAND;
    }
    
    return OK;
}


int compare_stacks(void)
{
    int number_action, r;
    int array[MAX_LEN_ARR];
    stack_array_t stack_array;

    stack_array.size = 0;
    stack_array.arr = array - 1;

    el_stack_list_t *elem_stack_list = NULL;

    stack_list_t stack;

    stack.arr = NULL;
    stack.size = 0;
    
    int64_t start = 0, end = 0;

    printf("\nПервый стек - массив;\n"
           "Второй стек - список.\n");
    
    int flag = 1;
    while(flag)
    {
        print_menu_time();

        r = read_number_action_time(&number_action);
        
        if (r)
        {
            free_stack(&elem_stack_list);
            return r;
        }

        if (number_action == 2)
        {
            int numb_add_elem;

            r = count_add_elems(&numb_add_elem, &stack_array);

            if (r)
            {
                free_stack(&elem_stack_list);
                return r;
            }

            if (stack_array.size != MAX_LEN_ARR)
            {
                for (int i = 0; i < NUMBER_OF_RUNS; i++)
                {
                    start += tick();
                    add_random_elems_array(numb_add_elem, &stack_array);
                    end += tick();

                    del_elems_array(numb_add_elem, &stack_array);
                }
                
                add_random_elems_array(numb_add_elem, &stack_array);

                print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
                printf("Затраченная память под стек (массив) - %llu байт\n\n", 
                    MAX_LEN_ARR * sizeof(int) + sizeof(stack_array_t));

                start = 0;
                end = 0;

                for (int i = 0; i < NUMBER_OF_RUNS; i++)
                {
                    start += tick();
                    add_elems_list_random(&elem_stack_list, numb_add_elem);
                    end += tick();

                    del_elems_list(&elem_stack_list, numb_add_elem);
                }

                add_elems_list_random(&elem_stack_list, numb_add_elem);

                print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
                printf("Затраченная память под стек (список) - %llu байт\n\n", 
                    elem_stack_list->i_el * sizeof(el_stack_list_t));

                start = 0;
                end = 0;
            }
        }
        else if (number_action == 3)
        {
            int numb_remove_elem;

            r = count_del_elems(&numb_remove_elem, &stack_array);

            if (r)
            {
                free_stack(&elem_stack_list);
                return r;
            }

            printf("\n");

            if (stack_array.size != 0)
            {
                for (int i = 0; i < NUMBER_OF_RUNS; i++)
                {
                    start += tick();
                    del_elems_array(numb_remove_elem,&stack_array);
                    end += tick();

                    add_random_elems_array(numb_remove_elem, &stack_array);
                }
                del_elems_array(numb_remove_elem,&stack_array);

                print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);

                start = 0;
                end = 0;

                printf("\n");
                
                for (int i = 0; i < NUMBER_OF_RUNS; i++)
                {
                    start += tick();
                    del_elems_list(&elem_stack_list, numb_remove_elem);
                    end += tick();

                    add_elems_list_random(&elem_stack_list, numb_remove_elem);
                }

                del_elems_list(&elem_stack_list, numb_remove_elem);

                print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);

                start = 0;
                end = 0;
            }
        }
        else if (number_action == 4)
        {
            print_array_stack(&stack_array);
            printf("\n");
            print_list(&elem_stack_list);
        }
        else if (number_action == 5)
        {
            int arr_size = stack_array.size;
            int list_size = elem_stack_list->i_el;
            for (int i = 0; i < NUMBER_OF_RUNS; i++)
            {
                start += tick();
                check_palindrom(&stack_array);
                end += tick();
                del_elems_array(stack_array.size, &stack_array);
                add_random_elems_array(arr_size, &stack_array);
            }
        
            print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);

            start = 0;
            end = 0;

            printf("\n");

            for (int i = 0; i < NUMBER_OF_RUNS; i++)
            {
                start += tick();
                check_palindrom_list(&elem_stack_list, &stack);
                end += tick();
                del_elems_list(&elem_stack_list, elem_stack_list->i_el);
                add_elems_list_random(&elem_stack_list, list_size);
            }

            print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);

            start = 0;
            end = 0;

            // print_descend_sequen_stack_array(stack_array, stdout);
            // printf("\n");
            // print_descend_sequen_stack_list(elem_stack_list, stdout);
        }
        else if (number_action == 0)
        {
            free_stack(&elem_stack_list);
            break;
        }
       
        if (r)
        {
            free_stack(&elem_stack_list);
            return r;
        }
    }

    return OK;
}