#include "../inc/errors.h"
#include "task_simulation.h"
#include "menu.h"
#include "compare.h"
#include <stdio.h>

int main(void)
{
    int error_code;
    int comand;
    setbuf(stdout, NULL);
    if ((error_code = read_comand_main(&comand)) != OK)
        return error_code;
    
    if (comand == 1)
    {
        error_code = compare();
    }
    else if (comand == 2)
    {
        task_simulation();
    }

    if (error_code)
        return error_code;
    return OK;
}