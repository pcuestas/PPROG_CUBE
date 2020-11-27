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

#include "cube.h"
#include "print_c.h"
#include "solver.h"
#include "lib_funct.h"

#ifndef SCRAMBLES_TXT
#define SCRAMBLES_TXT "./txt_files/scrambles.txt"
#endif

#define MAX_CAD 500

static SDL_GLContext ctx;
static SDL_Window *window;

int main(int argc, char *argv[])
{
    int value, flag = 0, mov, i = 0, done, j = 0, status, w, h;
    SDL_DisplayMode mode;
    SDL_Event event, ev2;
    Uint32 then, now, frames;
    Cube3 *c = NULL;
    SDL_Event ev;
    cprint_from_stickers printcube = c_print2;
    char cad[MAX_CAD], *text = malloc(200);
    short s[54], s2[54];
    double **stickers = NULL, **stickers2 = NULL;
    char akkk = 'u', *solution = NULL;
    float angle = 0.0f;

    c = c_init();
    if (!c)
        return 1;

    stickers = sticker_colorSDL_init();
    if(!stickers){
        c_free(c);
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    srand(time(NULL));

    /*Create window*/
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    window = SDL_CreateWindow("Rubik Cube PPROG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 940, 880, SDL_WINDOW_OPENGL);

    if (!window)
    {
        printf("SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    ctx = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);

    gluLookAt(1.5, 1.0, 1.0, 0, 0, 0, 0.5, 0, 0);
    /* Main loop */
    SDL_StartTextInput();
    while (flag == 0)
    {   

        while (SDL_PollEvent(&ev)){

            switch (ev.type){
            case SDL_QUIT:
                flag = 1;
                break;

            case SDL_KEYDOWN:
                switch (ev.key.keysym.sym){
                    case SDLK_ESCAPE:
                        flag = 1;
                        break;
                }
                break;
            case SDL_TEXTINPUT:
                /*update rgb matrix*/
                cube_to_SDL(c, stickers);

                strcat(text, ev.text.text);
                
                if (text[j] == 'R'||text[j]=='L'||text[j]=='M'||text[j]=='E'||text[j]=='U'||text[j]=='D'||text[j]=='F'||text[j]=='B'||text[j]=='S'||text[j] == 'r'||text[j]=='l'||text[j]=='m'||text[j]=='e'||text[j]=='u'||text[j]=='d'||text[j]=='f'||text[j]=='b'||text[j]=='s'||text[j] == 'x'||text[j] == 'X'||text[j] == 'y'||text[j] == 'Y'||text[j] == 'z'||text[j] == 'Z'){
                    Rot_full_move(&w, &h, stickers, text[j], window, ctx);
                }
                if (text[j] == 'w')
                    scramble_cube(c, SCRAMBLES_TXT);
                else if (text[j] == 'W'){
                    solution = solve_cube(c);
                    c_moves(c, solution);
                    free(solution);
                }
                else if (text[j] == 'A'){
                    solution = solve_cube(c);
                    printf("%s", solution);
                    free(solution);
                }
                else if (text[j] == 'a'){
                    solution = solve_cube(c);
                    SlowMoveRot(c, &w, &h, stickers, solution, window, ctx);
                    free(solution);
                }
                c_make(c, text[j]);/*make move in the cube*/
                j++;
                break;
            }
        }

        /*update rgb matrix*/
        cube_to_SDL(c, stickers);
        /*render changes in the cube*/
        Render_wr(&w,&h,stickers,window,ctx);
    }
    SDL_StopTextInput();
    colorSDL_free(stickers);
    free(text);
    SDL_Delay(1000);
    quit(0);
    c_free(c);
    return 0;
}
