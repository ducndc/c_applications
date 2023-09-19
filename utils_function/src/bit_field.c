/*
 * (C) Copyright 2023
 * Author:  Chung Duc Nguyen Dang
 * Email:   nguyendangchungduc1999@gmail.com
 *
 */

#include "stdlib.h"
#include "bit_field.h"

struct bit_field *
bit_field_alloc(
    size_t max_bits
)
{
    struct bit_field *bf;

    bf = malloc(sizeof(*bf) + (max_bits + 7) / 8);

    if (NULL == bf) {
        return NULL;
    }

    bf->bits = (char *)(bf + 1);
    bf->max_bits = max_bits;

    return bf;
}

void 
bit_field_free(
    struct bit_field *bf
)
{
    free(bf);
}

void 
bit_field_set(
    struct bit_field *bf,
    size_t bit
)
{
    if (bit >= bf->max_bits) {
        return;
    }

    bf->bits[bit / 8] |= BIT(bit % 8);
}

void 
bit_field_clear(
    struct bit_field *bf,
    size_t bit 
)
{
    if (bit >= bf->max_bits) {
        return;
    }

    bf->bits[bit / 8] &= ~BIT(bit % 8);
}

int 
bit_field_is_set(
    struct bit_field *bf,
    size_t bit 
)
{
    if (bit >= bf->max_bits) {
        return 0;
    }

    return !!(bf->bits[bit / 8] & BIT(bit % 8));
}

static int 
first_zero(
    char val
)
{
    int i = 0;

    for (i = 0; i < 8; ++i) {
        if (!(val & 0x01))
            return i;

        val >>= 1;
    }

    return -1;
}

int 
bit_field_get_first_zero(
    struct bit_field *bf
)
{
    size_t i;

    for (i = 0; i < (bf->max_bits + 7) / 8; ++i) {
        if (bf->bits[i] != 0xff) 
            break;
    }

    if (i == (bf->max_bits + 7) / 8)
        return -1;

    i = i * 8 + first_zero(bf->bits[i]);

    if (i >= bf->max_bits)
        return -1;

    return i;
}
