/*
 * (C) Copyright 2023
 * Author:  Chung Duc Nguyen Dang
 * Email:   nguyendangchungduc1999@gmail.com
 *
 */
#include "error_instruction.h"
#include <stdio.h>

int
main(
    int argc,
    char *argv[]
)
{
    int cp0_epc;
    int reg_29;
    int error_code;
    int sp;
    int e = 1;

    printf("Enter cp0_epc: ");
    scanf("%x", &cp0_epc);
    printf("Enter reg_29: ");
    scanf("%x", &reg_29);
    printf("Enter error_code: ");
    scanf("%x", &error_code);

    do {
        printf("Enter sp: ");
        scanf("%d", &sp);
        printf("Error Instruction: %x\n", 
            get_error_instruction(cp0_epc, reg_29, error_code, sp));
        
        printf("If exit enter 0, continue enter 1\n");
        scanf("%d", &e);
    } while (e != 0);
    return 0;
}