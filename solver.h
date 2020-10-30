#ifndef SOLVER_H_
#define SOLVER_H_

#include "cube.h"

char *solve_cube(Cube3* c1);

void solve_cross(Cube3 *c, char *sol);

void solve_d_corners(Cube3* c, char *sol);

void solve_finishF2L(Cube3*c, char *sol);

void solve_topcross(Cube3* c, char *sol);

/*gets rid of unnecessary moves (redundancy)*/
void clean_moves(char* m);

/*if it is lowercase, returns uppercase and viceversa*/
char opposite_move(char c);

/*strcat seems not to work*/
void concatenate(char* a, char* b);


#endif