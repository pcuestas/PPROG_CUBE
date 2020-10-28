#ifndef SOLVER_H_
#define SOLVER_H_

#include "cube.h"

char *solve_cube(Cube3* c1);

void solve_cross(Cube3 *c, char *sol);

void solve_d_corners(Cube3* c, char *sol);

void solve_finishF2L(Cube3*c, char *sol);


#endif