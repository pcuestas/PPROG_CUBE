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

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

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

        if (colour_stickers(c, s) == ERROR)
            return ERROR;

        stickers = sticker_colorSDL(s);
        if (!stickers)
            return ERROR;

        
        while (SDL_PollEvent(&ev))
        {

            switch (ev.type)
            {
            case SDL_QUIT:
                flag = 1;
                break;

            case SDL_KEYDOWN:
                switch (ev.key.keysym.sym)
                {
                case SDLK_UP:
                    mov = 1;
                    break;
                case SDLK_DOWN:
                    mov = 2;
                    break;
                case SDLK_LEFT:
                    mov = 3;
                    break;
                case SDLK_RIGHT:
                    mov = 4;
                    break;
                case SDLK_ESCAPE:
                    flag = 1;
                    break;
                }
                break;
            case SDL_TEXTINPUT:
                strcat(text, ev.text.text);
                angle = 0;
                if (text[j] == 'R'||text[j]=='L'||text[j]=='M'||text[j]=='E'||text[j]=='U'||text[j]=='D'||text[j]=='F'||text[j]=='B'||text[j]=='S')
                {
                    glPushMatrix();
                    while (angle < 90.0f)
                    {

                        SDL_GL_MakeCurrent(window, ctx);
                        SDL_GetWindowSize(window, &w, &h);
                        glViewport(0, 0, w, h);
                        Rot_layer(angle, stickers, text[j]);
                        SDL_GL_SwapWindow(window);

                        SDL_Delay(10);
                        angle += 1.0f;
                    }
                    glPopMatrix();
                }
                else if (text[j] == 'x'||text[j] == 'X'||text[j] == 'y'||text[j] == 'Y'||text[j] == 'z'||text[j] == 'Z')
                {
                    while (angle < 90.0f)
                    {

                        SDL_GL_MakeCurrent(window, ctx);
                        SDL_GetWindowSize(window, &w, &h);
                        glViewport(0, 0, w, h);
                        Rot(angle, stickers, text[j]);
                        SDL_GL_SwapWindow(window);

                        SDL_Delay(10);
                        angle += 1.0f;
                    }
                   
                }
                
                
                else if (text[j] == 'w')
                    scramble_cube(c, SCRAMBLES_TXT);
                else if (text[j] == 'W')
                {
                    solution = solve_cube(c);
                    c_moves(c, solution);
                    free(solution);
                }
                else if (text[j] == 'A')
                {
                    solution = solve_cube(c);
                    printf("%s", solution);
                    free(solution);
                }
                else if (text[j] == 'a')
                {
                    solution = solve_cube(c);
                    i = 0;
                    while (i < strlen(solution))
                    {

                        while (SDL_PollEvent(&ev2))
                        {

                            switch (ev2.key.keysym.sym)
                            {
                            case SDLK_UP:
                                mov = 1;
                                break;
                            case SDLK_DOWN:
                                mov = 2;
                                break;
                            case SDLK_LEFT:
                                mov = 3;
                                break;
                            case SDLK_RIGHT:
                                mov = 4;
                                break;
                            case SDLK_ESCAPE:
                                flag = 1;
                                break;
                            }
                        }

                        c_make(c, solution[i]);
                        if (colour_stickers(c, s2) == ERROR)
                        {
                            return ERROR;
                        }
                        stickers2 = sticker_colorSDL(s2);
                        if (!stickers2)
                        {
                            return ERROR;
                        }

                        SDL_GL_MakeCurrent(window, ctx);
                        SDL_GetWindowSize(window, &w, &h);
                        glViewport(0, 0, w, h);
                        Render(mov, stickers2);
                        SDL_GL_SwapWindow(window);
                        i++;
                        SDL_Delay(200);
                        colorSDL_free(stickers2);
                    }
                    free(solution);
                }
                c_make(c, text[j]);
                j++;
                break;
            }
        }
        if (colour_stickers(c, s) == ERROR)
            return ERROR;

        stickers = sticker_colorSDL(s);
        if (!stickers)
            return ERROR;
        SDL_GL_MakeCurrent(window, ctx);
        SDL_GetWindowSize(window, &w, &h);
        glViewport(0, 0, w, h);
        Render(mov, stickers);
        SDL_GL_SwapWindow(window);
        colorSDL_free(stickers);
    }
    SDL_StopTextInput();
    free(text);
    SDL_Delay(1000);
    quit(0);
    c_free(c);
    return 0;
}
