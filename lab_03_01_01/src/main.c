#include "menu.h"
#include "matrix.h"
#include "sparce_matrix.h"
#include "timer.h"

int main(void)
{
    setbuf(stdout, NULL);
    int error_code;
    int comand;

    int flag = 1;

    while (flag)
    {
        print_menu();
        error_code = get_comand(&comand);

        if (error_code)
            return error_code;
        
        if (comand == 1)
        {
            error_code = sparce_addition();
            if (error_code)
                flag = 0;
        }
        if (comand == 2)
        {
            error_code = simple_addition();
            if (error_code)
                flag = 0;
        }
        if (comand == 3)
        {
            comparison_time_memory();
        }
        else if (comand == 0)
        {
            flag = 0;
        }
    }

    return error_code;
}