#include "../inc/menu.h"

void print_menu(void)
{
        printf("\n"
        "1. Смоделировать операцию сложения двух матриц,\n"
        "   хранящихся в особой форме, с получением результата в той же форме.\n"
        "2. Произвести операцию сложения, "
        "применяя стандартный алгоритм работы с матрицами.\n"
        "3. Сравнить время выполнения операций и объем памяти при использовании\n"
        "   этих 2-х алгоритмов при различном проценте заполнения матриц.\n"
        "0. Выйти из программы.\n\n"
        "Особая форма:\n"
        "Разреженная матрица хранится в форме 3-х объектов:\n"
        "   - вектор A содержит значения ненулевых элементов;\n"
        "   - вектор JA содержит номера столбцов для элементов вектора A;\n"
        "   - связный список IA, в элементе Nk которого находится номер компонент\n"
        "     в A и JA, с которых начинается описание строки Nk матрицы A.\n\n");
}

int get_comand(int *comand)
{
    int error_code;

    printf("Введите номер команды: ");

    error_code = scanf("%d", comand);

    if (error_code != 1)
    {
        printf("\nОшибка при чтении команды\n");
        return ERROR_INVALID_COMAND;
    }
    else if (*comand < MIN_COMAND || *comand > MAX_COMAND)
    {
        printf("\n\n");
        return ERROR_NO_COMAND;
    }
    return OK;
}