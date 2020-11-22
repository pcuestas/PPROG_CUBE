#ifndef _LIB_FUNCT_
#define _LIB_FUNCT_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <GL/glut.h>

#ifndef NPC
#define NPC 26
#endif

typedef struct _sSticker{
    int num; /*index in the rgb matrix, -1 if there is no sticker*/
    int mat[4]; /*index of vertices in vertices matrix (sorted)*/
}sSticker;

typedef struct _sPiece{
    sSticker st[3]; /*stickers in directions x, y, z (same directions as described by the structures in cube.h), if the piece has no sticker in direction i=0,1,2; then st[i].num==-1*/
}sPiece;

typedef struct _sCube{
    sPiece pc[NPC];/*26 pieces that make the cube, ordered and static*/
}sCube;

/*initializes the whole static sCube structure, to be used in order for the processes of colouring the cube in the library's window easier*/
sCube *sCube_init();


void quit(int rc);

void Render(int mov, double **s);

#endif