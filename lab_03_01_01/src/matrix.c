#include "../inc/matrix.h"
#include <stdlib.h>
#include<stdio.h>

void free_matrix(int **arr, int n)
{
    for (int i = 0; i < n; i++)
        free(arr[i]);

    free(arr);
}

int **allocate_matrix(int row, int colunm)
{
    int **arr = calloc(row, sizeof(int*));
    if (!arr)
        return NULL;
    
    for (int i = 0; i < row; i++)
    {
        arr[i] = calloc(colunm * sizeof(int), sizeof(int));

        if (!arr[i])
        {
            free_matrix(arr, row);
            return NULL;
        }
    }
    return arr;
}

int create_simple_matrix(matrix_t *matrix)
{
    matrix->matrix = allocate_matrix(matrix->rows, matrix->columns);

    if (matrix->matrix == NULL)
    {
        printf("\nОшибка выделения памяти\n");
        return ERROR_MEMORY;
    }

    return OK;
}

int get_method_simple(int *method, int *fill_size)
{
    int error_code;

    printf("1 - заполнить матрицу вручную\n2 - заполнить матрицу автоматически\n3 - заполнить только ненулевые элементы\nКоманда: ");

    error_code = scanf("%d", method);

    if (error_code != 1)
    {
        printf("\nНе удалось прочитать команду\n");
        return ERROR_READING;
    }
    if (*method < 1 || *method > 3)
    {
        printf("\nНедопустимая команда\n");
        return ERROR_NO_COMAND;
    }

    if (*method == 2)
    {
        printf("\nВведите процент заполнения: ");

        error_code = scanf("%d", fill_size);

        if (error_code != 1)
        {
            printf("\nОшибка чтения числа\n");
            return ERROR_READING;
        }
        if (*fill_size > 100 || *fill_size <= 0)
        {
            printf("\nНедопустимый процент заполнения\n");
            return ERROR_INVALID_MATRIX;
        }
    }
    return OK;
}

int read_matrix(matrix_t *matrix)
{
    int error_code;
    printf("\nЗаполните матрицу по строкам:");

    for(int i = 0; i < matrix->rows; i++)
    {
        printf("\n%d-я строка: ", i);
        for (int j = 0; j < matrix->columns; j++)
        {
            error_code = scanf("%d", matrix->matrix[i] + j);

            if (error_code != 1)
            {
                printf("\nОшибка чтения мастрицы\n");
                return ERROR_READING;
            }
        }
    }
    return OK;
}

int read_elem_matrix(matrix_t *matrix)
{
    int error_code;

    int count;

    printf("\nКоличество ненулевых элементов матрицы (от 1 до %d): ", matrix->columns * matrix->rows);

    error_code = scanf("%d", &count);

    if (error_code != 1)
    {
        printf("\nНе удалось прочитать число\n");
        return ERROR_READING;
    }

    if (count < 0)
    {
        printf("\nКоличество ненулевых элементов не может быть отрицательным\n");
        return ERROR_INVALID_MATRIX;
    }

    if (count > matrix->columns * matrix->rows)
    {
        printf("\nКоличество ненулевых элементов не может привышать размер матрицы\n");
        return ERROR_INVALID_MATRIX;
    }
    error_code = OK;

    printf("\nВведите элементы: ");
    int i, j, elem;
    for (int k = 0; k < count; k++)
    {
        printf("\nЭлемент: ");
        error_code = scanf("%d", &elem);

        if (error_code != 1)
        {
            printf("\nОшибка чтения элемента матрицы\n");
            return ERROR_READING;
        }

        printf("  Номер столбца: ");
        error_code = scanf("%d", &j);

        if (error_code != 1)
        {
            printf("\nОшибка чтения номера столбца\n");
            return ERROR_READING;
        }
        if (j < 0 || j >= matrix->columns)
        {
            printf("\nНедопустимое значение столбца\n");
            return ERROR_SIZE_MATRIX;
        }

        printf("  Номер строки: ");
        error_code = scanf("%d", &i);

        if (error_code != 1)
        {
            printf("\nОшибка чтения строки\n");
            return ERROR_READING;
        }
        if (i < 0 || i >= matrix->rows)
        {
            printf("\nНедопустимое значение строки\n");
            return ERROR_SIZE_MATRIX;
        }
        matrix->matrix[i][j] = elem;
    }
    return OK;
}

int random_simple_matrix(matrix_t *matrix, int fill_size)
{
    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->columns; j++)
            matrix->matrix[i][j] = 0;

    int elems = matrix->rows * matrix->columns * fill_size/100;

    if (!elems)
    {
        printf("\nМатрица состоит из нулей\n");
        return ERROR_INVALID_MATRIX;
    }

    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
        {
            if (elems-- > 0)
            {
                int i_el = 0 + rand() % matrix->rows;
                int j_el = 0 + rand() % matrix->columns;
                int el = 0 + rand() % 120;
                while(matrix->matrix[i_el][j_el] != 0)
                {
                    i_el = 0 + rand() % matrix->rows;
                    j_el = 0 + rand() % matrix->columns;
                }
                matrix->matrix[i_el][j_el] = el;
            }
        }
    }

    return OK;
}

void addition_simple(matrix_t *res_matrix,matrix_t *matrix, matrix_t *matrix_2)
{
    for (int i = 0; i < res_matrix->rows; i++)
        for (int j = 0; j < res_matrix->columns; j++)
            res_matrix->matrix[i][j] = matrix->matrix[i][j] + matrix_2->matrix[i][j];
}

void print_matrix(matrix_t *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
            printf("%d ", matrix->matrix[i][j]);
        printf("\n");
    }
}

int simple_addition(void)
{
    int error_code;
    matrix_t matrix;

    error_code = read_matrix_size(&matrix.rows, &matrix.columns);

    if (error_code)
        return error_code;
    
    error_code = create_simple_matrix(&matrix);

    if (error_code)
        return error_code;
    
    int method;
    int fill_size;

    error_code = get_method_simple(&method, &fill_size);

    if (error_code)
    {
        free_matrix(matrix.matrix, matrix.rows);
        return error_code;
    }

    if (method == 1)
    {
        error_code = read_matrix(&matrix);

        if (error_code)
        {
            free_matrix(matrix.matrix, matrix.rows);
            return error_code;
        }
    }
    else if (method == 2)
    {
        error_code = random_simple_matrix(&matrix, fill_size);

        if (error_code)
        {
            free_matrix(matrix.matrix, matrix.rows);
            return OK;
        }
    }
    else if (method == 3)
    {
        error_code = read_elem_matrix(&matrix);

        if (error_code)
        {
            free_matrix(matrix.matrix, matrix.rows);
            return error_code;
        }
    }
    print_matrix(&matrix);
    printf("\n");
    matrix_t matrix_2;

    matrix_2.rows = matrix.rows;
    matrix_2.columns = matrix.columns;

    error_code = create_simple_matrix(&matrix_2);

    if (error_code)
        return error_code;

    error_code = get_method_simple(&method, &fill_size);

    if (error_code)
    {
        free_matrix(matrix_2.matrix, matrix_2.rows);
        free_matrix(matrix.matrix, matrix.rows);
        return error_code;
    }

    if (method == 1)
    {
        error_code = read_matrix(&matrix_2);

        if (error_code)
        {
            free_matrix(matrix_2.matrix, matrix_2.rows);
            free_matrix(matrix.matrix, matrix.rows);
            return error_code;
        }
    }
    else if (method == 2)
    {
        error_code = random_simple_matrix(&matrix_2, fill_size);

        if (error_code)
        {
            free_matrix(matrix_2.matrix, matrix_2.rows);
            free_matrix(matrix.matrix, matrix.rows);
            return OK;
        }
    }
    else if (method == 3)
    {
        error_code = read_elem_matrix(&matrix_2);

        if (error_code)
        {
            free_matrix(matrix_2.matrix, matrix_2.rows);
            free_matrix(matrix.matrix, matrix.rows);
            return error_code;
        }
    }
    print_matrix(&matrix_2);
    printf("\n");
    matrix_t res_matrix;

    res_matrix.rows = matrix.rows;
    res_matrix.columns = matrix.columns;

    error_code = create_simple_matrix(&res_matrix);

    if (error_code)
    {
        free_matrix(matrix.matrix, matrix.rows);
        free_matrix(matrix_2.matrix, matrix_2.rows);
        return error_code;
    }

    addition_simple(&res_matrix, &matrix, &matrix_2);
    printf("\nРезультирующая матрица\n");
    print_matrix(&res_matrix);
    return OK;
}