#include "menu.h"

int read_type(int *s_type)
{
    int error_code;

    printf("Команды:\n"
           "    1 - стек, реализованный с помощью массива;\n"
           "    2 - стек, реализонаееый с помощью списка;\n"
           "    3 - сравнение времени и памяти двух типов стеков\n\n");
    printf("Команда: ");
    error_code = scanf("%d", s_type);

    if (error_code != 1)
    {
        printf("Ошибка при чтении команды\n");
        return ERROR_READING;
    }
    
    if (*s_type < 1 || *s_type > 3)
    {
        printf("Несуществующая команда\n");
        return ERROR_COMAND;
    }
    return OK;
}

int read_comand(int *comand)
{
    printf("\nКоманда: ");
    if (scanf("%d", comand) != 1)
    {
        printf("\nОшибка при чтении\n");
        return ERROR_READING;
    }

    if (*comand < MIN_COM || *comand > MAX_COM)
    {
        printf("\nНедопустимая команда\n");
        return ERROR_COMAND;
    }
    return OK;
}

void print_menu(void)
{
    printf("\n"
        "1. Добавить элементы в стек;\n"
        "2. Добавить случайные элементы в стек;\n"
        "3. Удалить элементы из стека;\n"
        "4. Вывести текущее состояние стека;\n"
        "5. Используя стек, определить является ли строка палиндромом;\n"
        "0. Выйти из программы.\n\n");
}