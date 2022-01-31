#include "menu.h"
#include <stdio.h>

int read_comand_main(int *comand)
{
    printf("Введите команду:\n"
            "   1 - сравнение работы двух реализаций очереди по времени и памяти;\n"
            "   2 - смоделировать обработку очереди;\n"
            "   0 - выход из программы.\n\n");
    
    if (scanf("%d", comand) != 1)
    {
        printf("Ошибка при чтении команды\n");
        return ERROR_READING;
    }
    else if (*comand < 0 || *comand > 2)
    {
        printf("Ошибка. Несуществующая команда\n");
        return ERROR_COMAND;
    }
    return OK;
}

int read_comand(int *comand)
{
    printf("\n"
        "1. Добавить элементы в очередь;\n"
        "2. Добавить случайные элементы в очередь;\n"
        "3. Удалить элементы из очереди;\n"
        "4. Вывести текущее состояние очереди (массив);\n"
        "5. Вывести текущее состояние очереди (список);\n"
        "6. Вывести массив освобождённых адресов;\n"
        "0. Выйти из программы.\n\n");

    printf("Введите команду: ");

    if (scanf("%d", comand) != 1)
    {
        printf("Ошибка при чтении команды\n");
        return ERROR_READING;
    }
    else if (*comand < 0 || *comand > 6)
    {
        printf("Ошибка. Несуществующая команда\n");
        return ERROR_COMAND;
    }
    return OK;
}

