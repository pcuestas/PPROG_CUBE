#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>

#include "cube.h"
#include "print_c.h"
#include "solver.h"

#define MAX_CAD 500

static SDL_GLContext ctx;
static SDL_Window *window;

static void quit(int rc)
{
    if (ctx)
        SDL_GL_DeleteContext(ctx);

    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(rc);
}

static void Render(int mov, double **s)
{
    static float color[8][3] = {
        {1.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 1.0, 1.0},
        {1.0, 1.0, 1.0},
        {1.0, 0.0, 1.0},
        {0.0, 0.0, 1.0}};

    static float cube[56][3] = {
        //Cara 1
        {0.6, 0.6, 0.6},
        {0.6, 0.6, 0.2},
        {0.6, 0.6, -0.2},
        {0.6, 0.6, -0.6},
        {0.6, 0.2, -0.6},
        {0.6, -0.2, -0.6},
        {0.6, -0.6, -0.6},
        {0.6, -0.6, -0.2},
        {0.6, -0.6, 0.2},
        {0.6, -0.6, 0.6},
        {0.6, -0.2, 0.6},
        {0.6, 0.2, 0.6},
        {0.6, 0.2, 0.2},
        {0.6, 0.2, -0.2},
        {0.6, -0.2, -0.2},
        {0.6, -0.2, 0.2},

        //Cara 2
        {0.2, 0.6, 0.6},
        {-0.2, 0.6, 0.6},
        {-0.6, 0.6, 0.6},
        {-0.6, 0.6, 0.2},
        {-0.6, 0.6, -0.2},
        {-0.6, 0.6, -0.6},
        {-0.2, 0.6, -0.6}, //22
        {0.2, 0.6, -0.6},
        {0.2, 0.6, -0.2},
        {0.2, 0.6, 0.2},
        {-0.2, 0.6, 0.2},
        {-0.2, 0.6, -0.2}, //27

        //Cara 3
        {-0.6, 0.2, 0.6},
        {-0.6, 0.2, 0.2},
        {-0.6, 0.2, -0.2},
        {-0.6, 0.2, -0.6},
        {-0.6, -0.2, -0.6},
        {-0.6, -0.6, -0.6}, //33
        {-0.6, -0.6, -0.2},
        {-0.6, -0.6, 0.2},
        {-0.6, -0.6, 0.6},
        {-0.6, -0.2, 0.6},
        {-0.6, -0.2, 0.2},
        {-0.6, -0.2, -0.2}, //39

        //Cara 4
        {-0.2, -0.6, 0.6},
        {-0.2, -0.6, 0.2},
        {-0.2, -0.6, -0.2},
        {-0.2, -0.6, -0.6},
        {0.2, -0.6, -0.6}, //44
        {0.2, -0.6, -0.2},
        {0.2, -0.6, 0.2},
        {0.2, -0.6, 0.6}, //47

        //Cara 5
        {0.2, 0.2, 0.6},
        {0.2, -0.2, 0.6},
        {-0.2, -0.2, 0.6},
        {-0.2, 0.2, 0.6},

        //Cara 6
        {0.2, 0.2, -0.6},
        {0.2, -0.2, -0.6},
        {-0.2, -0.2, -0.6},
        {-0.2, 0.2, -0.6}

    };

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);

    //Cara 1

    glColor3f(s[2][0], s[2][1], s[2][2]);
    glVertex3fv(cube[8]);
    glVertex3fv(cube[9]);
    glVertex3fv(cube[10]);
    glVertex3fv(cube[15]);

    glColor3f(s[5][0], s[5][1], s[5][2]);
    glVertex3fv(cube[10]);
    glVertex3fv(cube[11]);
    glVertex3fv(cube[12]);
    glVertex3fv(cube[15]);

    glColor3f(s[8][0], s[8][1], s[8][2]);
    glVertex3fv(cube[0]);
    glVertex3fv(cube[1]);
    glVertex3fv(cube[12]);
    glVertex3fv(cube[11]); //ST2

    glColor3f(s[1][0], s[1][1], s[1][2]);
    glVertex3fv(cube[7]);
    glVertex3fv(cube[8]);
    glVertex3fv(cube[15]);
    glVertex3fv(cube[14]);

    glColor3f(s[4][0], s[4][1], s[4][2]);
    glVertex3fv(cube[12]);
    glVertex3fv(cube[13]);
    glVertex3fv(cube[14]);
    glVertex3fv(cube[15]);

    glColor3f(s[7][0], s[7][1], s[7][2]);
    glVertex3fv(cube[1]);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[13]);
    glVertex3fv(cube[12]);

    glColor3f(s[0][0], s[0][1], s[0][2]);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[6]);
    glVertex3fv(cube[7]);
    glVertex3fv(cube[14]);

    glColor3f(s[3][0], s[3][1], s[3][2]);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[14]);
    glVertex3fv(cube[13]);

    glColor3f(s[6][0], s[6][1], s[6][2]);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[3]);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[13]);

    //Cara 2
    glColor3f(s[11][0], s[11][1], s[11][2]);
    glVertex3fv(cube[0]);
    glVertex3fv(cube[1]);
    glVertex3fv(cube[25]);
    glVertex3fv(cube[16]);

    glColor3f(s[10][0], s[10][1], s[10][2]);
    glVertex3fv(cube[1]);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[24]);
    glVertex3fv(cube[25]);

    glColor3f(s[9][0], s[9][1], s[9][2]);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[3]);
    glVertex3fv(cube[23]);
    glVertex3fv(cube[24]);

    glColor3f(s[12][0], s[12][1], s[12][2]);
    glVertex3fv(cube[23]);
    glVertex3fv(cube[24]);
    glVertex3fv(cube[27]);
    glVertex3fv(cube[22]);

    glColor3f(s[15][0], s[15][1], s[15][2]);
    glVertex3fv(cube[22]);
    glVertex3fv(cube[27]);
    glVertex3fv(cube[20]);
    glVertex3fv(cube[21]);

    glColor3f(s[16][0], s[16][1], s[16][2]);
    glVertex3fv(cube[27]);
    glVertex3fv(cube[26]);
    glVertex3fv(cube[19]);
    glVertex3fv(cube[20]);

    glColor3f(s[17][0], s[17][1], s[17][2]);
    glVertex3fv(cube[26]);
    glVertex3fv(cube[17]);
    glVertex3fv(cube[18]);
    glVertex3fv(cube[19]);

    glColor3f(s[14][0], s[14][1], s[14][2]);
    glVertex3fv(cube[25]);
    glVertex3fv(cube[16]);
    glVertex3fv(cube[17]);
    glVertex3fv(cube[26]);

    glColor3f(s[13][0], s[13][1], s[13][2]);
    glVertex3fv(cube[24]);
    glVertex3fv(cube[25]);
    glVertex3fv(cube[26]);
    glVertex3fv(cube[27]);

    //Cara 3

    glColor3f(s[47][0], s[47][1], s[47][2]);
    glVertex3fv(cube[18]);
    glVertex3fv(cube[19]);
    glVertex3fv(cube[29]);
    glVertex3fv(cube[28]);

    glColor3f(s[46][0], s[46][1], s[46][2]);
    glVertex3fv(cube[19]);
    glVertex3fv(cube[20]);
    glVertex3fv(cube[30]);
    glVertex3fv(cube[29]);

    glColor3f(s[45][0], s[45][1], s[45][2]);
    glVertex3fv(cube[20]);
    glVertex3fv(cube[21]);
    glVertex3fv(cube[31]);
    glVertex3fv(cube[30]);

    glColor3f(s[48][0], s[48][1], s[48][2]);
    glVertex3fv(cube[31]);
    glVertex3fv(cube[30]);
    glVertex3fv(cube[39]);
    glVertex3fv(cube[32]);

    glColor3f(s[51][0], s[51][1], s[51][2]);
    glVertex3fv(cube[32]);
    glVertex3fv(cube[39]);
    glVertex3fv(cube[34]);
    glVertex3fv(cube[33]);

    glColor3f(s[52][0], s[52][1], s[52][2]);
    glVertex3fv(cube[39]);
    glVertex3fv(cube[38]);
    glVertex3fv(cube[35]);
    glVertex3fv(cube[34]);

    glColor3f(s[53][0], s[53][1], s[53][2]);
    glVertex3fv(cube[38]);
    glVertex3fv(cube[37]);
    glVertex3fv(cube[36]);
    glVertex3fv(cube[35]);

    glColor3f(s[50][0], s[50][1], s[50][2]);
    glVertex3fv(cube[29]);
    glVertex3fv(cube[28]);
    glVertex3fv(cube[37]);
    glVertex3fv(cube[38]);

    glColor3f(s[49][0], s[49][1], s[49][2]);
    glVertex3fv(cube[30]);
    glVertex3fv(cube[29]);
    glVertex3fv(cube[38]);
    glVertex3fv(cube[39]);

    //Cara 4
    glColor3f(s[33][0], s[33][1], s[33][2]);
    glVertex3fv(cube[35]);
    glVertex3fv(cube[36]);
    glVertex3fv(cube[40]);
    glVertex3fv(cube[41]);

    glColor3f(s[34][0], s[34][1], s[34][2]);
    glVertex3fv(cube[34]);
    glVertex3fv(cube[35]);
    glVertex3fv(cube[41]);
    glVertex3fv(cube[42]);

    glColor3f(s[35][0], s[35][1], s[35][2]);
    glVertex3fv(cube[33]);
    glVertex3fv(cube[34]);
    glVertex3fv(cube[42]);
    glVertex3fv(cube[43]);

    glColor3f(s[32][0], s[32][1], s[32][2]);
    glVertex3fv(cube[43]);
    glVertex3fv(cube[42]);
    glVertex3fv(cube[45]);
    glVertex3fv(cube[44]);

    glColor3f(s[29][0], s[29][1], s[29][2]);
    glVertex3fv(cube[44]);
    glVertex3fv(cube[45]);
    glVertex3fv(cube[7]);
    glVertex3fv(cube[6]);

    glColor3f(s[28][0], s[28][1], s[28][2]);
    glVertex3fv(cube[45]);
    glVertex3fv(cube[46]);
    glVertex3fv(cube[8]);
    glVertex3fv(cube[7]);

    glColor3f(s[27][0], s[27][1], s[27][2]);
    glVertex3fv(cube[46]);
    glVertex3fv(cube[47]);
    glVertex3fv(cube[9]);
    glVertex3fv(cube[8]);

    glColor3f(s[30][0], s[30][1], s[30][2]);
    glVertex3fv(cube[41]);
    glVertex3fv(cube[40]);
    glVertex3fv(cube[47]);
    glVertex3fv(cube[46]);

    glColor3f(s[31][0], s[31][1], s[31][2]);
    glVertex3fv(cube[42]);
    glVertex3fv(cube[41]);
    glVertex3fv(cube[46]);
    glVertex3fv(cube[45]);

    //Cara 5
    glColor3f(s[18][0], s[18][1], s[18][2]);
    glVertex3fv(cube[11]);
    glVertex3fv(cube[48]);
    glVertex3fv(cube[16]);
    glVertex3fv(cube[0]);

    glColor3f(s[21][0], s[21][1], s[21][2]);
    glVertex3fv(cube[48]);
    glVertex3fv(cube[51]);
    glVertex3fv(cube[17]);
    glVertex3fv(cube[16]);

    glColor3f(s[24][0], s[24][1], s[24][2]);
    glVertex3fv(cube[51]);
    glVertex3fv(cube[28]);
    glVertex3fv(cube[18]);
    glVertex3fv(cube[17]);

    glColor3f(s[25][0], s[25][1], s[25][2]);
    glVertex3fv(cube[50]);
    glVertex3fv(cube[37]);
    glVertex3fv(cube[28]);
    glVertex3fv(cube[51]);

    glColor3f(s[26][0], s[26][1], s[26][2]);
    glVertex3fv(cube[40]);
    glVertex3fv(cube[36]);
    glVertex3fv(cube[37]);
    glVertex3fv(cube[50]);

    glColor3f(s[23][0], s[23][1], s[23][2]);
    glVertex3fv(cube[47]);
    glVertex3fv(cube[40]);
    glVertex3fv(cube[50]);
    glVertex3fv(cube[49]);

    glColor3f(s[20][0], s[20][1], s[20][2]);
    glVertex3fv(cube[9]);
    glVertex3fv(cube[47]);
    glVertex3fv(cube[49]);
    glVertex3fv(cube[10]);

    glColor3f(s[19][0], s[19][1], s[19][2]);
    glVertex3fv(cube[10]);
    glVertex3fv(cube[49]);
    glVertex3fv(cube[48]);
    glVertex3fv(cube[11]);

    glColor3f(s[22][0], s[22][1], s[22][2]);
    glVertex3fv(cube[51]);
    glVertex3fv(cube[50]);
    glVertex3fv(cube[49]);
    glVertex3fv(cube[48]);

    //Cara 6
    glColor3f(s[36][0], s[36][1], s[36][2]);
    glVertex3fv(cube[44]);
    glVertex3fv(cube[6]);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[53]);

    glColor3f(s[39][0], s[39][1], s[39][2]);
    glVertex3fv(cube[43]);
    glVertex3fv(cube[44]);
    glVertex3fv(cube[53]);
    glVertex3fv(cube[54]);

    glColor3f(s[42][0], s[42][1], s[42][2]);
    glVertex3fv(cube[33]);
    glVertex3fv(cube[43]);
    glVertex3fv(cube[54]);
    glVertex3fv(cube[32]);

    glColor3f(s[43][0], s[43][1], s[43][2]);
    glVertex3fv(cube[32]);
    glVertex3fv(cube[54]);
    glVertex3fv(cube[55]);
    glVertex3fv(cube[31]);

    glColor3f(s[44][0], s[44][1], s[44][2]);
    glVertex3fv(cube[31]);
    glVertex3fv(cube[55]);
    glVertex3fv(cube[22]);
    glVertex3fv(cube[21]);

    glColor3f(s[41][0], s[41][1], s[41][2]);
    glVertex3fv(cube[55]);
    glVertex3fv(cube[52]);
    glVertex3fv(cube[23]);
    glVertex3fv(cube[22]);

    glColor3f(s[38][0], s[38][1], s[38][2]);
    glVertex3fv(cube[52]);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[3]);
    glVertex3fv(cube[23]);

    glColor3f(s[37][0], s[37][1], s[37][2]);
    glVertex3fv(cube[53]);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[52]);

    glColor3f(s[40][0], s[40][1], s[40][2]);
    glVertex3fv(cube[53]);
    glVertex3fv(cube[54]);
    glVertex3fv(cube[55]);
    glVertex3fv(cube[52]);

    glEnd();

    glMatrixMode(GL_MODELVIEW);
    if (mov == 1)
    {
        glRotatef(2.0, 0, 0, 0);
    }
    else if (mov == 2)
    {
        glRotatef(2.0, 1.0, 0, 0);
    }
    else if (mov == 3)
    {
        glRotatef(2.0, 0, 1.0, 0);
    }
    else if (mov == 4)
    {
        glRotatef(2.0, 0, 0, 1.0);
    }
    else
        glRotatef(1.0, 0, 0, 0);
}

int main(int argc, char *argv[])
{
    int value;
    int mov;
    int i = 0, done, j = 0;
    SDL_DisplayMode mode;
    SDL_Event event;
    Uint32 then, now, frames;
    int status;
    Cube3 *c = NULL;
    cprint_from_stickers printcube = c_print2;
    char cad[MAX_CAD], *text = malloc(200);
    short *s = NULL, *s2 = NULL;
    double **stickers = NULL, **stickers2 = NULL;
    char akkk = 'u', *solution = NULL;

    c = c_init();
    if (!c)
        return 1;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Create window
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

    /* Main loop */
    int flag = 0;
    SDL_StartTextInput();
    while (flag == 0)
    {
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            if (!(s = (short *)calloc(54, sizeof(short))))
            {
                return ERROR;
            }
            if (colour_stickers(c, s) == ERROR)
            {
                return ERROR;
            }
            stickers = sticker_colorSDL(s);
            if (!stickers)
            {
                return ERROR;
            }

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
                c_make(c, text[j]);
                if (text[j] == 'w')
                    scramble_cube(c, "scrambles.txt");
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
                    while (i < strlen(solution))
                    {

                        SDL_Event ev2;
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
                        if (!(s2 = (short *)calloc(54, sizeof(short))))
                        {
                            return ERROR;
                        }
                        if (colour_stickers(c, s2) == ERROR)
                        {
                            return ERROR;
                        }
                        stickers2 = sticker_colorSDL(s2);
                        if (!stickers2)
                        {
                            return ERROR;
                        }

                        //Render(mov, stickers2);

                        int w, h;
                        SDL_GL_MakeCurrent(window, ctx);
                        SDL_GetWindowSize(window, &w, &h);
                        glViewport(0, 0, w, h);
                        Render(mov, stickers2);
                        SDL_GL_SwapWindow(window);
                        free(s2);
                        i++;
                        SDL_Delay(200);
                    }
                    free(solution);
                }
                j++;
                break;
            }

            //colorSDL_free(stickers); //ESTO NO ENTIENDO POR QUE DA VIOLACION DE SEGMENTO
            free(s);
            // Render(mov);
        }
        int w, h;
        SDL_GL_MakeCurrent(window, ctx);
        SDL_GetWindowSize(window, &w, &h);
        glViewport(0, 0, w, h);
        Render(mov, stickers);
        SDL_GL_SwapWindow(window);
    }
    SDL_StopTextInput();

    SDL_Delay(1000);
    quit(0);
    return 0;
}
