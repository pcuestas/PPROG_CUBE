

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


/**
 * @brief ALLOCATES an array. Translates the array of colors of the stickers into the color code for ANSI ESC
 * @param s pointer to array of stickers (s[i]=MACRO of a color defined in cubo.c )
 * @return an array with the color for ansi code 
 */
short *sticker_to_color(short *s);

/**
 * @brief ALLOCATES a matrix. Translates the array of colors of the stickers into the color code for SLD ESC
 * @param s pointer to array of stickers (s[i]=MACRO of a color defined in cubo.c )
 * @return a 56x3 matrix with the rgb code 
 */
double **sticker_colorSDL(short *s);

/**
 * @brief Frees the array allocated by the function sticker_colorSDL
 * @param s matrix to be freed
 */
void colorSDL_free(double** s);

/**
 * @brief prints a cube
 * @param f, file to print in
 * @param s, array of stickers (it is translated with sticker_to_color funct)
 * @return 
 */ 
int c_print2(FILE *f, short *s);

/**
 * @brief makes the moves in the input waiting delay seconds befor making each move
 * @param c, cube
 * @param pf, file to print in
 * @param print_cube function used to print the cube 
 * @param moves -moves to be made to the cube
 * @param delay -used to regulate the time that it waits
 * @return 
 */ 
Status slow_moves(Cube3* c, FILE* pf, cprint_from_stickers print_cube, char *moves, int delay);


#endif 