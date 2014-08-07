/* Names: Michael Silverblatt and Jake Austin
 * Date: 2/15/13
 * uarray2b.c
 * Implementation of methods suite for unblocked 2d arrays
 * Homework 3 Part B
 */

#include <stdlib.h>
#include <a2plain.h>

#include "uarray2.h"

/*
 * define a private version of each function in A2Methods_T that we implement 
in order to work with a UArray_2
 */
typedef A2Methods_UArray2 A2; 

static A2Methods_UArray2 new(int width, int height, int size)
{
        return UArray2_new(height, width, size);
}

static A2Methods_UArray2 new_with_blocksize(int width, int height, int size,
                                            int blocksize)
{
        (void) blocksize;
        return UArray2_new(height, width, size);
}

static void a2free (A2 *array2p)
{
        UArray2_free((UArray_2 *)array2p);
}

static int width    (A2 array2) { return UArray2_width    (array2); }
static int height   (A2 array2) { return UArray2_height   (array2); }
static int size     (A2 array2) { return UArray2_size     (array2); }
static int blocksize (A2 array2) { (void) array2; return 0; }

static A2Methods_Object *at(A2 array2, int i, int j)
{
        return UArray2_at(array2, j, i);
}

typedef void applyfun(UArray_2 array2, int i, int j, void *cl);
typedef void smallapplyfun(void *elem, void *cl);

struct a2fun_closure {
        A2Methods_applyfun *apply;
        void *cl;
        A2 array2;
};

struct a2fun_smallclosure{
        A2Methods_smallapplyfun *apply;
        void *cl;
};

static void apply_a2methods_using_array2_prototype(UArray_2 array2, int i, 
                                                   int j, void *cl)
{
        struct a2fun_closure *f = cl;
        f -> apply(i, j, f -> array2, UArray2_at(array2, i, j), f -> cl);
}

static void apply_a2smallmethods_using_array2_prototype(UArray_2 array2, int i,
                                                        int j, void *cl)
{
        struct a2fun_smallclosure *f = cl;
        f -> apply(UArray2_at(array2, i, j), f -> cl);
}

static void map_row_major (A2 array2, A2Methods_applyfun apply, void *cl)
{
        struct a2fun_closure mycl = {apply, cl, array2};
        UArray2_map_row_major(array2, apply_a2methods_using_array2_prototype, 
                              &mycl);
}

static void map_col_major(A2 array2, A2Methods_applyfun apply, void *cl)
{
        struct a2fun_closure mycl = {apply, cl, array2};
        UArray2_map_col_major(array2, apply_a2methods_using_array2_prototype, 
                              &mycl);
}
static void small_map_row_major(A2 array2, A2Methods_smallapplyfun apply, 
                                void *cl){
        struct a2fun_smallclosure mycl = {apply, cl};
        UArray2_map_row_major(array2, 
                              apply_a2smallmethods_using_array2_prototype, 
                              &mycl);
}

static void small_map_col_major(A2 array2, A2Methods_smallapplyfun apply, 
                                void *cl){
        struct a2fun_smallclosure mycl = {apply, cl};
        UArray2_map_col_major(array2, 
                              apply_a2smallmethods_using_array2_prototype, 
                              &mycl);
}

    /*
     * now create the private struct containing pointers to the functions
     */

static struct A2Methods_T uarray2_methods_plain_struct = {
        new,
        new_with_blocksize,
        a2free,
        width,
        height,
        size,
        blocksize,
        at,
        map_row_major,
        map_col_major,
        NULL, //map_block_major,
        map_row_major, // map_default
        small_map_row_major,
        small_map_col_major,
        NULL, //small_map_block_major,
        small_map_row_major, //small_map_block_major, // small_map_default
};


/*
 * finally the payoff: here is the exported pointer to the struct
 */

A2Methods_T uarray2_methods_plain = &uarray2_methods_plain_struct;
