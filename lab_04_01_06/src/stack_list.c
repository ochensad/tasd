#include "stack_list.h"
#include <stdlib.h>

void free_stack(el_stack_list_t **elem_stack_list)
{
    el_stack_list_t *buf;
    while (*elem_stack_list != NULL)
    {
        buf = (*elem_stack_list)->next;
        free(*elem_stack_list);
        *elem_stack_list = buf;
    }
}
int count_add_list_elems(int *num, el_stack_list_t *el_stack)
{
    if (el_stack != NULL && el_stack->i_el == MAX_LIST_LEN)
    {
        printf("Стек уже заполнен\n");
        return ERROR_OVER_STACK;
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
    if (el_stack == NULL && *num <= MAX_LIST_LEN)
        return OK;
    if (el_stack == NULL && *num > MAX_LIST_LEN)
    {
        printf("\nПроизошло переполнение стека");
        return ERROR_OVERFLOW;
    }
    else if (el_stack->i_el + *num > MAX_LIST_LEN)
    {
        printf("\nПроизошло переполнение стека");
        return ERROR_OVERFLOW;
    }
    return OK;
}

int push_list(el_stack_list_t **el, int value)
{
    el_stack_list_t *new;

    new = malloc(sizeof(el_stack_list_t));
    if (new == NULL)
        return ERROR_MEMORY;
    
    if (*el == NULL)
        new->i_el = 1;
    else
        new->i_el = (*el)->i_el + 1;
    new->next = *el;
    *el = new;
    (*el)->el = value;
    return OK;
}

int read_elem_list(int *el)
{
    if (scanf("%d", el) != 1)
    {
        printf("Ошибка при чтении\n");
        return ERROR_READING;
    }
    return OK;
}

int add_elems_list(el_stack_list_t **el, int n)
{
    int value;
    for (int i = 0; i < n; i++)
    {
        printf("Введите %d элемент\n", i + 1);
        if (read_elem_list(&value) != OK)
            return ERROR_READING;
        if (push_list(el, value) != OK)
        {
            printf("Ошибка выделения памяти\n");
            return ERROR_MEMORY;
        }
    }
    return OK;
}

int add_elems_list_random(el_stack_list_t **el, int n)
{
    int value;
    for (int i = 0; i < n; i++)
    {
        value = 0 + rand() % 150;
        if (push_list(el, value) != OK)
        {
            printf("Ошибка выделения памяти\n");
            return ERROR_MEMORY;
        }
    }
    return OK;
}


int count_del_list_elems(int *num, el_stack_list_t *el_stack)
{
    if (el_stack == NULL)
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
    if (*num > el_stack->i_el)
    {
        printf("\nНельзя удалить такое количество элементов");
        return ERROR_OVERFLOW;
    }
    return OK;
}

int get_arr_del_elems(stack_list_t *arr, el_stack_list_t *el, int n)
{
    if (el == NULL)
        return OK;
    el_stack_list_t **tmp;
    for (int i = 0; i < n; i++)
    {
        tmp = realloc(arr->arr, (arr->size + 1) * sizeof(el_stack_list_t*));
        if (tmp == NULL)
        {
            printf("Ошибка выделения памяти\n");
            free(arr->arr);
            return ERROR_MEMORY;
        }
        arr->arr = tmp;
        arr->arr[arr->size] = el;
        arr->size++;
        el = el->next;
    }
    return OK;
}

void pop_list(el_stack_list_t **el)
{
    el_stack_list_t *cur;

    cur = (*el)->next;
    free(*el);
    *el = cur;
}

void del_elems_list(el_stack_list_t **el, int n)
{
    for (int i = 0; i < n; i++)
    {
        pop_list(el);
    }
}

void print_list(el_stack_list_t **el)
{
    if (*el == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    printf("___________________________________\n");
    printf("|%-15s|%-15s|\n", "    Указатель   ", "    Значение    ");
    printf("___________________________________\n");


    for (; *el != NULL;)
    {
        printf("| %-15p| %-15d|\n", (void*)*el, (*el)->el);
        pop_list(el);
    }

    
    printf("___________________________________\n");
}

void print_list_pointer_array(stack_list_t *arr)
{
    printf("Массив освобожденных элементов стека\n");
    for (int i = 0; i < arr->size; i++)
    {
        printf("%d элемент - %-15p\n", i + 1, (void*)arr->arr[i]);
    }
}

int check_palindrom_list(el_stack_list_t **stack_cur, stack_list_t *arr)
{
    if (*stack_cur == NULL)
    {
        printf("Стек пуст\n");
        return OK;
    }
    el_stack_list_t *stack_buf = NULL;

    int k = (*stack_cur)->i_el/2;
    int flag = 0;
    if ((*stack_cur)->i_el % 2 != 0)
    {
        k++;
        flag = 1;
    }

    for (int i = (*stack_cur)->i_el; i > k; i--)
    {
        if (push_list(&stack_buf, (*stack_cur)->el) != OK)
        {
            printf("Ошибка выделения памяти\n");
            return ERROR_MEMORY;
        }
        pop_list(stack_cur);
        get_arr_del_elems(arr, *stack_cur, 1);
    }

    if (flag)
    {
        get_arr_del_elems(arr, *stack_cur, 1);
        pop_list(stack_cur);
    }

    for (; *stack_cur != NULL;)
    {
        if (stack_buf->el != (*stack_cur)->el)
        {
            printf("Стек не является палиндромом\n");
            return OK;
        }
        get_arr_del_elems(arr, *stack_cur, 1);
        pop_list(stack_cur);
        pop_list(&stack_buf);
    }
    printf("Стек является палиндромом\n");
    return OK;
}

int get_stack_list(void)
{
    int error_code, comand, flag = 1;

    el_stack_list_t *el_stack = NULL;
    stack_list_t stack;

    stack.arr = NULL;
    stack.size = 0;

    while (flag)
    {
        print_menu();
        if ((error_code = read_comand(&comand)) != OK)
        {
            free_stack(&el_stack);
            free(stack.arr);
            return error_code;
        }
        if (comand == 1)
        {
            int elems_add;
            if ((error_code = count_add_list_elems(&elems_add, el_stack)) != OK && error_code != ERROR_OVER_STACK )
            {
                free_stack(&el_stack);
                free(stack.arr);
                return error_code;
            }
            if (error_code != ERROR_OVER_STACK &&((stack.size != MAX_LIST_LEN && el_stack != NULL) || el_stack == NULL))
                error_code = add_elems_list(&el_stack, elems_add);
            if (error_code != OK && error_code != ERROR_OVER_STACK)
            {
                free_stack(&el_stack);
                free(stack.arr);
                return error_code;
            }
        }
        else if (comand == 2)
        {
            int elems_add;
            if ((error_code = count_add_list_elems(&elems_add, el_stack)) != OK)
            {
                free_stack(&el_stack);
                free(stack.arr);
                return error_code;
            }

            if ((stack.size != MAX_LIST_LEN && el_stack != NULL) || el_stack == NULL)
                error_code = add_elems_list_random(&el_stack, elems_add);
            if (error_code)
            {
                free_stack(&el_stack);
                free(stack.arr);
                return error_code;
            }
        }
        else if (comand == 3)
        {
            int elems_del;
            if ((error_code = count_del_list_elems(&elems_del, el_stack)) != OK)
            {
                free_stack(&el_stack);
                free(stack.arr);
                return error_code;
            }
            if (el_stack != NULL)
            {
                if ((error_code = get_arr_del_elems(&stack, el_stack, elems_del)) != OK)
                {
                    free_stack(&el_stack);
                    return error_code;
                }
                del_elems_list(&el_stack, elems_del);
            }
        }
        else if (comand == 4)
        {
            if (el_stack != NULL)
                get_arr_del_elems(&stack, el_stack, el_stack->i_el);
            print_list(&el_stack);
            print_list_pointer_array(&stack);
        }
        else if (comand == 5)
        {
            error_code = check_palindrom_list(&el_stack, &stack);
            if (error_code)
            {
                free_stack(&el_stack);
                free(stack.arr);
                return error_code;
            }
        }
        else if (comand == 0)
        {
            free_stack(&el_stack);
            free(stack.arr);
            flag = 0;
        }
    }
    return OK;
}