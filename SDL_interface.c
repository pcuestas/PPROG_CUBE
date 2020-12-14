#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include "cube.h"
#include "print_c.h"
#include "solver.h"
#include "lib_funct.h"

#ifndef SCRAMBLES_TXT
#define SCRAMBLES_TXT "./txt_files/scrambles.txt"
#endif

#ifndef FONT_TTF
#define FONT_TTF "/usr/share/fonts/truetype/freefont/FreeMonoOblique.ttf"
#endif

#define MAX_CAD 500

pthread_mutex_t mutex_sdl = PTHREAD_MUTEX_INITIALIZER;


typedef struct _counter_data_sdl counter_data_sdl;

struct _counter_data_sdl
{
    int sec, min, h, mode; /*Mode=0: show time 00:00. Mode=-1 Counter stopped. Mode=1 Counter running. Mode=2 kill thread*/
};

void *counter(void *dat)
{
    SDL_Event event;
    SDL_Rect rect1;
    SDL_Renderer *renderer;
    SDL_Texture *texture1 = NULL;
    SDL_Window *window;
    char text[200];
    int quit, stop = 0, blank = 0;
    TTF_Font *font;
    /*h = m = s = 0;*/

    counter_data_sdl *d;
    d = (counter_data_sdl *)dat;

    strcpy(text, "");

    /* Inint TTF. */
    window = SDL_CreateWindow("", 440, 150, 300, 150, SDL_WINDOW_BORDERLESS);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    font = TTF_OpenFont(FONT_TTF, 50);
    if (font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }

    quit = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&event) == 1)
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
        }

        while (d->mode == 1)
        {
            stop = 0;
            blank = 0;
            sprintf(text, "%02d:%02d:%02d", d->h, d->min, d->sec);
            SDL_DisplayText(renderer, text, font);

            sleep(1);
            d->sec++;

            if (d->sec == 60)
            {
                d->min += 1;
                d->sec = 0;
            }
            if (d->min == 60)
            {
                d->h += 1;
                d->min = 0;
            }
            if (d->h == 24)
            {
                d->h = 0;
                d->min = 0;
                d->sec = 0;
            }
        }

        while (d->mode == 0)
        {
            stop = 0;
            if (blank == 0)
            {
                sprintf(text, "%02d:%02d:%02d", 0, 0, 0);
                SDL_DisplayText(renderer, text, font);
                blank = 1;
            }
        }

        while (d->mode == -1)
        {
            blank = 0;
            if (stop == 0)
            {
                sprintf(text, "%02d:%02d:%02d", d->h, d->min, d->sec);
                SDL_DisplayText(renderer, text, font);
            }
        }

        if (d->mode == 2)
        {
            pthread_mutex_lock(&mutex_sdl);
            SDL_DestroyTexture(texture1);

            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            pthread_mutex_unlock(&mutex_sdl);
            return NULL;
        }
    }

    return NULL;
}

int SDL_interface(int option, int use_saved_game, char *save_game_file)
{
    Cube3 *c = NULL;

    SDL_GLContext ctx;
    SDL_Window *window, *window2;
    SDL_Renderer *renderer;
    SDL_Event ev;
    TTF_Font *font2=NULL;

    char text[MAX_CAD] = "", a = 0, *solution = NULL, scramble[MAX_LINE];
    double **stickers = NULL;
    int flag = 0, j = 0, w, h, flag2=0;

    

    pthread_t hilo;
    counter_data_sdl dat;
    int stop = 0, firstmove = 0;
    dat.min = 0;
    dat.sec = 0;
    dat.h = 0;
    dat.mode = 0;

    c = c_init(option);
    if (!c)
        return 1;

    if (use_saved_game == TRUE)
    {
        if (read_saved_cube(c, save_game_file) == ERROR)
        {
            c_free(c);
            return ERROR;
        }
        option = c->option;
    }
    stickers = sticker_colorSDL_init();
    if (!stickers)
    {
        c_free(c);
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    pthread_create(&hilo, NULL, counter, &dat);

    /*Create window*/
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    window = SDL_CreateWindow("Rubik Cube PPROG", 400, 100, 940, 880, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window)
    {
        printf("SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    TTF_Init();

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

    gluLookAt(1.0, 1.0, 1.0, 0, 0, 0, 0.5, 0, 0);
    /* Main loop */
    SDL_StartTextInput();
    while (flag == 0)
    {

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
                case SDLK_ESCAPE:
                    flag = 1;
                    break;
                }
                break;
            case SDL_TEXTINPUT:
                /*update rgb matrix*/
                cube_to_SDL(c, stickers);

                strcat(text, ev.text.text);

                a = text[j]; /*letter read*/


                if (a == 'R' || a == 'L' || a == 'M' || a == 'E' || a == 'U' || a == 'D' || a == 'F' || a == 'B' || a == 'S' || a == 'r' || a == 'l' || a == 'm' || a == 'e' || a == 'u' || a == 'd' || a == 'f' || a == 'b' || a == 's' || a == 'x' || a == 'X' || a == 'y' || a == 'Y' || a == 'z' || a == 'Z')
                {
                    if (firstmove == 0)
                    {
                        pthread_mutex_lock(&mutex_sdl);
                        dat.mode = 1; /*Counter running*/
                        pthread_mutex_unlock(&mutex_sdl);
                        firstmove = 1;
                    }
                    Rot_full_move(&w, &h, stickers, a, window, ctx, option);
                }
                if (a == 'w')
                {
                    scramble_cube(c, SCRAMBLES_TXT, scramble);

                    SDL_DisplayTextWRAPPER(&window2, scramble, &renderer, font2);

                    flag2=1;
                    
                    pthread_mutex_lock(&mutex_sdl);
                    dat.min = 0;
                    dat.sec = 0;
                    dat.h = 0;
                    dat.mode = 0;
                    pthread_mutex_unlock(&mutex_sdl);
                    firstmove = 0;
                }
                else if (a == 'W')
                {             
                    solution = solve_cube(c); 
                    SDL_DisplayTextWRAPPER(&window2, solution, &renderer, font2);

                    flag2=1;
                    
                    c_moves(c, solution);
                    free(solution);
                }
                else if (a == 'A')
                {                                       
                    solution = solve_cube(c); 

                    SDL_DisplayTextWRAPPER(&window2, solution, &renderer, font2);

                    flag2=1;
                    free(solution);
                }
                else if (a == 'a')
                {                                                          
                    solution = solve_cube(c); 

                    SDL_DisplayTextWRAPPER(&window2, solution, &renderer, font2);

                    flag2=1;

                    pthread_mutex_lock(&mutex_sdl);
                    dat.mode = 0;
                    pthread_mutex_unlock(&mutex_sdl);

                    SlowMoveRot(c, &w, &h, stickers, solution, window, ctx, option);

                    free(solution);
                    firstmove = 0;
                }
                else if (a == 32)
                {
                    if (stop == 0)
                    { /*counter was running*/
                        pthread_mutex_lock(&mutex_sdl);
                        dat.mode = -1;
                        pthread_mutex_unlock(&mutex_sdl);
                        stop = 1;
                    }
                    else
                    {
                        pthread_mutex_lock(&mutex_sdl);
                        dat.mode = 1;
                        dat.min = 0;
                        dat.sec = 0;
                        dat.h = 0;
                        pthread_mutex_unlock(&mutex_sdl);
                        stop = 0;
                    }
                }
                c_make(c, a); /*make move in the cube*/
                j++;
                break;
            }
        }

        /*update rgb matrix*/
        cube_to_SDL(c, stickers);
        /*render changes in the cube*/
        Render_wr(&w, &h, stickers, window, ctx, option);
    }
    SDL_StopTextInput();

    if (save_cube(c, save_game_file) == ERROR)
        printf("There was an error when saving the game.\n");

    pthread_mutex_lock(&mutex_sdl);
    dat.mode = 2; /*To suicide thread*/
    pthread_mutex_unlock(&mutex_sdl);

    SDL_Delay(1000);
    pthread_detach(hilo);
    pthread_cancel(hilo);

    colorSDL_free(stickers);
    c_free(c);

    /*pthread_join(hilo,NULL); Ya no es necesario. con mode2 hacemos que el hilo haga return*/
    /*pthread_cancel(hilo);*/
     
    TTF_Quit();
    quit(0);
    return 0;
}
