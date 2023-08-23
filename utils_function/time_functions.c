/*
 * (C) Copyright 2023
 * Author:  Chung Duc Nguyen Dang
 * Email:   nguyendangchungduc1999@gmail.com
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "time_functions.h"
#include "utils.h"

long
get_uptime()
{
    FILE *fp = NULL;
    char buf[64] = {0};

    fp = fopen(PROC_LINUX_UP_TIME, "r");

    if (NULL == fp)
    {
        APP_LOG("Do not open " PROC_LINUX_UP_TIME);
        return -1;
    }

    if (fscanf(fp, "%s", buf) != 1) 
    {
        fclose(fp);
        APP_LOG("Get data from file fail");
        return -1;
    }

    fclose(fp);

    return atoi(buf);
}