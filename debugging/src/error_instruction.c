/*
 * (C) Copyright 2023
 * Author:  Chung Duc Nguyen Dang
 * Email:   nguyendangchungduc1999@gmail.com
 *
 */
#include "error_instruction.h"
#include <stdio.h>

int 
get_error_instruction(
    int cp0_epc,
    int reg_29,
    int error_code,
    int sp
)
{
    int stack_pointer = 0;
    int return_address = 0;
    int offset = 0;
    int next_error_code = 0;

    stack_pointer = get_stack_pointer(cp0_epc, reg_29, error_code, sp);
    printf("From stack pointer %X, enter return address\n", stack_pointer);
    scanf("%x", &return_address);

    if (cp0_epc > return_address) {
        offset = cp0_epc - return_address;
        next_error_code = error_code - offset;
        return next_error_code;
    } else {
        offset = return_address - cp0_epc;
        next_error_code = error_code + offset;
        return next_error_code;
    }
}

int 
get_stack_pointer(
    int cp0_epc,
    int reg_29,
    int error_code,
    int sp
)
{
    return (reg_29 + sp - 4);
}