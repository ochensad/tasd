#include "int_num.h"

//Функция проверки ввода целого числа
int read_int(int_t s)
{
    int ch;
    int i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if (i < SIMAX)
            s[i++] = ch;
        else
        {
            printf("\nОШИБКА:\nВведенные данные целого числа слишком длинные.");
            return ERROR_LEN;
        }
    }
    s[i] = '\0';
    return OK;
}

//Функция считывает в структуру целого числа данные из строки 
//ввода и в случае неправильного ввода сообщает об ошибке
int is_integer(int_t string, num_t *integer, size_t *man_i)
{
    int i = 0;
    //Проверка на переполнение
    if (strlen(string) > SIMAX - 1)
    {
        printf("\nОШИБКА:\nКоличество цифр целого числа превышает допустимое.\nМаксимальное количество цифр в числе: 30.");
        return ERROR_LEN;
    }
    //Знак числа
    if (string[i] == '-')
    {
        integer->num_sign = '-';
        i++;
    }
    else if (string[i] == '+')    
        i++;
    //Порядок числа
    integer->order = strlen(string) - i;

    while (string[i] != '\0')
    {
        //Проверка символов числа
        if (isdigit((int)string[i]) == 0)
        {
            printf("\nОШИБКА:\nЦелое число введено неправильно (Использованы недопустимые символы).");
            return ERROR_SYMBOLS;
        }
        else
        {
            integer->mantissa[*man_i] = string[i] - '0';
            *man_i = *man_i + 1;
        }
        i++;
    }
    return OK;
}