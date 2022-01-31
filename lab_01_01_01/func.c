#include "func.h"

//Функция присваивает нули всем элементам массива структуры
void zeros_in_massive(num_t *num)
{
  for (int i = 0; i < NMAX; i++)
  num->mantissa[i] = 0;
}

//Удаление лидирующих нулей массива
int normalization(num_t *data, size_t *n)
{
    int count = 0;
    while (data->mantissa[0] == 0 && *n > 0)
    {
        for (size_t i = 1; i < *n; i++)
            data->mantissa[i - 1] = data->mantissa[i];
        *n = *n - 1;
        if (count != 0)
            data->order += 1;
        data->mantissa[*n] = 0;
        count += 1;
    }
    return OK;
}

//Функция сдвигает число из начала в конец мантиссы
int move_num_end(num_t *data, size_t *n)
{
	size_t i = NMAX - 1;
	size_t j = *n;
	
	while (j > 0)
	{
        data->mantissa[i] = data->mantissa[j - 1];
		data->mantissa[j - 1] = 0;
        i--;
        j--;
    }
    return OK;
}

//функция двигает данные массива относительно его конца для выравнивания порядков 
//и для того, чтобы было возможно произвести операцию вычитания 
void move_digits(num_t *num, int size, int offset)
{
    if (offset <= -1)
    {
        offset *= -1;
        for (int i = 0; i < size - offset; i++)
            num->mantissa[i] = num->mantissa[i+offset];
        for (int i = size - offset; i < size; i++)
            num->mantissa[i] = 0;
    }
    else if (offset >= 1)
    {
        for (int i = size - 1; i >= offset; i--)
            num->mantissa[i] = num->mantissa[i-offset];
        for (int i = offset - 1; i >= 0; i--)
            num->mantissa[i] = 0;
    }
}

//Функция поразрядного сравнения чисел 
int comparison(num_t *real, num_t *integer)
{
	int i = 0;
    int res = 0;
	while (res == 0 && i < NMAX)
	{
		res = real->mantissa[i] - integer->mantissa[i];
		i++;
	}
	return res;
}

//Функция округления при нахождении 31 цифры мантиссы
void rounding(num_t *result, size_t size, int last_digit)
{
    if (last_digit >= 5)
    {
        result->mantissa[size - 1]++;
        for (int i = size - 1; i >= 0; i--)
        {
            if (result->mantissa[i] == 10)
            {
                result->mantissa[i] -= 10;
                result->mantissa[i - 1]++;
            }
            else
                break;
        }
    }
}

//Функция пораздрядного вычетания цифр массивов
void subtract(num_t *real, num_t *integer, int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        if (real->mantissa[i] >= integer->mantissa[i])
            real->mantissa[i] -= integer->mantissa[i];
        else
        {
            real->mantissa[i] += 10 - integer->mantissa[i];
            real->mantissa[i-1]--;
        }
    }
}

//Функция, обЪединяющая в себе логику деления
int division(num_t *real, num_t *integer, num_t *result, int size)
{
    size_t current_pos = 0;
    int equal, flag;
	int counter;
    int flag_zero = 1, beggining_flag = 1;

    while (current_pos < NMAX)
    {
        //Разность между разрядами мантисы
        equal = comparison(real, integer);
        //Действительное и целое число равны
        if (equal == 0)
        {
            result->mantissa[current_pos] = 1;
            break;
        }
        else if (equal > 0)
        {
            flag_zero = 0;
            counter = 0;
            //Пока не найдется одинаковых разрядов
            while ((flag = comparison(real, integer)) >= 0)
            {
                if (flag == 0)
                {
                    counter++;
                    break;
                }
                //Вычитание разрядов
                subtract(real, integer, size);
                counter++;
            }
            //Округление при переполнении мантисы
            if (current_pos == NMAX - 2)
            {
                rounding(result, NMAX - 2, counter);
                break;
            }
            //Запись в мантису результата
            else
            {
                result->mantissa[current_pos++] = counter;
                beggining_flag = 0;
				if (flag == 0)
                    break;
            }
        }
        else
        {
            //Разряд мантисы меньше разряда целого
            if (flag_zero)
            {
                if (beggining_flag)
                    result->order--;
                else
                    result->mantissa[current_pos++] = 0;
            }
            flag_zero = 1;
            move_digits(real, size, -1);
        }
    }
    return OK;
}