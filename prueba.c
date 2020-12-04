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

void *counter(void *argv)
{
    SDL_Event event;
    SDL_Rect rect1;
    SDL_Renderer *renderer;
    SDL_Texture *texture1;
    SDL_Window *window;
    char text[200];
    int quit;
    int h, m, s;
    TTF_Font *font;
    h = m = s = 0;

    strcpy(text, "");

    /* Inint TTF. */
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    window = SDL_CreateWindow("", 440, 200, 300, 150, SDL_WINDOW_BORDERLESS);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Init();
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
        sprintf(text, "%02d:%02d:%02d", h, m, s);
        get_text_and_rect(renderer, 0, 0, text, font, &texture1, &rect1);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture1, NULL, &rect1);

        SDL_RenderPresent(renderer);

        sleep(1);
        s++;

        if (s == 60)
        {
            m += 1;
            s = 0;
        }
        if (m == 60)
        {
            h += 1;
            m = 0;
        }
        if (h == 24)
        {
            h = 0;
            m = 0;
            s = 0;
        }
        
    }

    /* Deinit TTF. */
    SDL_DestroyTexture(texture1);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
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

    pthread_create(&hilo, NULL, counter, NULL);

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
                    Rot_full_move(&w, &h, stickers, a, window, ctx, option);
                }
                if (a == 'w')
                    scramble_cube(c, SCRAMBLES_TXT);
                else if (a == 'W')
                {
                    solution = solve_cube(c);
                    c_moves(c, solution);
                    free(solution);
                }
                else if (a == 'A')
                {
                    solution = solve_cube(c);
                    printf("%s", solution);
                    free(solution);
                }
                else if (a == 'a')
                {
                    solution = solve_cube(c);
                    SlowMoveRot(c, &w, &h, stickers, solution, window, ctx, option);
                    free(solution);
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
    quit(0);

    colorSDL_free(stickers);
    c_free(c);
    pthread_detach(hilo);
    pthread_cancel(hilo);
    return 0;
}
