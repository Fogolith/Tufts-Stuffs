/* Names: Michael Silverblatt and Jake Austin
 * Date: 2/15/13
 * uarray2b.c
 * Implementation of blocked unboxed 2d arrays
 * Homework 3 Part A
 */
#include <math.h>

#include "uarray2b.h"
#include "uarray.h"
#include "uarray2.h"

#define T UArray2b_T


extern void freeMap(UArray_2 uarray2, int row, int col, void *cl);

typedef void apply_fun(int, int, T, void *, void *);

struct T 
{
        int height, width, size, blocksize;
        UArray_2 arr;
};

struct size_vals
{
        int size, blocksize;
};

/* 
Apply function for UArray2 maps. 
Allocates a UArray_T within every element of the UArray_2 passed as a 
parameter
 */
void init_block(UArray_2 uarray2, int row, int column, void *cl) 
{
        struct size_vals *temp = cl;
        UArray_T *elem = (UArray_T *)UArray2_at(uarray2, row, column);
        *elem = UArray_new(temp -> blocksize * temp -> blocksize,
                           temp -> size);
}


/*
Allocates space for a new 2d array. Calls init_block to initialize each block.
User specifies block size in parameter blocksize.
*/
extern T    UArray2b_new (int width, int height, int size, int blocksize)
{
        struct size_vals *values = malloc(sizeof(*values));
        values -> size = size;
        values -> blocksize = blocksize;

        struct T *TwoDBarr = malloc(sizeof(*TwoDBarr));
        TwoDBarr -> height = height;
        TwoDBarr -> width = width;
        TwoDBarr -> size = size;
        TwoDBarr -> blocksize = blocksize;
   
        int h,w;
        h = height / blocksize;
        /* If there is a remainder, you need one extra block */
        if (height % blocksize > 0) h++;
        w = width / blocksize;
        /* Increments to account for remainder */
        if (width % blocksize) w++;
        UArray_T *temp;
        TwoDBarr -> arr = UArray2_new(h, w, sizeof(*temp));
        UArray2_map_row_major(TwoDBarr -> arr, init_block, values);
        free(values); 
        return TwoDBarr;
}


                      

/*
Allocates a new UArray2b with largest possible block (64k)
*/
extern T    UArray2b_new_64K_block(int width, int height, int size)
{
        if (size > 64000) return UArray2b_new(width, height, size, 1);
        else {
            return UArray2b_new(width, height, size,sqrt(64000 / size));
        }
}


/*
Frees memory allocated to UArray2b_T
*/
extern void  UArray2b_free  (T *array2b)
{
    assert(array2b);
    assert((*array2b) -> arr);
    UArray_2 test = (*array2b) -> arr;
    UArray2_map_row_major(test, freeMap, NULL); 
    UArray2_free(&(*array2b) -> arr);
        free(*array2b);
}


extern void freeMap(UArray_2 uarray2, int row, int col, void *cl)
{
       UArray_T *uarray = UArray2_at(uarray2, row, col);
        UArray_free(uarray); 
    (void) row;
    (void) col;
    (void) uarray2;     
(void) cl;
}
/*
The following 4 functions return the data member in the struct
*/
extern int   UArray2b_width (T array2b)
{
        return array2b -> width;
}

extern int   UArray2b_height(T array2b)
{
        return array2b -> height;
}

extern int   UArray2b_size  (T array2b)
{
        return array2b -> size;
}

extern int   UArray2b_blocksize(T array2b)
{
        return array2b -> blocksize;
}

/* returns a pointer to the cell in column i, row j.*/
extern void *UArray2b_at(T array2b, int j, int i)
{
        int blockRow, blockCol, blockIndex;
        blockRow = (j / array2b -> blocksize);
        blockCol = (i / array2b -> blocksize);
        blockIndex = ((array2b -> blocksize * (i % array2b -> blocksize)) + 
                      (j % array2b->blocksize));
        UArray_T *u2 = UArray2_at(array2b -> arr, blockCol, blockRow);
        assert(u2);
        return UArray_at(*(UArray_T *)u2, blockIndex);
 
}

struct map_vals{
        T uarray2b;
        apply_fun *apply;    
        void *cl;
};

/*
Apply function for UArray2 mapping functions. 
Maps through the UArray in a block contained by each UArray2
*/
extern void map_apply(UArray_2 uarray2, int row, int col, void *cl)
{ 
        struct map_vals *temp = cl;
        int blocksize = temp->uarray2b->blocksize;
        int height = temp->uarray2b->height;
        int width = temp->uarray2b->width;
        for (int i = 0; i < (blocksize * blocksize); i++){
            if ((col == (width / blocksize)) && 
                    ((i % blocksize) >= (width % blocksize)))
                {
/*                  fprintf(stderr,"FAIL\n"); */
/*                        // DO NOTHING, UNUSED CELL */
                } else if ((row == (height / blocksize)) && 
                           ((i / blocksize) >= (height % blocksize)))
                {
/*                  fprintf(stderr,"FAIL2\n");*/
/*                        // DO NOTHING, UNUSED CELL */
                } else {
                        assert(sizeof(UArray2_at(uarray2, row, col)) == 
                               sizeof(UArray_T));
                        temp -> apply(row * blocksize + (i / blocksize), 
                                      col * blocksize + (i % blocksize),
                                      temp -> uarray2b, 
                                      UArray_at(*(UArray_T *)UArray2_at(uarray2
                                                ,row,col),i),
                                      temp->cl);
                }
        }

}

/* 
Visits every element in 2d array, block by block. 
Calls map_apply on each block with apply function pointer in closure
*/
extern void  UArray2b_map(T array2b, 
                          void apply(int i, int j, T array2b, void *elem, 
                                     void *cl), 
                          void *cl)
{
        struct map_vals *values = malloc(sizeof(*values));
        values -> cl = cl;
        values -> uarray2b = array2b;
        values -> apply = apply;
        UArray2_map_row_major(array2b -> arr, map_apply, values);
        //UArray2b_free(&(values->uarray2b));
        free(values);
}

#undef T
