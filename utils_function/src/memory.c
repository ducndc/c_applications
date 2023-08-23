/*
 * (C) Copyright 2023
 * Author:  Chung Duc Nguyen Dang
 * Email:   nguyendangchungduc1999@gmail.com
 *
 */

#include <string.h>

#include "memory.h"

void
*os_zalloc(
    size_t size 
)
{
    void *p_mem = malloc(size);

    if (p_mem != NULL)
    {
        memset(p_mem, 0, size);
    }

    return p_mem;
}