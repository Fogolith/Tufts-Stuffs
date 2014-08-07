/* UArray2.h
 * by Zack McGowan and Jake Austin, 02/03/2013
 * HW2 Part A: Two Dimensional Polymorphic Unboxed Arrays
 * This header file represents a UArray_2; a two dimensional array built
 * from Hanson's UArray_T structure. A UArray_2 is one large UArray_T, coupled
 * with information to traverse it as a two dimensional structure.
 */
#include "uarray.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED

#define T UArray_2
typedef struct T *T;



extern T        UArray2_new(int height, int width, int size);
extern void     UArray2_free(T *uarray2);
extern int      UArray2_height(T uarray2);
extern int      UArray2_width(T uarray2);
extern int      UArray2_size(T uarray2);
extern UArray_T UArray2_array(UArray_2 uarray2);
extern void    *UArray2_at(T uarray2, int row, int column);
extern void     UArray2_map_col_major(T uarray2, void apply(T uarray2, int row, 
                              int column, void *cl), void *cl);
extern void     UArray2_map_row_major(T uarray2, void apply(T uarray2, int row, 
                              int column, void *cl), void *cl);

#undef T
#endif
