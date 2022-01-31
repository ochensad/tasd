#include "../inc/comands.h"

int load_table(char *file_name, size_t max_size, table_t *table)
{
    int error_code;

    FILE *f;

    f = fopen(file_name, "r");
    if (f == NULL)
    {
        printf("Ошибка при открытии файла\n");
        error_code = ERROR_OPEN_FILE;
        return error_code;
    }

    error_code = fscanf(f, "%zu", &((table->size)));

    if (error_code != 1)
    {
        error_code = ERROR_CANT_READ_SIZE;
        printf("Ошибка при чтнии размера файла");
        return error_code;
    }

    if (table->size > max_size)
    {
        printf("Ошибка недопустимый размер таблицы\n");
        return ERROR_SIZE_TABLE;
    }
    error_code = OK;

    for (size_t i = 0; i < (table->size); i++)
    {
        error_code = read_record(f, &(table->cars[i]));

        if (error_code)
        {
            printf("Ошибка при чтении строки файла\n");
            return error_code;
        }
    }

    fclose(f);
    get_keys(table);
    return OK;
}

int print_table(table_t *table)
{
    if (table->size == 0)
    {
        printf("Таблица пустая\n");
        return OK;
    }

    for(size_t i = 0; i < LINE_LEN; i++)
        printf("%s", "_");
    
    printf("\n| %-15s| %-20s| %-13s| %-15s| %-9s| %-8s| %-5s| %-7s| %-7s| %-7s|\n", "NAME", "COUNTRY", "PRICE","COLOR", "CONDITION", "GARANTY", "YEAR", "MILEAGE", "REPAIRS", "OWNERS");

    for(size_t i = 0; i < LINE_LEN; i++)
        printf("_");

    for(size_t i = 0; i < table->size; i++)
    {
        if (strcmp((table->cars[i].condition), "new") == 0)
        {
            printf("\n| %-15s| %-20s| %-13d| %-15s| %-9s| %-8d| %-5s| %-7s| %-7s| %-7s|\n", table->cars[i].car_name, table->cars[i].country, table->cars[i].price, table->cars[i].color, table->cars[i].condition, table->cars[i].car_type.new_car.garanty_till, "-", "-","-","-");
        }
        else if (strcmp((table->cars[i].condition), "old") == 0)
        {
            printf("\n| %-15s| %-20s| %-13d| %-15s| %-9s| %-8s| %-5d| %-7d| %-7d| %-7d|\n", table->cars[i].car_name, table->cars[i].country, table->cars[i].price, table->cars[i].color, table->cars[i].condition, "-", table->cars[i].car_type.old_car.year, table->cars[i].car_type.old_car.mileage, table->cars[i].car_type.old_car.repairs_num, table->cars[i].car_type.old_car.owners);
        }
    }
    for(size_t i = 0; i < LINE_LEN; i++)
        printf("_");
    return OK;
}

int add_car(table_t *table)
{
    int error_code;
    table->size++;
    size_t size = table->size - 1;

    if (table->size >= MAX_TABLE_SIZE)
    {
        printf("\nТаблица переполнена\n");
        table->size--;
        return ERROR_SIZE_TABLE;
    }
    printf("\nВведите марку машины: ");
    error_code = char_check(stdin, CAR_NAME_LEN, table->cars[size].car_name);

    if (error_code)
    {
        if (error_code == ERROR_READING)
            printf("\nОшибка при чтении имени машины");
        else if (error_code == ERROR_LEN)
            printf("\nОшибка переполнения имени машины");
        else if (error_code == ERROR_INVALID_CHAR)
            printf("\nНедопустимый символ в имени машины");
        return error_code;
    }

    printf("\nВведите страну производителя: ");
    error_code = char_check(stdin, COUNTRY_NAME_LEN, table->cars[size].country);

    if (error_code)
    {
        if (error_code == ERROR_READING)
            printf("\nОшибка при чтении страны");
        else if (error_code == ERROR_LEN)
            printf("\nОшибка переполнения названия страны");
        else if (error_code == ERROR_INVALID_CHAR)
            printf("\nНедопустимый символ в названии страны");
        return error_code;
    }
    printf("\nВведите цену машины: ");
    error_code = fscanf(stdin,"%d", &table->cars[size].price);
    if (error_code != 1)
    {
        printf("\nОшибка при чтении цены");
        return ERROR_PRICE;
    }
    else if (table->cars[size].price <= 0)
    {
        printf("\nОшибка цена не может быть не натуральной величиной");
        return ERROR_PRICE;
    }

    printf("\nВведите цвет машины: ");
    error_code = char_check(stdin, COLOR_LEN, table->cars[size].color);
    if (error_code)
    {
        if (error_code == ERROR_READING)
            printf("\nОшибка при чтении цвета машины");
        else if (error_code == ERROR_LEN)
            printf("\nОшибка переполнения цвета машины");
        else if (error_code == ERROR_INVALID_CHAR)
            printf("\nНедопустимый символ в цвете машины");
        return error_code;
    }

    printf("\nВведите состояние машины: ");
    error_code = char_check(stdin, CONDITION_LEN, table->cars[size].condition);
    if (error_code)
    {
        if (error_code == ERROR_READING)
            printf("\nОшибка при чтении состояния машины");
        else if (error_code == ERROR_LEN)
            printf("\nОшибка переполнения состояния машины");
        else if (error_code == ERROR_INVALID_CHAR)
            printf("\nНедопустимый символ в состоянии машины");
        return error_code;
    }
    else if (strcmp(table->cars[size].condition, "new") != 0 && strcmp(table->cars[size].condition, "old") != 0)
    {
        printf("\nОшибка недопустимое состояние машины");
        return ERROR_CONDITION;
    }

    if (strcmp(table->cars[size].condition, "new") == 0)
    {
        printf("\nВведите гарантию на машину: ");
        error_code = fscanf(stdin,"%d", &table->cars[size].car_type.new_car.garanty_till);
        if (error_code != 1)
        {
            printf("\nОшибка при чтении гарантии");
            return ERROR_GARANTY;
        }
        else if (table->cars[size].car_type.new_car.garanty_till < 0)
        {
            printf("\nОшибка гарантия не может быть отрицательной");
            return ERROR_GARANTY;
        }
        get_keys(table);
        return OK;
    }
    printf("\nВведите год изготовления машины: ");
    error_code = fscanf(stdin,"%d", &table->cars[size].car_type.old_car.year);
    if (error_code != 1)
    {
        printf("\nОшибка при чтении года");
        return ERROR_OLD;
    }
    else if (table->cars[size].car_type.old_car.year <= 0)
    {
        printf("\nОшибка год не может быть не натуральной величиной");
        return ERROR_OLD;
    }
    printf("\nВведите пробег машины: ");
    error_code = fscanf(stdin,"%d", &table->cars[size].car_type.old_car.mileage);
    if (error_code != 1)
    {
        printf("\nОшибка при чтении пробега");
        return ERROR_OLD;
    }
    else if (table->cars[size].car_type.old_car.mileage <= 0)
    {
        printf("\nОшибка пробег не может быть не натуральной величиной");
        return ERROR_OLD;
    }
    
    printf("\nВведите количество ремонтов машины: ");
    error_code = fscanf(stdin, "%d", &table->cars[size].car_type.old_car.repairs_num);
    if (error_code != 1)
    {
        printf("\nОшибка при чтении количества ремонтов");
        return ERROR_OLD;
    }
    else if (table->cars[size].car_type.old_car.repairs_num < 0)
    {
        printf("\nОшибка количество ремонтов не может быть отрицательной величиной");
        return ERROR_OLD;
    }

    printf("\nВведите количество владельцев машины: ");
    error_code = fscanf(stdin, "%d", &table->cars[size].car_type.old_car.owners);
    if (error_code != 1)
    {
        printf("\nОшибка при чтении количества владельцев");
        return ERROR_OLD;
    }
    else if (table->cars[size].car_type.old_car.owners < 0)
    {
        printf("\nОшибка количество владельцев не может быть отрицательной величиной");
        return ERROR_OLD;
    }
    get_keys(table);
    return OK;
}

int delite_cars(table_t *table)
{
    int error_code;

    printf("\nВведите название поля\nname, country, price, color,\ncondition, garanty, year,\nmillage, repairs, owners: ");

    char line[COUNTRY_NAME_LEN];
    error_code = char_check(stdin, COUNTRY_NAME_LEN, line);
    if (error_code)
    {
        if (error_code == ERROR_READING)
            printf("\nОшибка при чтении поля");
        else if (error_code == ERROR_LEN)
            printf("\nОшибка переполнения поля");
        else if (error_code == ERROR_INVALID_CHAR)
            printf("\nНедопустимый символ в названии поля");
        return error_code;
    }

    size_t i = 0, j = 0;
    car_t buf;
    if (strcmp(line, "name") == 0)
    {
        printf("\nВведите марку машины: ");
        char name[CAR_NAME_LEN];
        error_code = char_check(stdin, CAR_NAME_LEN, name);
        if (error_code)
        {
            if (error_code == ERROR_READING)
                printf("\nОшибка при чтении поля");
            else if (error_code == ERROR_LEN)
                printf("\nОшибка переполнения поля");
            else if (error_code == ERROR_INVALID_CHAR)
                printf("\nНедопустимый символ в названии поля");
            return error_code;
        }

        while(i < table->size - j)
        {
            if (strcmp(table->cars[i].car_name, name) == 0)
            {
                for(size_t k = i; k < table->size - 1 - j; k++)
                {
                    buf = table->cars[k];
                    table->cars[k] = table->cars[k + 1];
                    table->cars[k + 1] = buf;
                }
                j++;
            }
            i++;
        }
    }

    if (strcmp(line, "country") == 0)
    {
        printf("\nВведите название страны: ");
        char country[COUNTRY_NAME_LEN];
        error_code = char_check(stdin, COUNTRY_NAME_LEN, country);
        if (error_code)
        {
            if (error_code == ERROR_READING)
                printf("\nОшибка при чтении поля");
            else if (error_code == ERROR_LEN)
                printf("\nОшибка переполнения поля");
            else if (error_code == ERROR_INVALID_CHAR)
                printf("\nНедопустимый символ в названии поля");
            return error_code;
        }

        while(i < table->size - j)
        {
            if (strcmp(table->cars[i].country, country) == 0)
            {
                for(size_t k = i; k < table->size - 1 - j; k++)
                {
                    buf = table->cars[k];
                    table->cars[k] = table->cars[k + 1];
                    table->cars[k + 1] = buf;
                }
                j++;
            }
            i++;
        }
    }

    if (strcmp(line, "price") == 0)
    {
        int price;
        printf("\nВведите цену машины: ");
        error_code = fscanf(stdin,"%d", &price);
        if (error_code != 1)
        {
            printf("\nОшибка при чтении цены");
            return ERROR_PRICE;
        }
        else if (price <= 0)
        {
            printf("\nОшибка цена не может быть не натуральной величиной");
            return ERROR_PRICE;
        }

        while(i < table->size - j)
        {
            if (table->cars[i].price == price)
            {
                for(size_t k = i; k < table->size - 1 - j; k++)
                {
                    buf = table->cars[k];
                    table->cars[k] = table->cars[k + 1];
                    table->cars[k + 1] = buf;
                }
                j++;
            }
            i++;
        }
    }

    if (strcmp(line, "color") == 0)
    {
        printf("\nВведите цвет машины: ");
        char color[COLOR_LEN];
        error_code = char_check(stdin, COLOR_LEN, color);
        if (error_code)
        {
            if (error_code == ERROR_READING)
                printf("\nОшибка при чтении поля");
            else if (error_code == ERROR_LEN)
                printf("\nОшибка переполнения поля");
            else if (error_code == ERROR_INVALID_CHAR)
                printf("\nНедопустимый символ в названии поля");
            return error_code;
        }

        while(i < table->size - j)
        {
            if (strcmp(table->cars[i].color, color) == 0)
            {
                for(size_t k = i; k < table->size - 1 - j; k++)
                {
                    buf = table->cars[k];
                    table->cars[k] = table->cars[k + 1];
                    table->cars[k + 1] = buf;
                }
                j++;
            }
            i++;
        }
    }

    if (strcmp(line, "condition") == 0)
    {
        printf("\nВведите состояние машины: ");
        char condition[CONDITION_LEN];
        error_code = char_check(stdin, CONDITION_LEN, condition);
        if (error_code)
        {
            if (error_code == ERROR_READING)
                printf("\nОшибка при чтении поля");
            else if (error_code == ERROR_LEN)
                printf("\nОшибка переполнения поля");
            else if (error_code == ERROR_INVALID_CHAR)
                printf("\nНедопустимый символ в названии поля");
            return error_code;
        }

        while(i < table->size - j)
        {
            if (strcmp(table->cars[i].condition, condition) == 0)
            {
                for(size_t k = i; k < table->size - 1 - j; k++)
                {
                    buf = table->cars[k];
                    table->cars[k] = table->cars[k + 1];
                    table->cars[k + 1] = buf;
                }
                j++;
            }
            i++;
        }
    }

    if (strcmp(line, "garanty") == 0)
    {
        int garanty;
        printf("\nВведите гарантию машины: ");
        error_code = fscanf(stdin,"%d", &garanty);
        if (error_code != 1)
        {
            printf("\nОшибка при чтении гарантии");
            return ERROR_PRICE;
        }
        else if (garanty <= 0)
        {
            printf("\nОшибка гарантия не может быть не натуральной величиной");
            return ERROR_PRICE;
        }

        while(i < table->size - j)
        {
            if (table->cars[i].car_type.new_car.garanty_till == garanty)
            {
                for(size_t k = i; k < table->size - 1 - j; k++)
                {
                    buf = table->cars[k];
                    table->cars[k] = table->cars[k + 1];
                    table->cars[k + 1] = buf;
                }
                j++;
            }
            i++;
        }
    }

    if (strcmp(line, "year") == 0)
    {
        int year;
        printf("\nВведите год машины: ");
        error_code = fscanf(stdin,"%d", &year);
        if (error_code != 1)
        {
            printf("\nОшибка при чтении года");
            return ERROR_PRICE;
        }
        else if (year <= 0)
        {
            printf("\nОшибка год не может быть не натуральной величиной");
            return ERROR_PRICE;
        }

        while(i < table->size - j)
        {
            if (table->cars[i].car_type.old_car.year == year)
            {
                for(size_t k = i; k < table->size - 1 - j; k++)
                {
                    buf = table->cars[k];
                    table->cars[k] = table->cars[k + 1];
                    table->cars[k + 1] = buf;
                }
                j++;
            }
            i++;
        }
    }

    if (strcmp(line, "millage") == 0)
    {
        int millage;
        printf("\nВведите пробег машины: ");
        error_code = fscanf(stdin,"%d", &millage);
        if (error_code != 1)
        {
            printf("\nОшибка при чтении пробега");
            return ERROR_PRICE;
        }
        else if (millage <= 0)
        {
            printf("\nОшибка пробег не может быть не натуральной величиной");
            return ERROR_PRICE;
        }

        while(i < table->size - j)
        {
            if (table->cars[i].car_type.old_car.mileage == millage)
            {
                for(size_t k = i; k < table->size - 1 - j; k++)
                {
                    buf = table->cars[k];
                    table->cars[k] = table->cars[k + 1];
                    table->cars[k + 1] = buf;
                }
                j++;
            }
            i++;
        }
    }

    if (strcmp(line, "repairs") == 0)
    {
        int repairs;
        printf("\nВведите количество ремонтов машины: ");
        error_code = fscanf(stdin,"%d", &repairs);
        if (error_code != 1)
        {
            printf("\nОшибка при чтении количества ремонтов");
            return ERROR_PRICE;
        }
        else if (repairs < 0)
        {
            printf("\nОшибка количество ремонтов не может быть отрицательной величиной");
            return ERROR_PRICE;
        }

        while(i < table->size - j)
        {
            if (table->cars[i].car_type.old_car.repairs_num == repairs)
            {
                for(size_t k = i; k < table->size - 1 - j; k++)
                {
                    buf = table->cars[k];
                    table->cars[k] = table->cars[k + 1];
                    table->cars[k + 1] = buf;
                }
                j++;
            }
            i++;
        }
    }

    if (strcmp(line, "owners") == 0)
    {
        int owners;
        printf("\nВведите количество владельцев машины: ");
        error_code = fscanf(stdin,"%d", &owners);
        if (error_code != 1)
        {
            printf("\nОшибка при чтении количества владельцев");
            return ERROR_PRICE;
        }
        else if (owners < 0)
        {
            printf("\nОшибка количество владельцев не может быть отрицательной величиной");
            return ERROR_PRICE;
        }

        while(i < table->size - j)
        {
            if (table->cars[i].car_type.old_car.owners == owners)
            {
                for(size_t k = i; k < table->size - 1 - j; k++)
                {
                    buf = table->cars[k];
                    table->cars[k] = table->cars[k + 1];
                    table->cars[k + 1] = buf;
                }
                j++;
            }
            i++;
        }
    }

    table->size -= j;
    printf("\nКоличество удаленных машин: %zu", j);
    get_keys(table);
    return OK;
}

int print_task(table_t *table)
{
    int error_code;

    char name[CAR_NAME_LEN];
    printf("\nВведите марку машины: ");
    error_code = char_check(stdin, CAR_NAME_LEN, name);


    int price_min, price_max;

    printf("\nВведите минимальную цену машины: ");
    error_code = fscanf(stdin, "%d", &price_min);
    if (error_code != 1)
    {
        printf("\nОшибка чтения цены");
        return ERROR_PRICE;
    }
    if (price_min < 0)
    {
        printf("\nЦена не может быть отрицательной");
        return ERROR_PRICE;
    }

    printf("\nВведите максимальную цену машины: ");
    error_code = fscanf(stdin, "%d", &price_max);
    if (error_code != 1)
    {
        printf("\nОшибка чтения цены");
        return ERROR_PRICE;
    }
    if (price_max < 0)
    {
        printf("\nЦена не может быть отрицательной");
        return ERROR_PRICE;
    }

    if (price_min >= price_max)
    {
        printf("\nНеверный диапозон цены");
        return ERROR_PRICE;
    }


    for (size_t i = 0; i < LINE_LEN; i++)
        printf("_");
    printf("\n| %-15s| %-20s| %-13s| %-15s| %-9s| %-8s| %-5s| %-7s| %-7s| %-7s|\n", "NAME", "COUNTRY", "PRICE","COLOR", "CONDITION", "GARANTY", "YEAR", "MILEAGE", "REPAIRS", "OWNERS");
    for (size_t i = 0; i < LINE_LEN; i++)
        printf("_");

    for (size_t i = 0; i < table->size; i++)
    {
        if (compare(&table->cars[i], name, price_min,price_max) == OK)
            printf("\n| %-15s| %-20s| %-13d| %-15s| %-9s| %-8s| %-5d| %-7d| %-7d| %-7d|\n", table->cars[i].car_name, table->cars[i].country, table->cars[i].price,table->cars[i].color, table->cars[i].condition, "-", table->cars[i].car_type.old_car.year, table->cars[i].car_type.old_car.mileage, table->cars[i].car_type.old_car.repairs_num, table->cars[i].car_type.old_car.owners);
    }

    for (size_t i = 0; i < LINE_LEN; i++)
        printf("_");
    
    return OK;
}

void get_keys(table_t *table)
{
    for (size_t i = 0; i < table->size; i++)
    {
        table->keys[i].index = i;
        table->keys[i].key = table->cars[i].price;
    }
}

int print_keys(table_t *table)
{
    for(size_t i = 0; i < 23; i++)
        printf("_");
    
    printf("\n| %-4s| %-14s|", "INDEX", "PRICE");

    for (size_t i = 0; i < table->size; i++)
    {
        printf("\n| %-5d| %-14d|", table->keys[i].index, table->keys[i].key);
    }
    printf("\n");
    for(size_t i = 0; i < 23; i++)
        printf("_");
    return OK;
}

int print_sorted_keys_table(table_t *table)
{

    for(size_t i = 0; i < LINE_LEN; i++)
        printf("%s", "_");
    
    printf("\n| %-15s| %-20s| %-13s| %-15s| %-9s| %-8s| %-5s| %-7s| %-7s| %-7s|\n", "NAME", "COUNTRY", "PRICE","COLOR", "CONDITION", "GARANTY", "YEAR", "MILEAGE", "REPAIRS", "OWNERS");

    for(size_t i = 0; i < LINE_LEN; i++)
        printf("_");

    for(size_t i = 0; i < table->size; i++)
    {
        size_t j = table->keys[i].index;
        if (strcmp((table->cars[j].condition), "new") == 0)
        {
            printf("\n| %-15s| %-20s| %-13d| %-15s| %-9s| %-8d| %-5s| %-7s| %-7s| %-7s|\n", table->cars[j].car_name, table->cars[j].country, table->cars[j].price,table->cars[j].color, table->cars[j].condition, table->cars[j].car_type.new_car.garanty_till, "-", "-","-","-");
        }
        else if (strcmp((table->cars[j].condition), "old") == 0)
        {
            printf("\n| %-15s| %-20s| %-13d| %-15s| %-9s| %-8s| %-5d| %-7d| %-7d| %-7d|\n", table->cars[j].car_name, table->cars[j].country, table->cars[j].price,table->cars[j].color, table->cars[j].condition, "-", table->cars[j].car_type.old_car.year, table->cars[j].car_type.old_car.mileage, table->cars[j].car_type.old_car.repairs_num, table->cars[j].car_type.old_car.owners);
        }
    }
    for(size_t i = 0; i < LINE_LEN; i++)
        printf("_");
    return OK;
}

double timer(table_t *table, int (*func) (table_t*))
{
    clock_t start = clock();
    for (size_t i = 0; i < 100; i++)
    {
        table_t buf = *table;
        func(&buf);
    }
    clock_t end = clock() - start;
    return (double)end/100.0/CLOCKS_PER_SEC;
}

int timer_sort(table_t *table)
{
    double keys;
    double tables;

    double key_1 = timer(table, sort_keys_bubble);
    double key_2 = timer(table, sort_keys_qsort);

    double table_1 = timer(table, sort_table_bubble);
    double table_2 = timer(table, sort_table_qsort);

    keys = key_1/key_2;
    tables = table_1/ table_2;
    
    printf("\nПроцентное превосходство времени обработки\nвремени обработки таблицы автомобилей от таблицы\nключей сортировкой пузырек\n");
    printf("\n|%-19.2lf|%-19.2lf", key_1, table_1);

    printf("\n\nПроцентное превосходство времени обработки\nвремени обработки таблицы автомобилей от таблицы\nключей ,быстрой сортировкой\n");
    printf("\n|%-19.2lf|%-19.2lf", key_2, table_2);

    printf("\n\nПроцентное превосходство времени обработки\nисходной таблицы над временем обработки таблицы ключей\n");

    printf("\n|%-19.2lf ключей|", keys);
    printf("\n|%-18.2lf таблицы|\n", tables);
    

    size_t mem_1 = table->size * sizeof(table->cars[0]);
    size_t mem_2 = table->size * sizeof(table->keys[0]);

    printf("\nКоличество байт, занимаемых массивами:\n");
    printf("\n|Ключей: %zu", mem_2);
    printf("\n|Машин: %zu\n", mem_1);

    return OK;
}