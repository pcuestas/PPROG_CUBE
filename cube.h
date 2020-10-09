#ifndef CUBE_H_
#define CUBE_H_

#include <stdio.h> 
#include <stdlib.h>
#include "types.h"


/* 
COLORS: (standard) defined so that the id of a piece is c[0]+c[1]+c[2]
*/
#define W 1
#define Y 2
#define R 10
#define O 20
#define G 100
#define B 200
#define N 0 /*none, for edges and centers*/

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

/* @brief prints a cube in 2d */
int c_print(FILE* f,Cube3* c);

/*returns index of piece in pos (x,y,z)*/
int c_iofPos(Cube3 *c, short x, short y, short z);

/*returns index of piece whose id is searchcolors=color1+color2+color3*/
int c_iofCol(Cube3 *c, short searchcolours);

/*Functions that call moves*/

/* @brief performs move l in cube c*/
void c_make(Cube3 *c, char l);

/* @brief performs set of moves in string in order */
Status c_moves(Cube3 *c, char *s);




/***********MOVES*************/

/* @brief moves the upper layer clockwise */
void m_U(Cube3* c);

/* @brief moves the upper layer counterclockwise */
void m_u(Cube3* c);

/* @brief moves the lower layer clockwise */
void m_D(Cube3* c);

/* @brief moves the lower layer counterclockwise */
void m_d(Cube3* c);

/* @brief moves the right layer clockwise */
void m_R(Cube3* c);

/* @brief moves the right layer counterclockwise */
void m_r(Cube3* c);

/* @brief moves the left layer clockwise */
void m_L(Cube3* c);

/* @brief moves the left layer counterclockwise */
void m_l(Cube3* c);

/* @brief moves the front layer clockwise */
void m_F(Cube3* c);

/* @brief moves the front layer counterclockwise */
void m_f(Cube3* c);

/* @brief moves the back layer clockwise */
void m_B(Cube3* c);

/* @brief moves the back layer counterclockwise */
void m_b(Cube3* c);


/* @brief the layer between L and R, turn direction as L (top-down)*/
void m_M(Cube3* c);

void m_m(Cube3* c);

/* @brief the layer between U and D, turn direction as D (left-right)*/
void m_E(Cube3* c);

void m_e(Cube3* c);

/* @brief the layer between F and B, turn direction as F*/
void m_S(Cube3* c);

void m_s(Cube3* c);



/*the following functions consider different axis than we do in the cube.c for the auxiliary functions. No problem. This will be taken into account*/

/* @brief rotate the entire Cube on R*/
void m_X(Cube3* c);

void m_x(Cube3* c);

/* @brief rotate the entire Cube on U*/
void m_Y(Cube3* c);

void m_y(Cube3* c);

/* @brief rotate the entire Cube on F*/
void m_Z(Cube3* c);

void m_z(Cube3* c);

#endif