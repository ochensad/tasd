#include "array_turn.h"
#include <stdio.h>
#include <stdlib.h>

int push_turn_array(array_turn_t *turn, elem_t el)
{
    if (turn->size == turn->max_size)
        return ERROR_OVERFLOW;
    if (turn->head - turn->arr == turn->max_size)
        turn->head = turn->arr;
    
    *turn->head++ = el;
    turn->size++;
    return OK;
}

int pop_turn_array(array_turn_t *turn, elem_t *el)
{
    if (turn->size == 0)
        return ERROR_TURN;
    
    *el = *turn->head;

    turn->size--;
    turn->tail++;

    if (turn->tail - turn->arr == turn->max_size)
        turn->tail = turn->arr;
    return OK;
}

int read_elem(int *el)
{
    if (scanf("%d", el) != 1)
    {
        printf("\nОшибка при чтении");
        return ERROR_READING;
    }
    return OK;
}

int add_elems_array_turn(array_turn_t *turn, int n)
{
    int error_code;
    int el;
    elem_t elem;
    for (int i = 0; i < n; i++)
    {
        printf("\nВведите %d-й элемент: ", i + 1);
        error_code = read_elem(&el);
        if (error_code)
            return error_code;
        elem.value = el;
        push_turn_array(turn, elem);
    }
    return OK;
}

void random_elems_array_turn(array_turn_t *turn, int n)
{
    int el;
    elem_t elem;
    for (int i = 0; i < n; i++)
    {
        el = -120 + rand() % (576);
        elem.value = el;
        push_turn_array(turn, elem);
    }
}

void del_elems_array_turn(array_turn_t *turn, int n)
{
    elem_t el;
    for (int i = 0; i < n; i++)
        pop_turn_array(turn, &el);
}

int count_add_elems_array_turn(int *num, int size)
{
    if (size == MAX_TURN_LEN)
    {
        printf("Очередь полностью заполнена\n");
        return OK;
    }

    printf("Введите количество добавляемых элементов: \n");

    if (scanf("%d", num) != 1)
    {
        printf("Ошибка при чтении\n");
        return ERROR_READING;
    }
    else if (*num < 0)
    {
        printf("Ошибка. Отрицательное количество элементов\n");
        return ERROR_NUM;
    }
    else if (size + *num > MAX_TURN_LEN)
    {
        printf("Ошибка. Переполнение очереди\n");
        return ERROR_OVERFLOW;
    }
    return OK;
}

int count_del_elems_array_turn(int *num, int size)
{
    if (size == 0)
    {
        printf("Очередь пуста\n");
        return OK;
    }

    printf("Введите количество удаляемых элементов: \n");

    if (scanf("%d", num) != 1)
    {
        printf("Ошибка при чтении\n");
        return ERROR_READING;
    }
    else if (*num < 0)
    {
        printf("Ошибка. Отрицательное количество элементов\n");
        return ERROR_NUM;
    }
    else if (*num > size)
    {
        printf("Ошибка. В очереди нет столько элементов\n");
        return ERROR_TURN;
    }
    return OK;
}

void print_arr(array_turn_t *turn)
{
    printf("Текущий размер очереди - %d\n\n", turn->size);

    if (turn->size == 0)
        return;

    printf("HEAD\n");

    for (int i = 0; i < turn->max_size; i++)
    {
        if (turn->head <= turn->tail)
        {
            if (i >= turn->head - turn->arr && i < turn->tail - turn->arr)
                printf("i = %3d   свободная область памяти      |  адрес области %p\n", i + 1, (void*)(turn->arr + sizeof(elem_t) * i));
            else
                printf("i = %3d   значение элемента = %d  |  адрес элемента %p\n", i + 1, turn->arr[i].value, (void*)(turn->arr + sizeof(elem_t) * i));
        }
        else
        {
            if (i >= turn->tail - turn->arr && i < turn->head - turn->arr)
                printf("i = %3d   значение элемента = %d  |  адрес элемента %p\n", i+1, turn->arr[i].value, (void*)(turn->arr + sizeof(elem_t) * i));
            else
                printf("i = %3d   свободная область памяти      |  адрес области %p\n", i+1, (void*)(turn->arr + sizeof(elem_t) * i));
        }
    }

    printf("TAIL\n");
}
