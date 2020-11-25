#ifndef INTERFACE_H
#define INTERFACE_H

#include "types.h"

typedef struct _rect rect;

/**
 * @brief Allocates a rectangle and sets its data.
 */
rect *rect_init(int line,int column,int l,int h );

void rect_free(rect*r);

/********GETTERS AND SETTERS************/
Status rect_setline(rect*r,int line);
Status rect_setheight(rect*r,int h);
int rect_getline(rect*r);
int rect_getcolumn(rect*r);
int rect_getl(rect*r);
int rect_geth(rect*r);

/**
 * @brief Prints the content of a file starting on a specif position (line,column)
 * @param h height of the element
 * @param l length of the element
 * @return OK or ERROR in case of error opening File
 */
Status print_element(char *filename,rect*r);

/**
 * @brief Clears the part of the terminal delimited by the rectangle
 */
void rect_clear(rect *r);


/**
 * @brief Prints the border of a rectangle using unicode chars
 */
Status rect_border(rect *r);


/**
 * @brief inits a rectangle with the values of an existin rectangle expanded in x direction and y.
 * @param x changes column--> column-x && l+x
 * @param y changes line-->line-y && h+y
 * @return pointer to rect or NULL in case of error;
 */ 
rect* rect_expand(rect*r, int x,int y);

/**
 * @brief Clears the screen using the C ANSI ESC code
 * */
void terminal_clear();

/**
 * @brief positiones the cursor in a line and column (starting by 1) using C ANSI ESC codes
 * */
 Status positionate_cursor(int line, int column);

#endif