#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

int main(int argc, char *argv[])
{
    int flag = 0, j = 0, w, h;
    Cube3 *c = NULL;
    SDL_Event ev;
    char text[200]="", a=0, *solution = NULL;
    double **stickers = NULL;
    SDL_GLContext ctx;
    SDL_Window *window;

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

                a=text[j];/*letter read*/
                
                if (a=='R'||a=='L'||a=='M'||a=='E'||a=='U'||a=='D'||a=='F'||a=='B'||a=='S'||a == 'r'||a=='l'||a=='m'||a=='e'||a=='u'||a=='d'||a=='f'||a=='b'||a=='s'||a=='x'||a=='X'||a=='y'||a =='Y'||a=='z'||a=='Z'){
                    Rot_full_move(&w, &h, stickers, a, window, ctx);
                }
                if (a == 'w')
                    scramble_cube(c, SCRAMBLES_TXT);
                else if (a == 'W'){
                    solution = solve_cube(c);
                    c_moves(c, solution);
                    free(solution);
                }
                else if (a == 'A'){
                    solution = solve_cube(c);
                    printf("%s", solution);
                    free(solution);
                }
                else if (a == 'a'){
                    solution = solve_cube(c);
                    SlowMoveRot(c, &w, &h, stickers, solution, window, ctx);
                    free(solution);
                }
                c_make(c, a);/*make move in the cube*/
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

    SDL_Delay(1000);
    quit(0);

    colorSDL_free(stickers);
    c_free(c);
    return 0;
}
