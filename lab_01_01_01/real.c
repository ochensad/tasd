#include "real.h"

//Функция считывает в структуру действительного числа данные из строки 
//ввода и в случае неправильного ввода сообщает об ошибке
int is_real(real_t string, num_t *real, size_t *man_r)
{
    int i = 0;
    int flag = 1;
    long num;
    long buf = 0;
    long exp = 0;

    if (string[i] == '-')
    {
        real->num_sign = '-';
        i++;
    }
    else if (string[i] == '+')
        i++;
    
    //Проверка мантисы до точки
    while (string[i] != '.' && string[i] != '\0' && string[i] != 'E')
    {
        // Символ является чилом
        if (isdigit((int)string[i]) != 0)
        {
            //Получение числа из символа
            num = string[i] - '0';
            if (num > 0)
                flag = 0;
            //Проверка на переполнение мантисы
            if (*man_r == NMAX - 2)
            {
                printf("\nОШИБКА:\nКоличество цифр мантиссы превышает допустимое.\nМаксимальное количество цифр в мантиссе: 30.");
                return ERROR_MANT_LEN;
            }
            //Проверка на нули перед цифрой 01.1
            else if (num == 0 && string[i + 1] != '.' && i == 0)
            {
                printf("\nОШИБКА:\nДействительное число введено неправильно.");
                return ERROR_ZERO_FIRST;
            }
            //Добавление цифры в мантису
            else if(num >= 0 || flag == 0)
            {
                real->mantissa[*man_r] = num;
                *man_r = *man_r + 1;
                buf = buf + 1; 
            }  
        }
        else
        {
            printf("\nОШИБКА:\nДействительное число введено неправильно (Использованы недопустимые символы).");
            return ERROR_SYMBOLS;
        }
        i++;  
    }
    //Проверка на точку
    if (string[i] == '\0')
    {
        printf("\nОШИБКА:\nНеправильный ввод действительного числа.\nДействительное число должно вводиться с точкой.");
        return ERROR_NO_POINT;
    }
    if (string[i] == '.')
        i++;

    //Проверка мантисы после точки
    while (string[i] != 'E' && string[i] != '\0')
    {
        // Является ли цифрой
        if (isdigit((int)string[i]) != 0)
        {
            num = string[i] - '0';
            // Переполнение мантисы
            if (*man_r == NMAX - 2)
            {
                printf("\nОШИБКА:\nКоличество цифр мантиссы превышает допустимое.\nМаксимальное количество цифр в мантиссе: 30.");
                return ERROR_MANT_LEN;
            }
            // Добавление цифры в мантису
            else
            {
                real->mantissa[*man_r] = num;
                *man_r = *man_r + 1;
            }
        }
        else
        {
            printf("\nОШИБКА:\nДействительное число введено неправильно.");
            return ERROR_SYMBOLS;
        }
        i++;
    }
    // целая часть мантисы состоит из 0
    if (flag == 1)
    {
        buf = 0;
        real->order = 0;
    }
    
    //Порядок не указан
    if (string[i] != 'E')
    {
        real->order += buf;
        return OK;
    }

    i++;
    //Знак порядка
    if (string[i] == '-')
    {
        real->exp_sign = '-';
        i++;
    }
    else if (string[i] == '+')
        i++;
    
    //Проверка порядка
    while (string[i] != '\0')
    {
        if (isdigit((int)string[i]) != 0)
        {
            num = string[i] - '0';
            exp = exp *10 + num;
        }
        else
        {
            printf("\nОШИБКА:\nНеправильный порядок действительного числа.");
            return ERROR_ORDER;
        }
        i++;
    }
    //Нет порядка после знака
    if (string[i] == '\0' && isdigit((int)string[i - 1]) == 0)
    {
        printf("\nОШИБКА:\nНеправильный порядок действительного числа.");
        return ERROR_ORDER; 
    }
    // Запись порядка в структуру
    if (buf == 0)
        real->exp_sign = '-';

    if (real->exp_sign == '-')
        real->order = real->order - exp;
    else
        real->order = real->order + exp;
    // Проверка переполнения порядка
    if (abs(real->order) > MAX_EXP)
    {
        printf("\nОШИБКА:\nКоличество разрядов порядка действительного числа превышает допустимое.\nМаксимальное количество разрядов в порядке: 5");
        return ERROR_ORDER;
    }
    else
        real->order += buf;
        
    return OK;
}

//Функция проверки ввода действительного числа
int read_real(real_t s)
{
    int ch;
    int i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if (i < SRMAX)
            s[i++] = ch;
        else
        {
            printf("\nОШИБКА:\nВведенные данные действительного числа слишком длинные.");
            return ERROR_LEN;
        }
    }
    s[i] = '\0';
    return OK;
}