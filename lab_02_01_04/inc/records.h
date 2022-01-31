#ifndef MY_RECORDS
#define MY_RECORDS

#include <stdio.h>
#include "errors.h"

#define CAR_NAME_LEN 20
#define COUNTRY_NAME_LEN 25
#define CONDITION_LEN 4
#define LINE_LEN 125
#define MAX_TABLE_SIZE 6000
#define COLOR_LEN 15
typedef struct
{
    int garanty_till;
} new_t;

typedef struct
{
    int year;
    int mileage;
    int repairs_num;
    int owners;
} old_t;

typedef union
{
    new_t new_car;
    old_t old_car;
} type_of_car_t;

typedef struct
{
    char car_name[CAR_NAME_LEN];
    char country[COUNTRY_NAME_LEN];
    int price;
    char color[COLOR_LEN];
    char condition[CONDITION_LEN];
    type_of_car_t car_type;
} car_t;

typedef struct
{
    int index;
    int key;
} keys_t;

typedef struct
{
    size_t size;
    car_t cars[MAX_TABLE_SIZE];
    keys_t keys[MAX_TABLE_SIZE];

} table_t;

int read_record(FILE *f, car_t *car);
int char_check(FILE *f, size_t max_len, char *str);
int compare(car_t *car, char *name, int price_min, int price_max);
#endif