/*
Ляпина Наталья Викторовна ИУ7-32Б
Задание №1
Вариант №1

Задача:
Смоделировать операцию деления действительного числа в
форме +-m.n Е +-K, где суммарная длина мантиссы (m+n) - до
30 значащих цифр, а величина порядка K - до 5 цифр, на
целое число длиной до 30 десятичных цифр. Результат
выдать в форме +-0.m1 Е +-K1, где m1 - до 30 значащих цифр,
а K1 - до 5 цифр.
*/

#include "func.h"

int main(void)
{
    //"Зануление" всех переменных
    real_t real_s;
    int_t integer_s;
    size_t man_r = 0, man_i = 0, man_res = 0;
    num_t real = {.exp_sign = '+', .num_sign = '+', .order = 0}; 
    num_t integer = {.exp_sign = '+', .num_sign = '+'};
    num_t result = {.exp_sign = '+', .num_sign = '+', .order = 0};
	zeros_in_massive(&real);
    zeros_in_massive(&integer);

    //Отмена буферизации для корректной работы printf
    setbuf(stdout, NULL);

    printf("Программа предназначена для моделирования операции деления\nдействительного числа на целое число.\n\n");

    printf("Введите действительное число в формате: +-m.nE+-k, где m+n <= 30,\n k - порядок числа, который меньше по модулю 100000.\n");
    printf("Корректный ввод: 0.125  125. 125.521E5 12E5 +25.000E-80\n");
    printf("Число вводится без пробелов.\n");
    printf("      ---------+---------+---------+-E------\n");
    printf("Ввод: ");
    //Чтение действиетльного числа
    if (read_real(real_s) == ERROR_LEN)
        return ERROR_LEN;
    //Проверка действительного числа
    if (is_real(real_s, &real, &man_r) != OK)
        return ERROR_MANT_LEN;

    printf("\n\nВведите целое число в десятичном представлении\nс количеством разрядов не больше 30.\n");
    printf("Корректный ввод: 0  -125  43534\n");
    printf("Число вводится без пробелов.\n");
    printf("      ---------+---------+---------+-\n");
    printf("Ввод: ");
    //Чтение целого числа
    if (read_int(integer_s) != OK)
        return ERROR_LEN;

    //Проверка целого числа
    if (is_integer(integer_s, &integer, &man_i) != OK)
        return ERROR_SYMBOLS;
    
    //Нормализация целого и десятичного чисел
    normalization(&real, &man_r);
    normalization(&integer, &man_i);
    
    //Одно из чисел равно 0
    if (real.mantissa[0] == 0)
    {
        if (integer.mantissa[0] == 0)
        {
            printf("\nОШИБКА:\nРезультат не может быть получен (деление на ноль).");
            return ERROR_ZERO_FIRST;
        }
        else
        {
            printf("\n\nОтвет: 0.0E0");
            return OK;
        }
    }
    if (integer.mantissa[0] == 0)
    {
        printf("\nОШИБКА:\nРезультат не может быть получен (деление на ноль).");
        return ERROR_ZERO_FIRST;
    }
    
    //Сдвигаем числа в конец мантиссы
    move_num_end(&integer, &man_i);
    move_num_end(&real, &man_r);

    //Порядок результата деления
    result.order += (real.order - integer.order + 1);

    //Сдвиг относительно порядков чисел
    size_t diff = man_r - man_i;
    if (diff > 1)
        move_digits(&real, NMAX, diff);

    //Проверка на переполнение
    if (abs(result.order) > MAX_EXP)
    {
        printf("\nОШИБКА:\nВыход за пределы допустимого порядка результирующего числа.");
        return ERROR_ORDER;
    }
    //Получение результирующего знака
    if (result.order > 0)
        result.exp_sign = '+';
    else
        result.exp_sign = '-';
    
    if (real.num_sign == integer.num_sign)
        result.num_sign = '+';
    else
        result.num_sign = '-';

    //Деление чисел
    if (division(&real, &integer, &result, NMAX) == 0)
    {
        //Знак результата деления
        if (result.num_sign == '-')
            printf("\nОтвет: -0.");
        else
            printf("\n Ответ: 0.");
        
        //Размер мантисы результата деления
        for (size_t k = 0; k < NMAX; k++)
        {
            if (result.mantissa[k])
                man_res = k + 1;
        }
        
        if (result.mantissa[man_res] != 0)
            man_res++;
        //Печать результата деления
        for (size_t k = 0; k < man_res; k++)
            printf("%d", result.mantissa[k]);
        
        printf("E%d", result.order);
    }
    else
        return ERROR_DIVISION;
    
    return OK;
}