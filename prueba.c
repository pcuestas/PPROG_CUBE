#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_stdinc.h>


static SDL_GLContext ctx;
static SDL_Window *window;

static void quit(int rc){
    if (ctx)
        SDL_GL_DeleteContext(ctx);
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(rc);
}

static void Render(int mov){
    static float color[56][3] = {
        {1.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 1.0, 1.0},
        {1.0, 1.0, 1.0},
        {1.0, 0.0, 1.0},
        {0.0, 0.0, 1.0}
        }; 
    static float cube[56][3] = {
        /*{0.5, 0.5, -0.5},
        {0.5, -0.5, -0.5},
        {-0.5, -0.5, -0.5},
        {-0.5, 0.5, -0.5},
        {-0.5, 0.5, 0.5},
        {0.5, 0.5, 0.5},
        {0.5, -0.5, 0.5},
        {-0.5, -0.5, 0.5}*/
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
        {-0.2, 0.6, -0.6},//22
        {0.2, 0.6, -0.6},
        {0.2, 0.6, -0.2},
        {0.2, 0.6, 0.2},
        {-0.2, 0.6, 0.2},
        {-0.2, 0.6, -0.2},//27

        //Cara 3
        {-0.6, 0.2, 0.6},
        {-0.6, 0.2, 0.2},         
        {-0.6, 0.2, -0.2},
        {-0.6, 0.2, -0.6},
        {-0.6, -0.2, -0.6},
        {-0.6, -0.6, -0.6},//33
        {-0.6, -0.6, -0.2},
        {-0.6, -0.6, 0.2},
        {-0.6, -0.6, 0.6},
        {-0.6, -0.2, 0.6},
        {-0.6, -0.2, 0.2},
        {-0.6, -0.2, -0.2},//39


        //Cara 4
        {-0.2, -0.6, 0.6},
        {-0.2, -0.6, 0.2},         
        {-0.2, -0.6, -0.2},
        {-0.2, -0.6, -0.6},
        {0.2, -0.6, -0.6},//44
        {0.2, -0.6, -0.2},
        {0.2, -0.6, 0.2},
        {0.2, -0.6, 0.6},//47


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

    /*glColor3f(1.0, 0.0, 0.0);
    glVertex3fv(cube[0]);
    glVertex3fv(cube[1]);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[3]);

    glColor3f(1.0, 1.0, 0.0);
    glVertex3fv(cube[3]);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[7]);
    glVertex3fv(cube[2]);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3fv(cube[0]);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[6]);
    glVertex3fv(cube[1]);

    glColor3f(1.0, 0.5, 0.0);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[7]);
    glVertex3fv(cube[6]);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[0]);
    glVertex3fv(cube[3]);
    glVertex3fv(cube[4]);

    glColor3f(0.0, 1.9, 0.0);
    glVertex3fv(cube[6]);
    glVertex3fv(cube[1]);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[7]);*/



    glColor3f(1.0, 0.0, 0.0);
    glVertex3fv(cube[0]);
    glVertex3fv(cube[1]);
    glVertex3fv(cube[12]);
    glVertex3fv(cube[11]);

    glColor3f(1.0, 0.8, 0.0);
    glVertex3fv(cube[1]);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[13]);
    glVertex3fv(cube[12]);

    glColor3f(1.0, 0.2, 0.2);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[3]);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[13]);

    glColor3f(1.0, 0.5, 0.5);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[14]);
    glVertex3fv(cube[13]);

    glColor3f(0.5, 0.0, 0.0);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[6]);
    glVertex3fv(cube[7]);
    glVertex3fv(cube[14]);

    glColor3f(1.0, 0.5, 0.0);
    glVertex3fv(cube[7]);
    glVertex3fv(cube[8]);
    glVertex3fv(cube[15]);
    glVertex3fv(cube[14]);

    glColor3f(1.0, 0.0, 0.5);
    glVertex3fv(cube[8]);
    glVertex3fv(cube[9]);
    glVertex3fv(cube[10]);
    glVertex3fv(cube[15]);

    glColor3f(1.0, 0.0, 1.0);
    glVertex3fv(cube[10]);
    glVertex3fv(cube[11]);
    glVertex3fv(cube[12]);
    glVertex3fv(cube[15]);

    glColor3f(1.0, 1.0, 0.0);
    glVertex3fv(cube[12]);
    glVertex3fv(cube[13]);
    glVertex3fv(cube[14]);
    glVertex3fv(cube[15]);

//Cara 2
    glColor3f(1.0, 1.0, 0.0);
    glVertex3fv(cube[0]);
    glVertex3fv(cube[1]);
    glVertex3fv(cube[25]);
    glVertex3fv(cube[16]);

    glColor3f(1.0, 0.7, 0.8);
    glVertex3fv(cube[1]);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[24]);
    glVertex3fv(cube[25]);

    glColor3f(0.3, 0.0, 0.0);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[3]);
    glVertex3fv(cube[23]);
    glVertex3fv(cube[24]);

    glColor3f(1.0, 0.0, 0.3);
    glVertex3fv(cube[23]);
    glVertex3fv(cube[24]);
    glVertex3fv(cube[27]);
    glVertex3fv(cube[22]);

    glColor3f(1.0, 1.0, 0.5);
    glVertex3fv(cube[22]);
    glVertex3fv(cube[27]);
    glVertex3fv(cube[20]);
    glVertex3fv(cube[21]);

    glColor3f(0.5, 1.0, 1.0);
    glVertex3fv(cube[27]);
    glVertex3fv(cube[26]);
    glVertex3fv(cube[19]);
    glVertex3fv(cube[20]);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3fv(cube[26]);
    glVertex3fv(cube[17]);
    glVertex3fv(cube[18]);
    glVertex3fv(cube[19]);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3fv(cube[25]);
    glVertex3fv(cube[16]);
    glVertex3fv(cube[17]);
    glVertex3fv(cube[26]);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3fv(cube[24]);
    glVertex3fv(cube[25]);
    glVertex3fv(cube[26]);
    glVertex3fv(cube[27]);


    //Cara 3

    glColor3f(1.0, 1.0, 0.0);
    glVertex3fv(cube[18]);
    glVertex3fv(cube[19]);
    glVertex3fv(cube[29]);
    glVertex3fv(cube[28]);

    glColor3f(1.0, 0.7, 0.8);
    glVertex3fv(cube[19]);
    glVertex3fv(cube[20]);
    glVertex3fv(cube[30]);
    glVertex3fv(cube[29]);

    glColor3f(0.3, 0.0, 0.0);
    glVertex3fv(cube[20]);
    glVertex3fv(cube[21]);
    glVertex3fv(cube[31]);
    glVertex3fv(cube[30]);

    glColor3f(1.0, 0.0, 0.3);
    glVertex3fv(cube[31]);
    glVertex3fv(cube[30]);
    glVertex3fv(cube[39]);
    glVertex3fv(cube[32]);

    glColor3f(1.0, 1.0, 0.5);
    glVertex3fv(cube[32]);
    glVertex3fv(cube[39]);
    glVertex3fv(cube[34]);
    glVertex3fv(cube[33]);

    glColor3f(0.5, 1.0, 1.0);
    glVertex3fv(cube[39]);
    glVertex3fv(cube[38]);
    glVertex3fv(cube[35]);
    glVertex3fv(cube[34]);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3fv(cube[38]);
    glVertex3fv(cube[37]);
    glVertex3fv(cube[36]);
    glVertex3fv(cube[35]);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3fv(cube[29]);
    glVertex3fv(cube[28]);
    glVertex3fv(cube[37]);
    glVertex3fv(cube[38]);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3fv(cube[30]);
    glVertex3fv(cube[29]);
    glVertex3fv(cube[38]);
    glVertex3fv(cube[39]);


    //Cara 4
    glColor3f(1.0, 1.0, 0.0);
    glVertex3fv(cube[35]);
    glVertex3fv(cube[36]);
    glVertex3fv(cube[40]);
    glVertex3fv(cube[41]);

    glColor3f(1.0, 0.7, 0.8);
    glVertex3fv(cube[34]);
    glVertex3fv(cube[35]);
    glVertex3fv(cube[41]);
    glVertex3fv(cube[42]);

    glColor3f(0.3, 0.0, 0.0);
    glVertex3fv(cube[33]);
    glVertex3fv(cube[34]);
    glVertex3fv(cube[42]);
    glVertex3fv(cube[43]);

    glColor3f(1.0, 0.0, 0.3);
    glVertex3fv(cube[43]);
    glVertex3fv(cube[42]);
    glVertex3fv(cube[45]);
    glVertex3fv(cube[44]);

    glColor3f(1.0, 1.0, 0.5);
    glVertex3fv(cube[44]);
    glVertex3fv(cube[45]);
    glVertex3fv(cube[7]);
    glVertex3fv(cube[6]);

    glColor3f(0.5, 1.0, 1.0);
    glVertex3fv(cube[45]);
    glVertex3fv(cube[46]);
    glVertex3fv(cube[8]);
    glVertex3fv(cube[7]);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3fv(cube[46]);
    glVertex3fv(cube[47]);
    glVertex3fv(cube[9]);
    glVertex3fv(cube[8]);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3fv(cube[41]);
    glVertex3fv(cube[40]);
    glVertex3fv(cube[47]);
    glVertex3fv(cube[46]);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3fv(cube[42]);
    glVertex3fv(cube[41]);
    glVertex3fv(cube[46]);
    glVertex3fv(cube[45]);

    
    //Cara 5
    glColor3f(1.0, 1.0, 0.0);
    glVertex3fv(cube[11]);
    glVertex3fv(cube[48]);
    glVertex3fv(cube[16]);
    glVertex3fv(cube[0]);

    glColor3f(1.0, 0.7, 0.8);
    glVertex3fv(cube[48]);
    glVertex3fv(cube[51]);
    glVertex3fv(cube[17]);
    glVertex3fv(cube[16]);

    glColor3f(0.3, 0.0, 0.0);
    glVertex3fv(cube[51]);
    glVertex3fv(cube[28]);
    glVertex3fv(cube[18]);
    glVertex3fv(cube[17]);

    glColor3f(1.0, 0.0, 0.3);
    glVertex3fv(cube[50]);
    glVertex3fv(cube[37]);
    glVertex3fv(cube[28]);
    glVertex3fv(cube[51]);

    glColor3f(1.0, 1.0, 0.5);
    glVertex3fv(cube[40]);
    glVertex3fv(cube[36]);
    glVertex3fv(cube[37]);
    glVertex3fv(cube[50]);

    glColor3f(0.5, 1.0, 1.0);
    glVertex3fv(cube[47]);
    glVertex3fv(cube[40]);
    glVertex3fv(cube[50]);
    glVertex3fv(cube[49]);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3fv(cube[9]);
    glVertex3fv(cube[47]);
    glVertex3fv(cube[49]);
    glVertex3fv(cube[10]);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3fv(cube[10]);
    glVertex3fv(cube[49]);
    glVertex3fv(cube[48]);
    glVertex3fv(cube[11]);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3fv(cube[51]);
    glVertex3fv(cube[50]);
    glVertex3fv(cube[49]);
    glVertex3fv(cube[48]);


    //Cara 6
    glColor3f(1.0, 1.0, 0.0);
    glVertex3fv(cube[44]);
    glVertex3fv(cube[6]);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[53]);

    glColor3f(1.0, 0.7, 0.8);
    glVertex3fv(cube[43]);
    glVertex3fv(cube[44]);
    glVertex3fv(cube[53]);
    glVertex3fv(cube[54]);

    glColor3f(0.3, 0.0, 0.0);
    glVertex3fv(cube[33]);
    glVertex3fv(cube[43]);
    glVertex3fv(cube[54]);
    glVertex3fv(cube[32]);

    glColor3f(1.0, 0.0, 0.3);
    glVertex3fv(cube[32]);
    glVertex3fv(cube[54]);
    glVertex3fv(cube[55]);
    glVertex3fv(cube[31]);

    glColor3f(1.0, 1.0, 0.5);
    glVertex3fv(cube[31]);
    glVertex3fv(cube[55]);
    glVertex3fv(cube[22]);
    glVertex3fv(cube[21]);

    glColor3f(0.5, 1.0, 1.0);
    glVertex3fv(cube[55]);
    glVertex3fv(cube[52]);
    glVertex3fv(cube[23]);
    glVertex3fv(cube[22]);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3fv(cube[52]);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[3]);
    glVertex3fv(cube[23]);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3fv(cube[53]);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[52]);

    glColor3f(1.0, 0.0, 0.0);
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
    int i, done;
    SDL_DisplayMode mode;
    SDL_Event event;
    Uint32 then, now, frames;
    int status;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Create window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    window = SDL_CreateWindow("Prueba",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 940, 880,SDL_WINDOW_OPENGL);

    if (!window){
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
    then = SDL_GetTicks();
    done = 0;
    int flag = 0;
    while (!done && flag == 0)
    {
        ++frames;
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {

            if (ev.type == SDL_QUIT)
            {
                flag = 1;
                break;
            }
            else if (ev.type == SDL_KEYDOWN)
            {
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
                default:

                    break;
                }
            }
            // Render(mov);
        }
        int w, h;
        SDL_GL_MakeCurrent(window, ctx);
        SDL_GetWindowSize(window, &w, &h);
        glViewport(0, 0, w, h);
        Render(mov);
        SDL_GL_SwapWindow(window);
    }

    
    quit(0);
    return 0;
}

