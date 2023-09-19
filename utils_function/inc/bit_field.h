/*
 * (C) Copyright 2023
 * Author:  Chung Duc Nguyen Dang
 * Email:   nguyendangchungduc1999@gmail.com
 *
 */

#ifndef __BIT_FIELD_H__
#define __BIT_FIELD_H__

struct bit_field {
    char *bits;
    size_t max_bits;
}

/*
 * Allocate memory for bit field
 * 
 * @param   : Size of bit field
 * @return  : Pointer of bit field or NULL
 *
 */
struct bit_field *bit_field_alloc(size_t max_bits);

/*
 * Release memory for bit field
 * 
 * @param   : Pointer of bit field
 * @return  : NULL
 *
 */
void bit_field_free(struct bit_field *bf);

/*
 * Set a bit field
 * 
 * @param   : Pointer of bit field
 * @param   : Position of bit
 * @return  : NULL
 *
 */
void bit_field_set(struct bit_field *bf, size_t bit);

/*
 * Clear a bit field
 * 
 * @param   : Pointer of bit field
 * @param   : Position of bit
 * @return  : NULL
 *
 */
void bit_field_clear(struct bit_field *bf, size_t bit);

/*
 * Check a bit field
 * 
 * @param   : Pointer of bit field
 * @param   : Position of bit
 * @return  : interger
 *
 */
int bit_field_is_set(struct bit_field *bf, size_t bit);

/*
 * Get a bit field
 * 
 * @param   : Pointer of bit field
 * @return  : 0 or -1
 *
 */
int bit_field_get_first_zero(struct bit_field *bf);

#endif /* END __BIT_FIELD__H */