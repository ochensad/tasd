#include "../inc/records.h"
#include <string.h>
#include <ctype.h>

int char_check(FILE *f, size_t max_len, char *str)
{
    int error_code = OK;

    char buf[max_len + 2];
    error_code = fscanf(f, "%s", buf);

    if (error_code != 1)
        return ERROR_READING;
    
    if (strlen(buf) > max_len)
        return ERROR_LEN;
    
    for (size_t i = 0; i < strlen(buf) - 1; i++)
        if (isalpha((int)buf[i]) == 0)
            return ERROR_INVALID_CHAR;
    
    strncpy(str, buf, max_len);
    error_code = OK;
    return error_code;
}

int new_car_read(FILE *f, new_t *new)
{
    int error_code;

    error_code = fscanf(f, "%d", &(new->garanty_till));

    if (error_code != 1)
        return ERROR_READING;
    
    if (new->garanty_till <= 0)
        return ERROR_GARANTY;
    return OK;
}

int old_car_read(FILE *f, old_t *old)
{
    int error_code;

    error_code = fscanf(f, "%d", &(old->year));
    if (error_code != 1)
        return ERROR_READING;
    if (old->year <= 0)
        return ERROR_OLD;
    
    error_code = fscanf(f, "%d", &(old->mileage));
    if (error_code != 1)
        return ERROR_READING;
    if (old->mileage <= 0)
        return ERROR_OLD;

    error_code = fscanf(f, "%d", &(old->repairs_num));
    if (error_code != 1)
        return ERROR_READING;
    if (old->repairs_num < 0)
        return ERROR_OLD;

    error_code = fscanf(f, "%d", &(old->owners));
    if (error_code != 1)
        return ERROR_READING;
    if (old->owners < 0)
        return ERROR_OLD;

    return OK;
}

int read_record(FILE *f, car_t *car)
{
    int error_code;

    error_code = char_check(f, CAR_NAME_LEN, car->car_name);

    if (error_code)
    {
        if (error_code == ERROR_READING)
            printf("Ошибка при чтении имени машины\n");
        else if (error_code == ERROR_LEN)
            printf("Ошибка переполнения имени машины\n");
        else if (error_code == ERROR_INVALID_CHAR)
            printf("Недопустимый символ в имени машины\n");
        return error_code;
    }

    error_code = char_check(f, COUNTRY_NAME_LEN, car->country);

    if (error_code)
    {
        if (error_code == ERROR_READING)
            printf("Ошибка при чтении страны машины\n");
        else if (error_code == ERROR_LEN)
            printf("Ошибка переполнения страны машины\n");
        else if (error_code == ERROR_INVALID_CHAR)
            printf("Недопустимый символ в названии страны машины\n");
        return error_code;
    }

    error_code = fscanf(f, "%d", &(car->price));

    if (error_code != 1)
    {
        printf("Ошибка при чтении цены машины\n");
        error_code = ERROR_PRICE;
        return error_code;
    }
    if (car->price <= 0)
    {
        printf("Ошибка недопустимое значение цены\n");
        error_code = ERROR_PRICE;
        return error_code;
    }

    error_code = char_check(f, COLOR_LEN, car->color);

    if (error_code)
    {
        if (error_code == ERROR_READING)
            printf("Ошибка при чтении цвета машины\n");
        else if (error_code == ERROR_LEN)
            printf("Ошибка переполнения цвета машины\n");
        else if (error_code == ERROR_INVALID_CHAR)
            printf("Недопустимый символ в цвете машины\n");
        return error_code;
    }

    error_code = char_check(f, CONDITION_LEN, car->condition);
    if (error_code)
    {
        if (error_code == ERROR_READING)
            printf("Ошибка при чтении состояния машины\n");
        else if (error_code == ERROR_LEN)
            printf("Ошибка переполнения состояния машины\n");
        else if (error_code == ERROR_INVALID_CHAR)
            printf("Недопустимый символ в состоянии машины\n");
        return error_code;
    }

    if (strcmp(car->condition, "new") == 0)
        error_code = new_car_read(f, &(car->car_type.new_car));
    else if (strcmp(car->condition, "old") == 0)
        error_code = old_car_read(f, &(car->car_type.old_car));
    else
    {
        printf("Ошибка недопустимое состояние\n");
        error_code = ERROR_CONDITION;
        return error_code;
    }

    return error_code;
}

int compare(car_t *car, char *name, int price_min, int price_max)
{
    int own = 1;
    int rep = 0;

    if (strcmp(car->car_name, name) != 0)
        return NO;
    if (strcmp(car->condition, "old") != 0)
        return NO;
    if (car->car_type.old_car.owners != own)
        return NO;
    if (car->car_type.old_car.repairs_num != rep)
        return NO;
    if (car->price < price_min || car->price > price_max)
        return NO;
    return OK;
}