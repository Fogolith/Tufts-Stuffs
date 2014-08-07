/* 
 * Name: Michael Silverblatt and Jake Austin
 * Date: 2/15/13
 * ppmtrans.c
 * Implementation of image transformation software
 * Homework 3 Part C
 * Uses A2Methods suite to operate on and save data from Pnm_ppm types
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "assert.h"
#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "pnm.h"

void rotate90apply(int i, int j, A2Methods_UArray2 T, A2Methods_Object *ptr, 
                   void *cl);
void print_apply(int i, int j, A2Methods_UArray2 T, A2Methods_Object *ptr, 
                 void *cl);
void rotate180apply(int i, int j, A2Methods_UArray2 T, A2Methods_Object *ptr, 
                    void *cl);
void rotate0apply(int i, int j, A2Methods_UArray2 T, A2Methods_Object *ptr, 
                  void *cl);
void rotate270apply(int i, int j, A2Methods_UArray2 T, A2Methods_Object *ptr, 
                    void *cl);

struct myclosure{
        Pnm_ppm src;
        A2Methods_UArray2 result;
        A2Methods_T methods;
};

int main(int argc, char *argv[]) {
        int rotation = 0;
        A2Methods_T methods = uarray2_methods_plain; /* default to UArray2 
                                                      * methods
                                                      */
        assert(methods);
        A2Methods_mapfun *map = methods -> map_default; /*default to best map*/
        assert(map);

#define SET_METHODS(METHODS, MAP, WHAT) do {                            \
                methods = (METHODS);                                    \
                assert(methods);                                        \
                map = methods->MAP;                                     \
                if (!map) {                                             \
                        fprintf(stderr, \
                                "%s does not support " WHAT "mapping\n", \
                                argv[0]); \
                        exit(1);                                        \
                }                                                       \
        } while(0)
        char *filename = NULL;
        int i;
        for (i = 1; i < argc; i++) {
                if (!strcmp(argv[i], "-row-major")) {
                        SET_METHODS(uarray2_methods_plain,
                                    map_row_major,
                                    "row-major");
                } else if (!strcmp(argv[i], "-col-major")) {
                        SET_METHODS(uarray2_methods_plain,
                                    map_col_major,
                                    "column-major");
                } else if (!strcmp(argv[i], "-block-major")) {
                        SET_METHODS(uarray2_methods_blocked,
                                    map_block_major,
                                    "block-major");
                } else if (!strcmp(argv[i], "-rotate")) {
                        assert(i + 1 < argc);
                        char *endptr;
                        rotation = strtol(argv[++i], &endptr, 10);
                        assert(*endptr == '\0'); /* parsed all correctly */
                        assert(rotation == 0   || rotation == 90
                               || rotation == 180 || rotation == 270);
                } else if (*argv[i] == '-') {
                        fprintf(stderr, "%s: unknown option '%s'\n",
                                argv[0], argv[i]);
                        exit(1);
                } else if (argc - i > 2) {
                        fprintf(stderr, "Usage: %s [-rotate <angle>] "
                                "[-{row,col,block}-major] [filename]\n",
                                argv[0]);
                        exit(1);
                } else {
                    filename = argv[i];
                        break;
                }
        }
      
        Pnm_ppm image;
        /*
        result will replace the 2d array in image created by ppmread
         */
        A2Methods_UArray2 result;
        struct myclosure *mycl = malloc(sizeof(*mycl));
        mycl -> methods = methods;
        if (filename == NULL){
                image = Pnm_ppmread(stdin, methods);
        } else {
                FILE *fp = fopen(filename, "r");
                image = Pnm_ppmread(fp, methods);
                fclose(fp);
        }
        mycl -> src = image;
        if (rotation == 0 || rotation == 180)  
        result = methods->new(mycl -> src -> height, mycl -> src -> width, 
                              sizeof(struct Pnm_rgb));
        else result = methods->new(mycl -> src -> width, mycl -> src -> height,
                                   sizeof(struct Pnm_rgb));
        mycl -> result = result;
        unsigned int temp; /* Used to swap image's height and width */
        if (rotation == 90){
                map(image -> pixels, rotate90apply, mycl);
                temp = image -> height;
                image -> height = image -> width;
                image -> width = temp;
        } else if (rotation == 180){
                map(image -> pixels, rotate180apply, mycl);
        } else if (rotation == 0){
                map(image -> pixels, rotate0apply, mycl);
        } else if (rotation == 270){
                map(image->pixels,rotate270apply,mycl);
                temp = image->height;
                image->height = image->width;
                image->width = temp;
        }
        methods->free(&(image->pixels));
        image -> pixels = mycl -> result;
        Pnm_ppmwrite(stdout, image);
        Pnm_ppmfree(&image);
        //Pnm_ppmfree(&(mycl->src));
//      methods -> free(&(mycl -> result));
        free(mycl);
        
}

/* Maps every pixel (i,j) in src to pixel (i, j) in result */
void rotate0apply(int i, int j, A2Methods_UArray2 T, A2Methods_Object *ptr, 
                  void *cl){
       (void) T;
        struct myclosure *mycl = cl;
        Pnm_rgb temp = mycl -> methods -> at(mycl -> result, i, j);
        assert(sizeof(*temp) == sizeof(*(Pnm_rgb)ptr));
        assert(temp != NULL);
        assert(ptr != NULL);
        *temp = *(Pnm_rgb)ptr;
}

/* Maps every pixel (i,j) in src to pixel (height - j - 1, i) in result */
void rotate270apply(int i, int j, A2Methods_UArray2 T, A2Methods_Object *ptr, 
                   void *cl){
        (void) T;
        struct myclosure *mycl = cl;
        Pnm_rgb temp = mycl -> methods -> at(mycl -> result,
                                             mycl ->src->width - j -1,
                                             i);
        assert(sizeof(*temp) == sizeof(*(Pnm_rgb)ptr));
        assert(temp != NULL);
        assert(ptr != NULL);
        *temp = *(Pnm_rgb)ptr;
}

/*
Maps every pixel (i,j) in src to pixel (width - i - 1, height - j - 1) 
in result 
*/
void rotate180apply(int i, int j, A2Methods_UArray2 T, A2Methods_Object *ptr, 
                    void *cl){
        (void) T;
        struct myclosure *mycl = cl;
        Pnm_rgb temp = mycl -> methods -> at(mycl -> result,
                                             mycl -> src -> height - i - 1,
                                             mycl -> src -> width - j - 1);
        assert(sizeof(*temp) == sizeof(*(Pnm_rgb)ptr));
        assert(temp != NULL);
        assert(ptr != NULL);
        *temp = *(Pnm_rgb)ptr;
}

/* Maps every pixel (i,j) in src to pixel (j, height - i - 1) in result */
void rotate90apply(int i, int j, A2Methods_UArray2 T, A2Methods_Object *ptr, 
                    void *cl){
        (void) T;
        struct myclosure *mycl = cl;
        Pnm_rgb temp = mycl -> methods -> at(mycl -> result, j, 
                                             (mycl -> src -> height - i) - 1);
        assert(sizeof(*temp) == sizeof(*(Pnm_rgb)ptr));
        assert(temp != NULL);
        assert(ptr != NULL);
        *temp = *(Pnm_rgb)ptr;

}



