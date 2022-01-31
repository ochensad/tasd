#include "stack_array.h"
#include <stdlib.h>

int count_add_elems(int *num, stack_array_t *stack)
{
    if (stack->size == MAX_LEN)
    {
        printf("Стек уже заполнен\n");
        return OK;
    }

    printf("\nВведите количество элементов для добавления: ");
    if (scanf("%d", num) != 1)
    {
        printf("\nОшибка при чтении");
        return ERROR_READING;
    }
    if (*num < 0)
    {
        printf("\nНедопустимое значение");
        return ERROR_NUM_EL;
    }
    if (stack->size + *num > MAX_LEN)
    {
        printf("\nПроизошло переполнение стека");
        return ERROR_OVERFLOW;
    }
    return OK;
}

int read_elem(int *el)
{
    if (scanf("%d", el) != 1)
    {
        printf("Ошибка при чтении\n");
        return ERROR_READING;
    }
    return OK;
}

void get_el(int *el_dst, int *el_src)
{
    *el_dst = *el_src;
}

void push_array(stack_array_t *stack, int *value)
{
    stack->arr++;
    get_el(stack->arr, value);
    stack->size++;
}

int add_elems_array(int elems, stack_array_t *stack)
{
    printf("Введите элементы стека\n");
    int error_code;
    int value;
    for (int i = 0; i < elems; i++)
    {
        if ((error_code = read_elem(&value)) != OK)
            return error_code;
        push_array(stack, &value);
    }
    return OK;
}

int add_random_elems_array(int elems, stack_array_t *stack)
{
    for (int i = 0; i < elems; i++)
    {
        stack->arr++;
        *stack->arr = 0 + rand() % (1000);
        stack->size++;
    }
    return OK;
}

int count_del_elems(int *num, stack_array_t *stack)
{
    if (stack->size == 0)
    {
        printf("Стек пуст\n");
        return OK;
    }

    printf("\nВведите количество элементов для удаления: ");
    if (scanf("%d", num) != 1)
    {
        printf("\nОшибка при чтении");
        return ERROR_READING;
    }
    if (*num < 0)
    {
        printf("\nНедопустимое значение");
        return ERROR_NUM_EL;
    }
    if (stack->size < *num)
    {
        printf("\nНельзя удалить такое количество элементов");
        return ERROR_DELITE_ALL;
    }
    return OK;
}

void pop_array(stack_array_t *stack)
{
    stack->arr--;
    stack->size--;
}

int del_elems_array(int elems, stack_array_t *stack)
{
    for (int i = 0; i < elems; i++)
        pop_array(stack);
    return OK;
}

void print_array_stack(stack_array_t *stack)
{
    printf("\n");
    printf("________________________________\n");
    printf("|%-30s|\n", "           Значение           ");
    printf("________________________________\n");
    for (int i = stack->size; i > 0; i--)
    {
        printf("|%-30d|\n", *(stack->arr));
        pop_array(stack);
    }
    printf("________________________________\n");
}

int check_palindrom(stack_array_t *stack)
{
    if (stack->size == 0)
    {
        printf("Стек пуст\n");
        return OK;
    }
    stack_array_t buf;
    buf.size = 0;
    int arr_buf[MAX_LEN];
    buf.arr = arr_buf - 1;

    int k = stack->size/2;
    int flag = 0;
    if (stack->size % 2 != 0)
    {
        k++;
        flag = 1;
    }

    for (int i = stack->size; i > k; i--)
    {
        push_array(&buf, stack->arr);
        pop_array(stack);
    }
    if (flag)
        pop_array(stack);
    
    for (int i = stack->size; i > 0; i--)
    {
        if (*(stack->arr) != *(buf.arr))
        {
            printf("Строка не является палиндромом\n");
            return OK;
        }
        pop_array(stack);
        pop_array(&buf);
    }
    printf("Строка является палиндромом\n");
    return OK;
}

int get_stack_array(void)
{
    int error_code;
    int comand;

    stack_array_t stack;

    stack.size = 0;

    int arr[MAX_LEN];
    stack.arr = arr - 1;

    int flag = 1;

    while(flag)
    {
        print_menu();

        if ((error_code = read_comand(&comand)) != OK)
            return error_code;
        
        if (comand == 1)
        {
            int elems_add;
            if ((error_code = count_add_elems(&elems_add, &stack)) != OK)
                return error_code;
            if (stack.size != MAX_LEN)
                error_code = add_elems_array(elems_add, &stack);
            if (error_code)
                return error_code;
        }
        else if (comand == 2)
        {
            int elems_add;
            if ((error_code = count_add_elems(&elems_add, &stack)) != OK)
                return error_code;
            if (stack.size != MAX_LEN)
                error_code = add_random_elems_array(elems_add, &stack);
            if (error_code)
                return error_code;
        }
        else if (comand == 3)
        {
            int elems_del;
            if ((error_code = count_del_elems(&elems_del, &stack)) != OK)
                return error_code;
            if (stack.size != 0)
                del_elems_array(elems_del, &stack);
        }
        else if (comand == 4)
        {
            print_array_stack(&stack);
        }
        else if (comand == 5)
        {
            check_palindrom(&stack);
        }
        else if (comand == 0)
        {
            flag = 0;
        }
    }
    return OK;
}