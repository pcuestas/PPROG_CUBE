

#ifndef PRINT_C_H
#define PRINT_C_H

#include "cube.h"
#include "types.h"


typedef int (*cprint_from_stickers)(FILE*, short*);

int c_print(FILE *f, short *s);

/**
 * @brief : prints cube in FILE making use of the function passed in the last parameter
 * 
 * This function calls colour_stickers(Cube3*, short *) and frees all memory allocated within it
 * 
 * @returns ERROR/OK
*/
Status refresh_cube(Cube3*, FILE*, cprint_from_stickers);

#endif 