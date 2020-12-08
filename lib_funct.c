#include "lib_funct.h"
#include "cube.h"
#include "print_c.h"
#include "solver.h"

#define MAX_CAD 500

static SDL_GLContext ctx;
static SDL_Window *window;


void quit(int rc)
{
    if (ctx)
        SDL_GL_DeleteContext(ctx);

    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Render(double **s, int option)
{

    sCube *sc = NULL;
    int i = 0;

    if ((sc = sCube_init()) == NULL)
        return;

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glBegin(GL_QUADS);

    /* "paint" all pieces */
    for (i = 0; i < NPC; i++)
        paint_sPiece(&(sc->pc[i]), option, s);
    free_sCube(sc);

    glEnd();

}


void Render_wr(int *w, int *h, double **stickers, SDL_Window *_window, SDL_GLContext _ctx, int option){
    SDL_GL_MakeCurrent(_window, _ctx);
    SDL_GetWindowSize(_window, w, h);
    glViewport(0, 0, *w, *h);
    Render(stickers, option);
    SDL_GL_SwapWindow(_window);
}

void Rot_layer(float _angle, double **s, char c, int option)
{
    
    sCube *sc = NULL;
    int i = 0;

    if ((sc = sCube_init()) == NULL)
        return;

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0, 1.0, 1.0, 0, 0, 0, 0.5, 0, 0);

    glBegin(GL_QUADS);

    /* "paint" all pieces */
    for (i = 0; i < NPC; i++)
    {
        if (is_in_face(i, c) == 0)
        {
            paint_sPiece(&(sc->pc[i]), option, s);
        }
    }
    glEnd();
    glPushMatrix();

    /*set up the angles and axis of rotation*/
    if(c=='L'||c=='M'||c=='r')
        glRotatef(_angle, 0.0f, 0.0f, 1.0f);
    else if(c=='R'||c=='l'||c=='m')
        glRotatef(-_angle, 0.0f, 0.0f, 1.0f);
    else if(c=='E'||c=='D'||c=='u')
        glRotatef(_angle, 1.0f, 0.0f, 0.0f);
    else if(c=='U'||c=='e'||c=='d')
        glRotatef(-_angle, 1.0f, 0.0f, 0.0f);
    else if(c=='F'||c=='S'||c=='b')
        glRotatef(-_angle, 0.0f, 1.0f, 0.0f);
    else if(c=='B'||c=='f'||c=='s')
        glRotatef(_angle, 0.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
    for (i = 0; i < NPC; i++)
    {
        if (is_in_face(i, c) == 1)
        {
            paint_sPiece(&(sc->pc[i]), option, s);
        }
    }
    glPopMatrix();
    glEnd();

    free_sCube(sc);
}

void Rot_cube(float _angle, double **s, char c, int option)
{
   
    sCube *sc = NULL;
    int i = 0;

    if ((sc = sCube_init()) == NULL)
        return;

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0, 1.0, 1.0, 0, 0, 0, 0.5, 0, 0);

    glPushMatrix();
    if (c == 'x')
    {
        glRotatef(_angle, 0.0f, 0.0f, 1.0f);
    }
    else if (c == 'X')
    {
        glRotatef(-_angle, 0.0f, 0.0f, 1.0f);
    }
    else if (c == 'y')
    {
        glRotatef(_angle, 1.0f, 0.0f, 0.0f);
    }
    else if (c == 'Y')
    {
        glRotatef(-_angle, 1.0f, 0.0f, 0.0f);
    }
    else if (c == 'z')
    {
        glRotatef(_angle, 0.0f, 1.0f, 0.0f);
    }
    else if (c == 'Z')
    {
        glRotatef(-_angle, 0.0f, 1.0f, 0.0f);
    }

    glBegin(GL_QUADS);

    /* "paint" all pieces */
    for (i = 0; i < NPC; i++){
        paint_sPiece(&(sc->pc[i]), option, s);
    }

    glEnd();
    glPopMatrix();

    free_sCube(sc);
}


void Rot(float _angle, double **s, char c, int option){
    if(option==2){
        if(c == 'R'||c=='L'||c=='U'||c=='D'||c=='F'||c=='B'||c == 'r'||c=='l'||c=='u'||c=='d'||c=='f'||c=='b'){
            Rot_layer(_angle, s, c, option);
        }
    }else if (c == 'R'||c=='L'||c=='M'||c=='E'||c=='U'||c=='D'||c=='F'||c=='B'||c=='S'||c == 'r'||c=='l'||c=='m'||c=='e'||c=='u'||c=='d'||c=='f'||c=='b'||c=='s'){
        Rot_layer(_angle, s, c, option);
    }
    
    if(c == 'x'||c == 'X'||c == 'y'||c == 'Y'||c == 'z'||c == 'Z'){
        Rot_cube(_angle, s, c, option);
    }
}


void Rot_full_move(int *w, int *h, double **stickers, char move, SDL_Window *_window, SDL_GLContext _ctx, int option){
    float _angle = 0.0f;
    
    glPushMatrix();

    SDL_GL_MakeCurrent(_window, _ctx);
    SDL_GetWindowSize(_window, w, h);
    glViewport(0, 0, *w, *h);

    while (_angle <= 90.0f){
        
        Rot(_angle, stickers, move, option);
        SDL_GL_SwapWindow(_window);
        SDL_Delay(10);
        _angle += 4.0f;
    }
    glPopMatrix();
}


void SlowMoveRot(Cube3* c, int *w, int *h, double **stickers, char *moves, SDL_Window *_window, SDL_GLContext _ctx, int option){
    int i=0, len=strlen(moves);

    for(i=0;i<len;i++){
        /*display rotation*/
        Rot_full_move(w, h, stickers, moves[i], _window, _ctx, option);
        /*make move in the cube*/
        c_make(c, moves[i]);
        /*update rgb matrix*/
        cube_to_SDL(c, stickers);
    }
    /*render changes in the cube*/
    Render_wr(w, h, stickers, _window, _ctx, option);
}
