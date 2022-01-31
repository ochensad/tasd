#include "../inc/sparce_matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_matrix_size(int *rows, int *columns)
{
    int error_code;

    printf("Введите размер матрицы\n");

    printf("Количество строк: ");
    error_code = scanf("%d", rows);

    if (error_code != 1)
    {
        printf("\nПри чтении количества строк произошла ошибка");
        return ERROR_READING;
    }
    if (*rows <= 0)
    {
        printf("\nНедопустимый размер матрицы");
        return ERROR_INVALID_MATRIX;
    }

    printf("Количество столбцов: ");
    error_code = scanf("%d", columns);

    if (error_code != 1)
    {
        printf("\nПри чтении количества столбцов произошла ошибка");
        return ERROR_READING;
    }
    if (*columns <= 0)
    {
        printf("\nНедопустимый размер матрицы");
        return ERROR_INVALID_MATRIX;
    }
    error_code = OK;
    return error_code;
}

int get_method(int *method, int *fill_size)
{
    int error_code;

    printf("1 - заполнить матрицу вручную\n2 - заполнить матрицу автоматически\nКоманда: ");

    error_code = scanf("%d", method);

    if (error_code != 1)
    {
        printf("\nНе удалось прочитать команду\n");
        return ERROR_READING;
    }
    if (*method < 1 || *method > 2)
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

int read_sparce_no_zero(sparse_matrix_t *matrix)
{
    int error_code;

    printf("\nКоличество ненулевых элементов матрицы (от 1 до %d): ", matrix->columns * matrix->rows);

    error_code = scanf("%d", &matrix->elems);

    if (error_code != 1)
    {
        printf("\nНе удалось прочитать число\n");
        return ERROR_READING;
    }

    if (matrix->elems < 0)
    {
        printf("\nКоличество ненулевых элементов не может быть отрицательным\n");
        return ERROR_INVALID_MATRIX;
    }

    if (matrix->elems > matrix->columns * matrix->rows)
    {
        printf("\nКоличество ненулевых элементов не может привышать размер матрицы\n");
        return ERROR_INVALID_MATRIX;
    }
    error_code = OK;

    return error_code;
}

int create_sparce_matrix(sparse_matrix_t *matrix)
{
    matrix->vect_a = NULL;

    matrix->vect_a = calloc(matrix->elems, sizeof(int));

    if (matrix->vect_a == NULL)
    {
        printf("\nОшибка при выделении памяти для вектора А\n");
        return ERROR_MEMORY;
    }

    matrix->vect_ja = NULL;

    matrix->vect_ja = calloc(matrix->elems, sizeof(int));

    if (matrix->vect_ja == NULL)
    {
        printf("\nОшибка при выделении памяти для вектора JA\n");
        free(matrix->vect_a);
        return ERROR_MEMORY;
    }

    matrix->linked_list_ia = NULL;

    matrix->linked_list_ia = calloc(matrix->elems, sizeof(int));

    if (matrix->linked_list_ia == NULL)
    {
        printf("\nОшибка при выделении памяти для связного чписка\n");
        free(matrix->vect_a);
        free(matrix->vect_ja);
        return ERROR_MEMORY;
    }
    return OK;
}

void free_sparce_matrix(sparse_matrix_t *matrix)
{
    free(matrix->vect_a);
    free(matrix->vect_ja);
    free(matrix->linked_list_ia);
}

int convert_matrix(sparse_matrix_t *matrix)
{
    int *arr = calloc(matrix->rows + 1, sizeof(int));
    if (arr == NULL)
        return ERROR_MEMORY;
    int k = 0;
    arr[0] = 0;
    for (int i = 0, j = 1; i < matrix->rows; i++)
    {
        if (matrix->linked_list_ia[k] != i)
        {
            arr[j] = k;
            j++;
        }
        else if (matrix->linked_list_ia[k] == i)
        {
            while (matrix->linked_list_ia[k] < i + 1 && k < matrix->elems)
            {
                k++;
            }
            arr[j] = k;
            j++;
        }
    }

    int *tmp = realloc(matrix->linked_list_ia, (matrix->rows + 1) * sizeof(int));
    if (tmp == NULL)
        return ERROR_MEMORY;
    
    matrix->linked_list_ia = tmp;

    for (int i = 0; i < matrix->rows + 1; i++)
        matrix->linked_list_ia[i] = arr[i];
    free(arr);
    return OK;
}
int read_sparce_matrix(sparse_matrix_t *matrix)
{
    int error_code;

    printf("\nЗаполните матрицу,размером %dx%d\n", matrix->rows, matrix->columns);

    for (int i = 0; i < matrix->elems; i++)
    {
        printf("\nЭлемент: ");
        error_code = scanf("%d", matrix->vect_a + i);

        if (error_code != 1)
        {
            printf("\nОшибка чтения элемента матрицы\n");
            return ERROR_READING;
        }

        printf("  Номер столбца: ");
        error_code = scanf("%d", matrix->vect_ja + i);

        if (error_code != 1)
        {
            printf("\nОшибка чтения номера столбца\n");
            return ERROR_READING;
        }
        if (matrix->vect_ja[i] < 0 || matrix->vect_ja[i] >= matrix->columns)
        {
            printf("\nНедопустимое значение столбца\n");
            return ERROR_SIZE_MATRIX;
        }

        printf("  Номер строки: ");
        error_code = scanf("%d", matrix->linked_list_ia + i);

        if (error_code != 1)
        {
            printf("\nОшибка чтения строки\n");
            return ERROR_READING;
        }
        if (matrix->linked_list_ia[i] < 0 || matrix->linked_list_ia[i] >= matrix->rows)
        {
            printf("\nНедопустимое значение строки\n");
            return ERROR_SIZE_MATRIX;
        }

        for (int j = 0; j < i; j++)
        {
            if (matrix->linked_list_ia[j] == matrix->linked_list_ia[i] && matrix->vect_ja[j] == matrix->vect_ja[i])
            {
                printf("\nТакой элемент уже есть в матрице\n");
                return ERROR_INVALID_MATRIX;
            }
        }
    }
    sort_matrix(matrix);
    error_code = convert_matrix(matrix);
    if (error_code)
        return error_code;

    return OK;
}

int random_sparce_matrix(sparse_matrix_t *matrix)
{
    int error_code;
    
    for (int i = 0; i < matrix->elems; i++)
    {
        matrix->vect_a[i] = 0;
        matrix->vect_ja[i] = 0;
        matrix->linked_list_ia[i] = 0;
    }
    for (int i = 0; i < matrix->elems; i++)
    {
        int flag = 1;
        int i_el = 0;
        int j_el = 0;
        while (flag)
        {
            i_el = 0 + rand() % matrix->rows;
            j_el = 0 + rand() % matrix->columns;
            int flag_k = 1;
            for (int k = 0; k < matrix->elems && flag_k; k++)
            {
                if (matrix->vect_ja[k] == j_el && matrix->linked_list_ia[k] == i_el)
                    flag_k = 0;
            }
            if (flag_k)
                flag = 0;
        }
        int el = 0 + rand() % 120;
        matrix->vect_a[i] = el;
        matrix->vect_ja[i] = j_el;
        matrix->linked_list_ia[i] = i_el;
    }
    sort_matrix(matrix);
    error_code = convert_matrix(matrix);
    if (error_code)
        return error_code;

    return OK;
}

void print_zero_matrix(sparse_matrix_t *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
            printf("0 ");
        printf("\n");
    }
}

void swap(int *a, int *b)
{
    char buf[200];
    memcpy(&buf,a, sizeof(int));
    memcpy(a,b,sizeof(int));
    memcpy(b, &buf, sizeof(int));
}
void sort_matrix(sparse_matrix_t *matrix)
{
    for (int i = 0; i < matrix->elems; i++)
    {
        for (int j = 0; j < matrix->elems - 1; j++)
            if (matrix->linked_list_ia[j] > matrix->linked_list_ia[j + 1])
            {
                swap(&matrix->linked_list_ia[j], &matrix->linked_list_ia[j+1]);
                swap(&matrix->vect_ja[j], &matrix->vect_ja[j+1]);
                swap(&matrix->vect_a[j], &matrix->vect_a[j+1]);
            }
            else if (matrix->linked_list_ia[j] == matrix->linked_list_ia[j + 1])
            {
                if (matrix->vect_ja[j] > matrix->vect_ja[j + 1])
                {
                    swap(&matrix->linked_list_ia[j], &matrix->linked_list_ia[j+1]);
                    swap(&matrix->vect_ja[j], &matrix->vect_ja[j+1]);
                    swap(&matrix->vect_a[j], &matrix->vect_a[j+1]);
                }
            }
    }
}

int count_row(sparse_matrix_t *res, sparse_matrix_t *a, sparse_matrix_t *b, int i_cur)
{
    if (a->linked_list_ia[i_cur] == a->linked_list_ia[i_cur + 1] && b->linked_list_ia[i_cur] == b->linked_list_ia[i_cur + 1])
        return OK;
    
    int *jc = calloc(a->columns, sizeof(int));

    int i_c = 0;
    for (int i_a = a->linked_list_ia[i_cur]; i_a < a->linked_list_ia[i_cur + 1]; i_a++)
    {
        i_c = a->vect_ja[i_a];
        jc[i_c] = a->vect_a[i_a];
    }
    for (int i_b = b->linked_list_ia[i_cur]; i_b < b->linked_list_ia[i_cur + 1]; i_b++)
    {
        i_c = b->vect_ja[i_b];
        jc[i_c] += b->vect_a[i_b];
    }
    int k = res->linked_list_ia[i_cur];
    for (i_c = 0; i_c < a->columns; i_c ++)
        if (jc[i_c] != 0)
        {
            res->vect_a[k] = jc[i_c];
            res->vect_ja[k] = i_c;
            k++;
        }
    res->linked_list_ia[i_cur + 1] = k;
    free(jc);
    return OK;
}
void res_mat(sparse_matrix_t *res, sparse_matrix_t *a, sparse_matrix_t *b)
{
    res->elems = 0;
    for (int i = 0; i < a->rows; i++)
    {
        res->linked_list_ia[i] = res->elems;
        int k_a = a->linked_list_ia[i], k_b = b->linked_list_ia[i];
        for (; k_a < a->linked_list_ia[i + 1] && k_b < b->linked_list_ia[i + 1];)
        {
            //printf("~%d~", i);
            if (a->vect_ja[k_a] == b->vect_ja[k_b])
            {
                int sum = a->vect_a[k_a] + b->vect_a[k_b];
                if (sum != 0)
                {
                    res->vect_a[res->elems] = sum;
                    res->vect_ja[res->elems] = a ->vect_ja[k_a];
                    res->elems++;
                }
                k_a++;
                k_b++;
            }
            else if (a->vect_ja[k_a] > b->vect_ja[k_b])
            {
                res->vect_a[res->elems] = b->vect_a[k_b];
                res->vect_ja[res->elems] = b->vect_ja[k_b];
                res->elems++;
                k_b++;
            }
            else
            {
                res->vect_a[res->elems] = a->vect_a[k_a];
                res->vect_ja[res->elems] = a->vect_ja[k_a];
                res->elems++;
                k_a++;
            }
        }
        while (k_a < a->linked_list_ia[i + 1])
        {
            res->vect_a[res->elems] = a->vect_a[k_a];
            res->vect_ja[res->elems] = a->vect_ja[k_a];
            //printf("!%d, %d!", i, res->vect_a[res->elems]);
            res->elems++;
            k_a++;
        }
        while (k_b < b->linked_list_ia[i + 1])
        {
            res->vect_a[res->elems] = b->vect_a[k_b];
            res->vect_ja[res->elems] = b->vect_ja[k_b];
            //printf("*%d, %d*", i, res->vect_a[res->elems]);
            res->elems++;
            k_b++;
        }
    }
    res->linked_list_ia[a->rows] = res->elems;
}
void addition_sparce(sparse_matrix_t *res, sparse_matrix_t *a, sparse_matrix_t *b)
{
    for (int i = 0; i < a->rows; i++)
        count_row(res, a, b, i);
}

void addition_matrix_sparce(sparse_matrix_t *res_mat, sparse_matrix_t *mat_1, sparse_matrix_t *mat_2)
{
    int k = 0;
    int k_1 = 0;
    int k_2 = 0;
    while (k < res_mat->elems && (k_1 < mat_1->elems || k_2 < mat_2->elems))
    {
        if (k_1 < mat_1->elems && k_2 < mat_2->elems)
        {
            if (mat_1->linked_list_ia[k_1] == mat_2->linked_list_ia[k_2] && mat_1->vect_ja[k_1] == mat_2->vect_ja[k_2])
            {
                res_mat->linked_list_ia[k] = mat_2->linked_list_ia[k_2];
                res_mat->vect_ja[k] = mat_2->vect_ja[k_2];
                res_mat->vect_a[k] = mat_1->vect_a[k_1] + mat_2->vect_a[k_2];
                k++;
                k_1++;
                k_2++;
            }
            else if (mat_1->linked_list_ia[k_1] == mat_2->linked_list_ia[k_2])
            {
                if (mat_2->vect_ja[k_2] > mat_1->vect_ja[k_1])
                {
                    if (mat_1->vect_ja[k_1 + 1] > mat_2->vect_ja[k_2])
                    {
                        res_mat->linked_list_ia[k] = mat_2->linked_list_ia[k_2];
                        res_mat->vect_ja[k] = mat_2->vect_ja[k_2];
                        res_mat->vect_a[k] = mat_2->vect_a[k_2];
                        k++;
                        res_mat->linked_list_ia[k] = mat_1->linked_list_ia[k_1];
                        res_mat->vect_ja[k] = mat_1->vect_ja[k_1];
                        res_mat->vect_a[k] = mat_1->vect_a[k_1];
                        k++;
                        k_1++;
                        k_2++;
                    }
                    else if (mat_1->vect_ja[k_1 + 1] == mat_2->vect_ja[k_2] )
                    {
                        if (mat_1->linked_list_ia[k_1 + 1] == mat_2->linked_list_ia[k_2])
                        {
                            res_mat->linked_list_ia[k] = mat_1->linked_list_ia[k_1];
                            res_mat->vect_ja[k] = mat_1->vect_ja[k_1];
                            res_mat->vect_a[k] = mat_1->vect_a[k_1];
                            k++;
                            k_1++;
                            res_mat->linked_list_ia[k] = mat_2->linked_list_ia[k_2];
                            res_mat->vect_ja[k] = mat_2->vect_ja[k_2];
                            res_mat->vect_a[k] = mat_2->vect_a[k_2] + mat_1->vect_a[k_1];
                            k++;
                            k_1++;
                            k_2++;
                        }
                        else
                        {
                            res_mat->linked_list_ia[k] = mat_1->linked_list_ia[k_1];
                            res_mat->vect_ja[k] = mat_1->vect_ja[k_1];
                            res_mat->vect_a[k] = mat_1->vect_a[k_1];
                            k++;
                            res_mat->linked_list_ia[k] = mat_2->linked_list_ia[k_2];
                            res_mat->vect_ja[k] = mat_2->vect_ja[k_2];
                            res_mat->vect_a[k] = mat_2->vect_a[k_2];
                            k++;
                            k_1++;
                            k_2++;
                        }
                    }
                    else if (mat_1->vect_ja[k_1 + 1] < mat_2->vect_ja[k_2])
                    {
                        res_mat->linked_list_ia[k] = mat_1->linked_list_ia[k_1];
                        res_mat->vect_ja[k] = mat_1->vect_ja[k_1];
                        res_mat->vect_a[k] = mat_1->vect_a[k_1];
                        k++;
                        k_1++;
                    }
                }
                else if (mat_1->vect_ja[k_1] > mat_2->vect_ja[k_2])
                {
                    if (mat_2->vect_ja[k_2 + 1] > mat_1->vect_ja[k_1])
                    {
                        res_mat->linked_list_ia[k] = mat_2->linked_list_ia[k_2];
                        res_mat->vect_ja[k] = mat_2->vect_ja[k_2];
                        res_mat->vect_a[k] = mat_2->vect_a[k_2];
                        k++;
                        res_mat->linked_list_ia[k] = mat_1->linked_list_ia[k_1];
                        res_mat->vect_ja[k] = mat_1->vect_ja[k_1];
                        res_mat->vect_a[k] = mat_1->vect_a[k_1];
                        k++;
                        k_1++;
                        k_2++;
                    }
                    else if (mat_2->vect_ja[k_2 + 1] == mat_1->vect_ja[k_1])
                    {
                        if (mat_2->linked_list_ia[k_2 + 1] == mat_1->linked_list_ia[k_1])
                        {
                            res_mat->linked_list_ia[k] = mat_2->linked_list_ia[k_2];
                            res_mat->vect_ja[k] = mat_2->vect_ja[k_2];
                            res_mat->vect_a[k] = mat_2->vect_a[k_2];
                            k++;
                            k_2++;
                            res_mat->linked_list_ia[k] = mat_1->linked_list_ia[k_1];
                            res_mat->vect_ja[k] = mat_1->vect_ja[k_1];
                            res_mat->vect_a[k] = mat_1->vect_a[k_1] + mat_2->vect_a[k_2];
                            k++;
                            k_1++;
                            k_2++;
                        }
                        else
                        {
                            res_mat->linked_list_ia[k] = mat_2->linked_list_ia[k_2];
                            res_mat->vect_ja[k] = mat_2->vect_ja[k_2];
                            res_mat->vect_a[k] = mat_2->vect_a[k_2];
                            k++;
                            res_mat->linked_list_ia[k] = mat_1->linked_list_ia[k_1];
                            res_mat->vect_ja[k] = mat_1->vect_ja[k_1];
                            res_mat->vect_a[k] = mat_1->vect_a[k_1];
                            k++;
                            k_1++;
                            k_2++;
                        }
                    }
                    else if (mat_2->vect_ja[k_2 + 1] < mat_1->vect_ja[k_1])
                    {
                        res_mat->linked_list_ia[k] = mat_2->linked_list_ia[k_2];
                        res_mat->vect_ja[k] = mat_2->vect_ja[k_2];
                        res_mat->vect_a[k] = mat_2->vect_a[k_2];
                        k++;
                        k_2++;
                    }
                }
            }
            else if (mat_1->linked_list_ia[k_1] > mat_2->linked_list_ia[k_2])
            {
                res_mat->linked_list_ia[k] = mat_2->linked_list_ia[k_2];
                res_mat->vect_ja[k] = mat_2->vect_ja[k_2];
                res_mat->vect_a[k] = mat_2->vect_a[k_2];
                k++;
                k_2++;
            }
            else if (mat_1->linked_list_ia[k_1] < mat_2->linked_list_ia[k_2])
            {
                res_mat->linked_list_ia[k] = mat_1->linked_list_ia[k_1];
                res_mat->vect_ja[k] = mat_1->vect_ja[k_1];
                res_mat->vect_a[k] = mat_1->vect_a[k_1];
                k++;
                k_1++;
            }
            //printf("%d",k);
            //printf("~%d~~%d~", k_1, k_2);
        }
        else if (k_2 < mat_2->elems)
        {
            res_mat->linked_list_ia[k] = mat_2->linked_list_ia[k_2];
            res_mat->vect_ja[k] = mat_2->vect_ja[k_2];
            res_mat->vect_a[k] = mat_2->vect_a[k_2];
            k++;
            k_2++;
        }
        else if (k_1 < mat_1->elems)
        {
            res_mat->linked_list_ia[k] = mat_1->linked_list_ia[k_1];
            res_mat->vect_ja[k] = mat_1->vect_ja[k_1];
            res_mat->vect_a[k] = mat_1->vect_a[k_1];
            k++;
            k_1++;
        }
    }
    //printf("~%d~~%d~", k_1, k_2);
}

int res_size(sparse_matrix_t *mat_1, sparse_matrix_t *mat_2)
{
    int num = 0;
    for (int i = 0; i < mat_1->rows; i++)
    {
        if (mat_1->linked_list_ia[i] == mat_1->linked_list_ia[i + 1])
            continue;
        else
        {
            if (mat_2->linked_list_ia[i] == mat_2->linked_list_ia[i + 1])
                continue;
            else
                for (int j_a = mat_1->linked_list_ia[i]; j_a < mat_1->linked_list_ia[i + 1]; j_a++)
                    for (int j_b = mat_2->linked_list_ia[i]; j_b < mat_2->linked_list_ia[i + 1]; j_b++)
                        if (mat_1->vect_ja[j_a] == mat_2->vect_ja[j_b])
                            num++;
        }
    }
    num += ((mat_1->elems - num) + (mat_2->elems - num));
    return num;
}

void print_arr(sparse_matrix_t *mat)
{
    sort_matrix(mat);
    printf("a = ");
    for(int i = 0; i < mat->elems; i++)
        if (mat->vect_a[i] != 0)
            printf("%d ", mat->vect_a[i]);
    
    printf("\nja = ");
    for(int i = 0; i < mat->elems; i++)
        if (mat->vect_a[i] != 0)
            printf("%d ", mat->vect_ja[i]);

    printf("\nia = ");
    for(int i = 0; i < mat->rows + 1; i++)
        printf("%d ", mat->linked_list_ia[i]);
    printf("\n");
}

int sparce_addition(void)
{
    int error_code;

    sparse_matrix_t matrix;

    error_code = read_matrix_size(&matrix.rows, &matrix.columns);

    if (error_code)
        return error_code;
    
    int method;
    int fill_size;
    int zero_flag = 0;

    error_code = get_method(&method, &fill_size);

    if (error_code)
        return error_code;
    
    if (method == 1)
    {
        error_code = read_sparce_no_zero(&matrix);

        if (error_code)
            return error_code;
        
        error_code = create_sparce_matrix(&matrix);

        if (error_code)
            return error_code;

        error_code = read_sparce_matrix(&matrix);

        if (error_code)
        {
            free_sparce_matrix(&matrix);
            return error_code;
        }
    }
    else if (method == 2)
    {
        matrix.elems = matrix.rows * matrix.columns * fill_size/100;

        if (matrix.elems != 0)
        {
            error_code = create_sparce_matrix(&matrix);

            if (error_code)
                return error_code;
        
            error_code = random_sparce_matrix(&matrix);

            if (error_code)
            {
                free_sparce_matrix(&matrix);
                return error_code;
            }
        }
        else
            zero_flag = 1;
    }
    print_arr(&matrix);
    sparse_matrix_t matrix_2;
    
    matrix_2.rows = matrix.rows;
    matrix_2.columns = matrix.columns;

    int zero_flag_2 = 0;

    error_code = get_method(&method, &fill_size);

    if (error_code)
        return error_code;
    
    if (method == 1)
    {
        error_code = read_sparce_no_zero(&matrix_2);

        if (error_code)
        {
            free_sparce_matrix(&matrix);
            return error_code;
        }
        error_code = create_sparce_matrix(&matrix_2);

        if (error_code)
        {
            free_sparce_matrix(&matrix);
            return error_code;
        }
        error_code = read_sparce_matrix(&matrix_2);

        if (error_code)
        {
            free_sparce_matrix(&matrix);
            free_sparce_matrix(&matrix_2);
            return error_code;
        }
    }
    else if (method == 2)
    {
        matrix_2.elems = matrix_2.rows * matrix_2.columns * fill_size/100;

        if (matrix_2.elems != 0)
        {
            error_code = create_sparce_matrix(&matrix_2);

            if (error_code)
            {
                free_sparce_matrix(&matrix);
                return error_code;
            }
            error_code = random_sparce_matrix(&matrix_2);

            if (error_code)
            {
                free_sparce_matrix(&matrix);
                free_sparce_matrix(&matrix_2);
                return error_code;
            }
        }
        else
            zero_flag_2 = 1;
    }
    print_arr(&matrix_2);

    printf("\nРезультирующая матрица\n");

    if (zero_flag && zero_flag_2)
    {
        print_zero_matrix(&matrix);
        return OK;
    }

    
    sparse_matrix_t res_matrix;

    res_matrix.rows = matrix.rows;
    res_matrix.columns = matrix.columns;

    if (zero_flag)
    {
        print_arr(&matrix_2);
        free_sparce_matrix(&matrix_2);
        return OK;
    }
    else if (zero_flag_2)
    {
        print_arr(&matrix);
        free_sparce_matrix(&matrix);
        return OK;
    }

    res_matrix.elems = res_size(&matrix, &matrix_2);

    error_code = create_sparce_matrix(&res_matrix);

    if (error_code)
    {
        free_sparce_matrix(&matrix);
        free_sparce_matrix(&matrix_2);
        return error_code;
    }
    addition_sparce(&res_matrix, &matrix, &matrix_2);

    printf("\nРезультирующая матрица в разряженном виде\n");

    print_arr(&res_matrix);

    free_sparce_matrix(&matrix);
    free_sparce_matrix(&matrix_2);
    free_sparce_matrix(&res_matrix);

    return OK;
}