

#ifndef PRINT_C_H
#define PRINT_C_H

#include "cube.h"
#include "types.h"

/*returns array of stickers's colours */
Status colour_stickers(Cube3* c, short *s);

int c_print(FILE *f, short *s);

#endif 