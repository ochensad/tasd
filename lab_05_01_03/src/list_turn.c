#include "list_turn.h"
#include <stdlib.h>
#include <stdio.h>

int pop_turn_list(list_turn_t *turn, elem_t *el)
{
    if (turn->size == 0)
        return EMPTY_TURN;
    *el = turn->head->data;
    node_turn_t *next;
    next = turn->head->next;
    free(turn->head);
    turn->head = next;
    turn->size--;
    return OK;
}

elem_t create_elem(int val)
{
    elem_t el;
    el.value = val;
    return el;
}

int push_turn_list(list_turn_t *turn, elem_t el, size_t max_size)
{
    if (turn->size >= max_size)
        return ERROR_OVERFLOW;
    node_turn_t *new;
    new = calloc(1, sizeof(node_turn_t));
    //printf("cringe");
    if (new == NULL)
        return ERROR_MEMORY;
    new->data = el;
    new->next = NULL;

    if (turn->head == NULL)
    {
        turn->head = new;
        turn->tail = turn->head;
    }
    else
    {
        turn->tail->next = new;
        turn->tail = new;
    }
    turn->size++;

    return OK;
}

int read_elem_list(int *el)
{
    if (scanf("%d", el) != 1)
    {
        printf("\nОшибка при чтении");
        return ERROR_READING;
    }
    return OK;
}

int random_elems_list_turn(list_turn_t *turn, int n)
{
    int error_code;
    int el;
    elem_t data;
    for (int i = 0; i < n; i++)
    {
        el = -120 + rand() % (576);
        data = create_elem(el);
        error_code = push_turn_list(turn, data, MAX_TURN_LEN);
        
        if (error_code == ERROR_MEMORY)
        {
            printf("Ошибка выделения памяти\n");
            return error_code;
        }
        else if (error_code == EMPTY_TURN)
        {
            printf("Ошибка переполнение очереди\n");
            return error_code;
        }
    }
    return OK;
}
int add_elems_list_turn(list_turn_t *turn, int n)
{
    int error_code;
    int el;
    elem_t data;

    for (int i = 0; i < n; i++)
    {
        printf("\nВведите %d-й элемент: ", i + 1);
        error_code = read_elem_list(&el);
        if (error_code)
            return error_code;
        data = create_elem(el);
        error_code = push_turn_list(turn, data, MAX_TURN_LEN);
        if (error_code == ERROR_MEMORY)
        {
            printf("Ошибка выделения памяти\n");
            return error_code;
        }
        else if (error_code == EMPTY_TURN)
        {
            printf("Ошибка переполнение очереди\n");
            return error_code;
        }
    }
    return OK;
}

void del_elems_list_turn(list_turn_t *turn, int n)
{
    elem_t del;
    for (int i = 0; i < n; i++)
        pop_turn_list(turn, &del);
}

void free_list(list_turn_t *turn)
{
    node_turn_t *cur;

    for (; turn->head; turn->head = cur)
    {
        cur = turn->head->next;
        free(turn->head);
    }
}

int get_array_of_freed_areas(arr_free_areas_t *arr, int n, list_turn_t *turn)
{
    node_turn_t **cur_ptr;
    node_turn_t *cur = turn->head;

    for (int i = 0; i < n; i++, cur = cur->next)
    {
        cur_ptr = realloc(arr->arr, (arr->size + 1) * sizeof(node_turn_t*));
        if (cur_ptr == NULL)
        {
            free(arr->arr);
            printf("\n");
            return ERROR_MEMORY;
        }
        arr->arr = cur_ptr;

        arr->arr[arr->size] = cur;
        arr->size++;
    }
    return OK;
}

void print_list(list_turn_t *turn)
{
    if (turn->size == 0)
    {
        printf("Текущий размер очереди - 0\n\n");
        return;
    }
    else
        printf("Текущий размер очереди - %zu\n\n", turn->size);
    
    node_turn_t *p = turn->head;

    printf("HEAD\n");

    while (p != NULL)
    {
        printf("%-10d %-15p\n", p->data.value, (void*) p);
        p = p->next;
    }

    printf("TAIL\n");
}

void print_f_arr(arr_free_areas_t *arr)
{
    printf("\nМассив адресов освобождённых элементов стека:\n\n[");

    for (size_t i = 0; i < arr->size; i++)
    {
        printf("%-15p", (void*) arr->arr[i]);

        if (i != arr->size - 1)
            printf(", ");
    }

    printf("]\n");
}