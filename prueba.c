#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <GL/glut.h>

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

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

typedef struct _counter_data counter_data;

struct _counter_data{
    int sec, min, h,mode; /*Mode=0: show time 00:00. Mode=-1 Counter stopped. Mode=1 Counter running. Mode=2 kill thread*/
};

void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect)
{
    int ancho, alto;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);

    ancho = surface->w;
    alto = surface->h;
    rect->x = x;
    rect->y = y;

    rect->w = ancho;
    rect->h = alto;


    SDL_FreeSurface(surface);
}

void *counter(void *dat){
    SDL_Event event;
    SDL_Rect rect1;
    SDL_Renderer *renderer;
    SDL_Texture *texture1;
    SDL_Window *window;
    char text[200];
    int quit,stop=0,blank=0;
    TTF_Font *font;
    /*h = m = s = 0;*/
    
    counter_data *d;
    d=(counter_data*)dat;

    strcpy(text, "");

    /* Inint TTF. */
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    window = SDL_CreateWindow("", 440, 100, 300, 150, SDL_WINDOW_BORDERLESS);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Init();
    font = TTF_OpenFont(FONT_TTF, 50);
    if (font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }

    quit = 0;
    while (!quit){
        while (SDL_PollEvent(&event) == 1){
            if (event.type == SDL_QUIT){
                quit = 1;
            }
        }


        while(d->mode==1){
            stop=0;
            blank=0;
            sprintf(text, "%02d:%02d:%02d", d->h, d->min, d->sec);
            get_text_and_rect(renderer, 0, 0, text, font, &texture1, &rect1);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);

            SDL_RenderCopy(renderer, texture1, NULL, &rect1);

            SDL_RenderPresent(renderer);

            sleep(1);
            d->sec++;

            if (d->sec == 60){
                d->min += 1;
                d->sec = 0;
            }
            if (d->min == 60){
                d->h += 1;
                d->min = 0;
            }
            if (d->h == 24){
                d->h = 0;
                d->min = 0;
                d->sec = 0;
            }
        
        }

        while(d->mode==0){
            stop=0;
            if(blank==0){
            sprintf(text, "%02d:%02d:%02d", 0, 0, 0);
            get_text_and_rect(renderer, 0, 0, text, font, &texture1, &rect1);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture1, NULL, &rect1);
            SDL_RenderPresent(renderer);
            blank=1;
            }
        }

        while(d->mode==-1){
            blank=0;
            if(stop==0){
            sprintf(text, "%02d:%02d:%02d", d->h, d->min, d->sec);
            get_text_and_rect(renderer, 0, 0, text, font, &texture1, &rect1);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture1, NULL, &rect1);
            SDL_RenderPresent(renderer);
            stop=1;
            }
        }

        if(d->mode==2){
            pthread_mutex_lock(&mutex);
            SDL_DestroyTexture(texture1);
            TTF_Quit();
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
           /* SDL_Quit();*/
            pthread_mutex_unlock(&mutex);
            return;
        }
    }

   
}

int main(int option)
{
    int flag = 0, j = 0, w, h;
    Cube3 *c = NULL;
    SDL_Event ev;
    char text[200] = "", a = 0, *solution = NULL;
    double **stickers = NULL;
    SDL_GLContext ctx;
    SDL_Window *window;

    pthread_t hilo;
    counter_data dat;
    int stop=0,firstmove=0;
    dat.min = 0;
    dat.sec = 0;
    dat.h = 0;
    dat.mode = 0;

    /*************************************/
    option = 2;
    /*************************************/

    c = c_init(option);
    if (!c)
        return 1;

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

    srand(time(NULL));

    pthread_create(&hilo, NULL, counter, &dat);

    /*Create window*/
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    window = SDL_CreateWindow("Rubik Cube PPROG", 400, 100, 940, 880, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

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
    while (flag == 0){

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

                a = text[j]; /*letter read*/

                if (a == 'R' || a == 'L' || a == 'M' || a == 'E' || a == 'U' || a == 'D' || a == 'F' || a == 'B' || a == 'S' || a == 'r' || a == 'l' || a == 'm' || a == 'e' || a == 'u' || a == 'd' || a == 'f' || a == 'b' || a == 's' || a == 'x' || a == 'X' || a == 'y' || a == 'Y' || a == 'z' || a == 'Z'){   
                    if(firstmove==0){
                        pthread_mutex_lock(&mutex);
                        dat.mode=1; /*Counter running*/
                        pthread_mutex_unlock(&mutex);
                        firstmove = 1;
                    }
                    Rot_full_move(&w, &h, stickers, a, window, ctx, option);
                }
                if (a == 'w'){
                    scramble_cube(c, SCRAMBLES_TXT);
                    pthread_mutex_lock(&mutex);
                    dat.min=0;
                    dat.sec=0;
                    dat.h=0;
                    dat.mode=0;
                    pthread_mutex_unlock(&mutex);
                    firstmove = 0;
                }
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
                    pthread_mutex_lock(&mutex);
                    dat.mode=0;
                    pthread_mutex_unlock(&mutex);
                    SlowMoveRot(c, &w, &h, stickers, solution, window, ctx, option);
                    free(solution);
                }
                else if(a==32){
                    if (stop == 0){ /*counter was running*/
                        pthread_mutex_lock(&mutex);
                        dat.mode = -1;
                        pthread_mutex_unlock(&mutex);
                        stop = 1;
                    }
                    else{
                        pthread_mutex_lock(&mutex);
                        dat.mode = 1;
                        dat.min = 0;
                        dat.sec = 0;
                        dat.h = 0;
                        pthread_mutex_unlock(&mutex);
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
    
    SDL_Delay(1000);
    pthread_detach(hilo);

    colorSDL_free(stickers);
    c_free(c);

    pthread_mutex_lock(&mutex);
    dat.mode=2; /*To suicide thread*/
    pthread_mutex_unlock(&mutex);
    /*pthread_join(hilo,NULL);*/
    /*pthread_cancel(hilo);*/
    quit(0);
    return 0;
}
