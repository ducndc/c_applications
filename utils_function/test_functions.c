/*
 * (C) Copyright 2023
 * Author:  Chung Duc Nguyen Dang
 * Email:   nguyendangchungduc1999@gmail.com
 *
 */

#include <stdio.h>

#include "time_functions.h"
#include "utils.h"

int
main(
    int argc,
    char *argv[]
)
{
    long uptime = 0;

    uptime = get_uptime();
    printf("Uptime of system is %ld hours\n", SECOND_2_HOURS(uptime));
    printf("Uptime of system is %ld day\n", SECOND_2_DAY(uptime));

    return 0;
}