/* UArray2.c
 * by Zack MCGowan and Jake Austin, 02/03/2013
 * HW2 Part A: Two Dimensional Polymorphic Unboxed Arrays
 * This is the implementation for UArray_2
 */
#include "uarray2.h"
#include "uarray.h"

struct UArray_2 {
        int height;
        int width;
        int size;
        UArray_T array;
};

/* UArray2_new initializes and returns a pointer to a UArray_2
 * structure. Height, width, and size are stored, and a UArray_T
 * of size length*width is created.
 */
UArray_2 UArray2_new(int height, int width, int size)
{
        int length = height * width;
        UArray_2 twoD_array = malloc(sizeof(*twoD_array));
        twoD_array -> height = height;
	twoD_array -> width = width;
        twoD_array -> size = size;
        twoD_array -> array = UArray_new(length, size);
	return twoD_array;
}

/* UArray2_free deallocates the memory associated with the UArray_T
 * structure stored within UArray_2, and then deallocates UArray_2
 */
void UArray2_free(UArray_2 *uarray2)
{ 
        UArray_T p = UArray2_array(*uarray2);
        UArray_free(&p);
        free(*uarray2);
}

/* UArray2_height returns height value from the struct
 */
int UArray2_height(UArray_2 uarray2)
{
        return uarray2 -> height;
}

/* UArray2_width returns width value from the struct
 */

int UArray2_width(UArray_2 uarray2)
{
        return uarray2 -> width;
}

/* UArray2_size returns size value from the struct
 */
int UArray2_size(UArray_2 uarray2)
{
        return uarray2 -> size;
}

/* UArray2_array returns a pointer to the UArray_T associated
 * with the UArray_2 structure
 */
UArray_T UArray2_array(UArray_2 uarray2)
{
        struct UArray_T *p;
        p = uarray2 -> array;
        return p;
}

/* UArray2_at returns a pointer to an element of the 2D array
 * as referenced by it's row & column.
 */
void *UArray2_at(UArray_2 uarray2, int row, int column)
{
    
    //       fprintf(stderr,"row = %d, col = %d\n", row, column);
        int index = ((row *(uarray2 -> width)) + column);
	//    fprintf(stderr,"index = %d\n",index);
        void *p = UArray_at(uarray2 -> array, index);
        return p;
}

/* map_col_major, given a UArray_2, iterates through the 2D array in column-
 * first order. An apply function may be passed into map_col_major to act
 * on individual elements of the UArray_T
 */
void UArray2_map_col_major(UArray_2 uarray2, void apply(UArray_2 uarray2, int row, 
                   int column, void *cl), void *cl)
{
        for (int i = 0; i < uarray2 -> width; i++) {
	        for (int j = 0; j < uarray2 -> height; j++) {
	            apply(uarray2, j, i, cl);
	        }
        }
}


/* map_row_major, given a UArray_2, iterates through the 2D array in row-
 * first order. An apply function may be passed into map_row_major to act
 * on individual elements of the UArray_T
 */
void UArray2_map_row_major(UArray_2 uarray2, void apply(UArray_2 uarray2, int row,
                   int column, void *cl), void *cl)
{
        for (int i = 0; i < uarray2 -> height; i++) {
                for (int j = 0; j < uarray2 -> width; j++) {
	            apply(uarray2, i, j, cl);
		}
	}
}
