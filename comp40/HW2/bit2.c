/* Bit2 implementation
 */
#include "bit2.h"

UArray_T Bit2_array(Bit_2 twoDbitArray)
{
    struct UArray_T *p;
    p = twoDbitArray -> array;
    return p;
}

Bit_2 Bit2_new(int height, int width, int size)
{
    int length = height * width;
    Bit_2 twoDBitArray = malloc(sizeof(*twoDBitArray));
    twoDBitArray -> height = height;
    twoDBitArray -> width = width;
    twoDBitArray -> size = size;
    twoDBitArray -> array = UArray_new(length, size);
    return twoDbitArray;
}

void Bit2_free(Bit_2 *twoDbitArray)
{
    UArray_T p = Bit2_array(*twoDbitArray);
    UArray_free(&p);
    free(*twoDbitArray);
}

int UArray2_height(Bit_2 twoDbitArray)
{
    return twoDbitArray -> height;
}

int UArray2_width(Bit_2 twoDbitArray)
{
    return twoDbitArray -> width;
}

int UArray2_size(Bit_2 twoDbitArray)
{
    return twoDbitArray -> size;
}
/*
void *Bit2_get(Bit_2 twoDbitArray, int row, int column)
{
    int index =  ((row *(uarray2 -> width)) + column);
    void *

void Bit2_put(
*/
void map_col_major(Bit_2 twoDbitArray, void apply(Bit_2 twoDbitArray, int row, 
                   int column, void *cl), void *cl)
{
    for(int i = 0; i < twoDbitArray -> width; i++) {
	for(int j = 0; j < twoDbitArray -> height; j++) {
	    apply(twoDbitArray, j, i, cl);
		}
	}
}

void map_row_major(Bit_2 twoDbitArray, void apply(Bit_2 twoDbitArray2, int row,
                   int column, void *cl), void *cl)
{
    for(int i = 0; i < twoDbitArray -> height; i++) {
	for(int j = 0; j < twoDbitArray -> width; j++) {
	    apply(twoDbitarray, i, j, cl);
		}
	}
}
