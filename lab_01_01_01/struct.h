#ifndef MY_STRUCT
#define MY_STRUCT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define NMAX 32 
#define SRMAX 41
#define SIMAX 32
#define MAX_EXP 99999

typedef char real_t[SRMAX];
typedef char int_t[SIMAX];
typedef int man_t[NMAX];

typedef struct
{
    char num_sign;
    man_t mantissa;
    char exp_sign;
    int order;
} num_t;

#endif