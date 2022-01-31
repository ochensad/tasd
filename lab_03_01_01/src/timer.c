#include "../inc/timer.h"
#include <time.h>
#include <stdio.h>
#include <inttypes.h>


double timer(matrix_t *matrix, matrix_t *matrix_2, matrix_t *matrix_3, void (*func) (matrix_t*, matrix_t*, matrix_t*))
{
    clock_t start = clock();
    for (size_t i = 0; i < 3; i++)
    {
        func(matrix, matrix_2, matrix_3);
    }
    clock_t end = clock() - start;
    return (double)end/3.0/CLOCKS_PER_SEC;
}

double timer_s(sparse_matrix_t *res, sparse_matrix_t *m_1, sparse_matrix_t *m_2, void (*func) (sparse_matrix_t*, sparse_matrix_t*, sparse_matrix_t*))
{
    clock_t start = clock();
    for (size_t i = 0; i < 3; i++)
    {
        func(res, m_1, m_2);
    }
    clock_t end = clock() - start;
    return (double)end/3.0/CLOCKS_PER_SEC;
}

void time_check(int num, int pr, double *t_s, double *t_sp, size_t *m_s, size_t *m_sp)
{   
    matrix_t matrix_1;
    matrix_1.rows = num;
    matrix_1.columns = num;
    create_simple_matrix(&matrix_1);
    matrix_t matrix_2;
    matrix_2.rows = num;
    matrix_2.columns = num;
    create_simple_matrix(&matrix_2);
    matrix_t matrix_res;
    matrix_res.rows = matrix_1.rows;
    matrix_res.columns = matrix_1.columns;
    create_simple_matrix(&matrix_res);

    sparse_matrix_t mat_s_1;
    mat_s_1.rows = num;
    mat_s_1.columns = num;
    mat_s_1.elems = mat_s_1.rows * mat_s_1.columns * pr/100;

    create_sparce_matrix(&mat_s_1);
    random_sparce_matrix(&mat_s_1);

    sparse_matrix_t mat_s_2;
    mat_s_2.rows = num;
    mat_s_2.columns = num;
    mat_s_2.elems = mat_s_2.rows * mat_s_2.columns * pr/100;
    create_sparce_matrix(&mat_s_2);
    random_sparce_matrix(&mat_s_2);

    sparse_matrix_t mat_s_res;
    mat_s_1.rows = num;
    mat_s_1.columns = num;
    mat_s_res.elems = res_size(&mat_s_1, &mat_s_2);
    create_sparce_matrix(&mat_s_res);

    random_simple_matrix(&matrix_1, pr);
    random_simple_matrix(&matrix_2, pr);

    double time_sp;
    time_sp = timer_s(&mat_s_res, &mat_s_1, &mat_s_2, addition_sparce);
    *m_sp = 2 * sizeof(int) * mat_s_1.elems + sizeof(int) * (mat_s_1.rows + 1);

    double time_s;
    time_s = timer(&matrix_res, &matrix_1, &matrix_2, addition_simple);
    *m_s = matrix_1.rows * matrix_1.columns * sizeof(int);


    *t_s = time_s;
    *t_sp = time_sp;

    free_matrix(matrix_1.matrix, matrix_1.rows);
    free_matrix(matrix_2.matrix, matrix_2.rows);
    free_matrix(matrix_res.matrix, matrix_res.rows);

    free_sparce_matrix(&mat_s_res);
    free_sparce_matrix(&mat_s_1);
    free_sparce_matrix(&mat_s_2);
}

void time_table(void)
{
    int rows;
    printf("\nВведите размер матриц (матрицы квадратные) ");
    scanf("%d", &rows);
    int pr;
    printf("\nВведите процент заполнения ");
    scanf("%d", &pr);

    printf("\n| %-10s| %-13s| %-13s| %-13s|", " Размер  ", "Процент заполнения", "Обычная матрица", "Разреженная матрица");
    
    double t_1;
    double t_2;
    size_t m_1;
    size_t m_2;

    time_check(rows, pr, &t_1, &t_2, &m_1, &m_2);
    printf("\n| %-4dx%-4d| %-19d | t-%-9lf m-%-9zu| t-%-9lf m-%-9zu|", rows, rows, pr, t_1, m_1, t_2, m_2);
}

void print_result(int64_t start, int64_t end)
{
    printf("      %lld тактов, %.10lf секунд\n", end - start, (double)(end - start)/HZ);  
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

int comparison(const int fill_percentage, const int numb_rows, const int numb_columns)
{
    int64_t start = 0, end = 0;
    int r;

    matrix_t matrix;

    matrix.rows = numb_rows;
    matrix.columns = numb_columns;

    r = create_simple_matrix(&matrix);

    if (r)
        return r;

    r = random_simple_matrix(&matrix, fill_percentage);

    if (r == ERROR_INVALID_MATRIX)
    {
        free_matrix(matrix.matrix, matrix.rows);
        return OK;
    }

    matrix_t matrix_2;

    matrix_2.rows = numb_rows;
    matrix_2.columns = numb_columns;

    r = create_simple_matrix(&matrix_2);

    if (r)
    {
        free_matrix(matrix.matrix, matrix.rows);
        return r;
    }

    r = random_simple_matrix(&matrix_2, fill_percentage);

    if (r == ERROR_INVALID_MATRIX)
    {
        free_matrix(matrix.matrix, matrix.rows);
        free_matrix(matrix_2.matrix, matrix_2.rows);
        return OK;
    }

    matrix_t res_matrix;

    res_matrix.rows = matrix.rows;
    res_matrix.columns = matrix.columns;

    r = create_simple_matrix(&res_matrix);

    if (r)
    {
        free_matrix(matrix.matrix, matrix.rows);
        free_matrix(matrix_2.matrix, matrix_2.rows);
        return r;
    }

    printf("\nОбычные матрицы (%dx%d и %dx%d)            ",
        matrix.rows, matrix.columns, matrix_2.rows, matrix_2.columns);

    for (int i = 0; i < NUMBER_OF_RUNS; i++)
    {
        start += tick();
        addition_simple(&res_matrix, &matrix, &matrix_2);
        end += tick();
    }

    free_matrix(matrix.matrix, matrix.rows);
    free_matrix(matrix_2.matrix, matrix_2.rows);
    free_matrix(res_matrix.matrix, res_matrix.rows);

    print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
    printf("Затраченная память под массив %dx%d - %llu байт\n\n", 
        matrix.rows, matrix.columns, 
        sizeof(matrix.matrix[0][0]) * matrix.rows * matrix.columns);

    start = 0;
    end = 0;

    sparse_matrix_t s_matrix;

    s_matrix.rows = numb_rows;
    s_matrix.columns = numb_columns;

    s_matrix.elems = s_matrix.rows * s_matrix.columns * fill_percentage/100;

    r = create_sparce_matrix(&s_matrix);

    if (r)
        return r;

    r = random_sparce_matrix(&s_matrix);

    if (r == ERROR_INVALID_MATRIX)
    {
        free_sparce_matrix(&s_matrix);
        return OK;
    }

    sparse_matrix_t s_matrix_2;

    s_matrix_2.rows = s_matrix.rows;
    s_matrix_2.columns = s_matrix.columns;

    s_matrix_2.elems = s_matrix_2.rows * s_matrix_2.columns * fill_percentage/100;

    r = create_sparce_matrix(&s_matrix_2);

    if (r)
    {
        free_sparce_matrix(&s_matrix);
        return r;
    }

    r = random_sparce_matrix(&s_matrix_2);

    if (r == ERROR_INVALID_MATRIX)
    {
        free_sparce_matrix(&s_matrix);
        free_sparce_matrix(&s_matrix_2);
        return OK;
    }

    sparse_matrix_t s_res_matrix;

    s_res_matrix.rows = s_matrix.rows;
    s_res_matrix.columns = s_matrix.columns;
    s_res_matrix.elems= res_size(&s_matrix, &s_matrix_2);

    r = create_sparce_matrix(&s_res_matrix);

    if (r)
    {
        free_sparce_matrix(&s_matrix);
        free_sparce_matrix(&s_matrix_2);
        return r;
    }

    printf("Матрицы в особой форме (%dx%d и %dx%d)     ",
        s_matrix.rows, s_matrix.columns, s_matrix_2.rows, s_matrix_2.columns);

    for (int i = 0; i < NUMBER_OF_RUNS; i++)
    {
        start += tick();

        res_mat(&s_res_matrix, &s_matrix, &s_matrix_2);

        end += tick();
    }

    free_sparce_matrix(&s_matrix);
    free_sparce_matrix(&s_matrix_2);
    free_sparce_matrix(&s_res_matrix);

    print_result(start / NUMBER_OF_RUNS, end / NUMBER_OF_RUNS);
    printf("Затраченная память под массив %dx%d - %llu байт\n\n", 
        s_matrix.rows, s_matrix.columns, 
        sizeof(s_matrix.vect_a[0]) * s_matrix.elems + 
        sizeof(s_matrix.vect_ja[0]) * s_matrix.elems + 
        sizeof(s_matrix.linked_list_ia[0]) * (s_matrix.rows + 1));

    return OK;
}

int comparison_time_memory(void)
{
    int r;

    printf("                                "
           "Матрицы заполнены на %d%%\n", FILL_PERCENTAGE_1);

    r = comparison(FILL_PERCENTAGE_1, NUMBER_ROWS_1, NUMBER_COLUMNS_1);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_1, NUMBER_ROWS_2, NUMBER_COLUMNS_2);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_1, NUMBER_ROWS_3, NUMBER_COLUMNS_3);

    if (r)
        return r;

    printf("                                "
           "Матрицы заполнены на %d%%\n", FILL_PERCENTAGE_2);

    r = comparison(FILL_PERCENTAGE_2, NUMBER_ROWS_1, NUMBER_COLUMNS_1);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_2, NUMBER_ROWS_2, NUMBER_COLUMNS_2);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_2, NUMBER_ROWS_3, NUMBER_COLUMNS_3);

    if (r)
        return r;

    printf("                                "
           "Матрицы заполнены на %d%%\n", FILL_PERCENTAGE_3);

    r = comparison(FILL_PERCENTAGE_3, NUMBER_ROWS_1, NUMBER_COLUMNS_1);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_3, NUMBER_ROWS_2, NUMBER_COLUMNS_2);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_3, NUMBER_ROWS_3, NUMBER_COLUMNS_3);

    if (r)
        return r;

    printf("                                "
           "Матрицы заполнены на %d%%\n", FILL_PERCENTAGE_4);

    r = comparison(FILL_PERCENTAGE_4, NUMBER_ROWS_1, NUMBER_COLUMNS_1);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_4, NUMBER_ROWS_2, NUMBER_COLUMNS_2);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_4, NUMBER_ROWS_3, NUMBER_COLUMNS_3);

    if (r)
        return r;

    printf("                                "
           "Матрицы заполнены на %d%%\n", FILL_PERCENTAGE_5);

    r = comparison(FILL_PERCENTAGE_5, NUMBER_ROWS_1, NUMBER_COLUMNS_1);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_5, NUMBER_ROWS_2, NUMBER_COLUMNS_2);

    if (r)
        return r;

    r = comparison(FILL_PERCENTAGE_5, NUMBER_ROWS_3, NUMBER_COLUMNS_3);

    if (r)
        return r;

    
    return OK;
}



