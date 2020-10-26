#ifndef CUBE_H_
#define CUBE_H_

#include <stdio.h> 
#include <stdlib.h>
#include "types.h"


/* 
COLORS: (standard) defined so that the id of a piece is c[0]+c[1]+c[2]
*/

/*false colours, only for v1.0 of cube*/
#define W 1 /*white*/
#define Y 2 /*yellow*/
#define R 3 /**/
#define O 4
#define G 5
#define B 6
#define N 0 /*none, for edges and centers*/


/*REAL COLOURS:
#define W 1 
#define Y 2 
#define R 10 
#define O 20
#define G 100
#define B 200
#define N 0 
*/

#define NPC 26 /*number of pieces*/

typedef struct{
  short p[3];/*position x,y,z for x,y,z in {-1,0,1}*/
  short c[3];/*color {0...6}  [color axis x, c. axis y, color axis z]*/
  /*the id of a piece is c[0]+c[1]+c[2]*/
}Piece;

typedef struct{
  Piece pc[NPC];
}Cube3;

/*
 * @brief creates new cube alredy solved: 
 *         white on top, green in the front, red to the right
 * @return the cube created
*/
Cube3 *c_init();
/*
 * @brief frees a cube (entered as parameter)
 * 
*/
void c_free(Cube3*);


/*returns index of piece in pos (x,y,z)*/
int c_iofPos(Cube3 *c, short x, short y, short z);

/*returns index of piece whose id is searchcolors=color1+color2+color3*/
int c_iofCol(Cube3 *c, short searchcolours);

/***************Functions that call moves***************/

/* @brief performs move l in cube c*/
void c_make(Cube3 *c, char l);

/* @brief performs set of moves in string in order */
Status c_moves(Cube3 *c, char *s);


/*returns array of stickers's colours as shown in picture STICKERS.jpeg*/
Status colour_stickers(Cube3* c, short *s);


/*scrambles a cube using a random scramble from a file with name filename*/
Status scramble_cube(Cube3*c, char *filename);


/*prints info of a piece (for testing)*/
int p_print(FILE *, Piece *);

/*Checks if a cube is solved*/
Bool is_solved(short*s);

/*function that returns the color from the centerpiece in position cp: RLFBUD*/
short cfrom(Cube3* cube, char cp);


#endif
