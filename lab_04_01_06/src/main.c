#include "menu.h"
#include "stack_array.h"
#include "stack_list.h"
#include "timer.h"

int main(void)
{
    setbuf(stdout, NULL);
    int error_code;
    int stack_type;

    error_code = read_type(&stack_type);
    if (error_code)
        return error_code;
    
    if (stack_type == 1)
        error_code = get_stack_array();
    else if (stack_type == 2)
        error_code = get_stack_list();
    else if (stack_type == 3)
        error_code = compare_stacks();
    
    if (error_code)
        return error_code;

    return error_code;
}