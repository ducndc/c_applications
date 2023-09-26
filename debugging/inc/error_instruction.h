/*
 * (C) Copyright 2023
 * Author:  Chung Duc Nguyen Dang
 * Email:   nguyendangchungduc1999@gmail.com
 *
 */
#ifndef __ERROR_INSTRUCTION_H__
#define __ERROR_INSTRUCTION_H__

int 
get_error_instruction(
    int cp0_epc,
    int reg_29,
    int error_code,
    int sp
);

int 
get_stack_pointer(
    int cp0_epc,
    int reg_29,
    int error_code,
    int sp
);

#endif /* END __ERROR_INSTRUCTION_H__ */