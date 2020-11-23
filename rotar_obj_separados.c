#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
float angleaux;

float _angle = 30.0f;
int mov;
int flag = 0;
//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: //Escape key
        exit(0);
    case 'r':
        mov = 1;
        _angle = 0;
        break;
    
    case 'R':
        mov=2;
        _angle=0;
    break;
    }
}

//Initializes 3D rendering

//Called when the window is resized
void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -20, 20);

    gluLookAt(1.5, 1.0, 1.0, 0, 0, 0, 0.5, 0, 0);
}

float _cameraAngle = 0.0f;

//Draws the 3D scene
void drawScene()
{
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(0.0f, 0.0f, -5.0f);

    //glPushMatrix();

    glBegin(GL_QUADS);

    glColor3f(1, 0, 0);
    glVertex3fv(cube[7]);
    glVertex3fv(cube[8]);
    glVertex3fv(cube[15]);
    glVertex3fv(cube[14]);

    glColor3f(1, 0, 0);
    glVertex3fv(cube[12]);
    glVertex3fv(cube[13]);
    glVertex3fv(cube[14]);
    glVertex3fv(cube[15]);

    glColor3f(1, 0, 0);
    glVertex3fv(cube[1]);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[13]);
    glVertex3fv(cube[12]);

    glColor3f(1, 0, 0);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[6]);
    glVertex3fv(cube[7]);
    glVertex3fv(cube[14]);

    glColor3f(1, 0, 0);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[14]);
    glVertex3fv(cube[13]);

    glColor3f(1, 0, 0);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[3]);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[13]);

    //Cara 2

    glColor3f(0, 1, 0);
    glVertex3fv(cube[1]);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[24]);
    glVertex3fv(cube[25]);

    glColor3f(0, 1, 0);
    glVertex3fv(cube[2]);
    glVertex3fv(cube[3]);
    glVertex3fv(cube[23]);
    glVertex3fv(cube[24]);

    glColor3f(0, 1, 0);
    glVertex3fv(cube[23]);
    glVertex3fv(cube[24]);
    glVertex3fv(cube[27]);
    glVertex3fv(cube[22]);

    glColor3f(0, 1, 0);
    glVertex3fv(cube[22]);
    glVertex3fv(cube[27]);
    glVertex3fv(cube[20]);
    glVertex3fv(cube[21]);

    glColor3f(0, 1, 0);
    glVertex3fv(cube[27]);
    glVertex3fv(cube[26]);
    glVertex3fv(cube[19]);
    glVertex3fv(cube[20]);

    glColor3f(0, 1, 0);
    glVertex3fv(cube[24]);
    glVertex3fv(cube[25]);
    glVertex3fv(cube[26]);
    glVertex3fv(cube[27]);

    //Cara 3

    glColor3f(0, 0, 1);
    glVertex3fv(cube[19]);
    glVertex3fv(cube[20]);
    glVertex3fv(cube[30]);
    glVertex3fv(cube[29]);

    glColor3f(0, 0, 1);
    glVertex3fv(cube[20]);
    glVertex3fv(cube[21]);
    glVertex3fv(cube[31]);
    glVertex3fv(cube[30]);

    glColor3f(0, 0, 1);
    glVertex3fv(cube[31]);
    glVertex3fv(cube[30]);
    glVertex3fv(cube[39]);
    glVertex3fv(cube[32]);

    glColor3f(0, 0, 1);
    glVertex3fv(cube[32]);
    glVertex3fv(cube[39]);
    glVertex3fv(cube[34]);
    glVertex3fv(cube[33]);

    glColor3f(0, 0, 1);
    glVertex3fv(cube[39]);
    glVertex3fv(cube[38]);
    glVertex3fv(cube[35]);
    glVertex3fv(cube[34]);

    glColor3f(0, 0, 1);
    glVertex3fv(cube[30]);
    glVertex3fv(cube[29]);
    glVertex3fv(cube[38]);
    glVertex3fv(cube[39]);

    //Cara 4

    glColor3f(1, 1, 1);
    glVertex3fv(cube[34]);
    glVertex3fv(cube[35]);
    glVertex3fv(cube[41]);
    glVertex3fv(cube[42]);

    glColor3f(1, 1, 1);
    glVertex3fv(cube[33]);
    glVertex3fv(cube[34]);
    glVertex3fv(cube[42]);
    glVertex3fv(cube[43]);

    glColor3f(1, 1, 1);
    glVertex3fv(cube[43]);
    glVertex3fv(cube[42]);
    glVertex3fv(cube[45]);
    glVertex3fv(cube[44]);

    glColor3f(1, 1, 1);
    glVertex3fv(cube[44]);
    glVertex3fv(cube[45]);
    glVertex3fv(cube[7]);
    glVertex3fv(cube[6]);

    glColor3f(1, 1, 1);
    glVertex3fv(cube[45]);
    glVertex3fv(cube[46]);
    glVertex3fv(cube[8]);
    glVertex3fv(cube[7]);

    glColor3f(1, 1, 1);
    glVertex3fv(cube[42]);
    glVertex3fv(cube[41]);
    glVertex3fv(cube[46]);
    glVertex3fv(cube[45]);

    //Cara 6
    glColor3f(0, 0.5, 1);
    glVertex3fv(cube[44]);
    glVertex3fv(cube[6]);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[53]);

    glColor3f(0, 0.5, 1);
    glVertex3fv(cube[43]);
    glVertex3fv(cube[44]);
    glVertex3fv(cube[53]);
    glVertex3fv(cube[54]);

    glColor3f(0, 0.5, 1);
    glVertex3fv(cube[33]);
    glVertex3fv(cube[43]);
    glVertex3fv(cube[54]);
    glVertex3fv(cube[32]);

    glColor3f(0, 0.5, 1);
    glVertex3fv(cube[32]);
    glVertex3fv(cube[54]);
    glVertex3fv(cube[55]);
    glVertex3fv(cube[31]);

    glColor3f(0, 0.5, 1);
    glVertex3fv(cube[31]);
    glVertex3fv(cube[55]);
    glVertex3fv(cube[22]);
    glVertex3fv(cube[21]);

    glColor3f(0, 0.5, 1);
    glVertex3fv(cube[55]);
    glVertex3fv(cube[52]);
    glVertex3fv(cube[23]);
    glVertex3fv(cube[22]);

    glColor3f(0, 0.5, 1);
    glVertex3fv(cube[52]);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[3]);
    glVertex3fv(cube[23]);

    glColor3f(0, 0.5, 1);
    glVertex3fv(cube[53]);
    glVertex3fv(cube[5]);
    glVertex3fv(cube[4]);
    glVertex3fv(cube[52]);

    glColor3f(0, 0.5, 1);
    glVertex3fv(cube[53]);
    glVertex3fv(cube[54]);
    glVertex3fv(cube[55]);
    glVertex3fv(cube[52]);

    glColor3f(0, 0, 0);
    glVertex3f(0.6, 0.6, 0.2);
    glVertex3f(0.6, -0.6, 0.2);
    glVertex3f(-0.6, -0.6, 0.2);
    glVertex3f(-0.6, 0.6, 0.2);

    glEnd();

    /*glPopMatrix();*/

    if (mov == 1)
    {
        if (_angle < 90.0f)
        {
            glPushMatrix();
            glRotatef(_angle, 0.0f, 0.0f, 1.0f);

            glBegin(GL_QUADS);

            //Cara blanca-roja

            glColor3f(1, 0, 0);
            glVertex3fv(cube[8]);
            glVertex3fv(cube[9]);
            glVertex3fv(cube[10]);
            glVertex3fv(cube[15]);

            glColor3f(1, 0, 0);
            glVertex3fv(cube[10]);
            glVertex3fv(cube[11]);
            glVertex3fv(cube[12]);
            glVertex3fv(cube[15]);

            glColor3f(1, 0, 0);
            glVertex3fv(cube[0]);
            glVertex3fv(cube[1]);
            glVertex3fv(cube[12]);
            glVertex3fv(cube[11]);

            //Cara verde-roja

            glColor3f(0, 1, 0);
            glVertex3fv(cube[0]);
            glVertex3fv(cube[1]);
            glVertex3fv(cube[25]);
            glVertex3fv(cube[16]);

            glColor3f(0, 1, 0);
            glVertex3fv(cube[26]);
            glVertex3fv(cube[17]);
            glVertex3fv(cube[18]);
            glVertex3fv(cube[19]);

            glColor3f(0, 1, 0);
            glVertex3fv(cube[25]);
            glVertex3fv(cube[16]);
            glVertex3fv(cube[17]);
            glVertex3fv(cube[26]);

            //Cara amarillo-roja

            glColor3f(0, 0, 1);
            glVertex3fv(cube[18]);
            glVertex3fv(cube[19]);
            glVertex3fv(cube[29]);
            glVertex3fv(cube[28]);

            glColor3f(0, 0, 1);
            glVertex3fv(cube[38]);
            glVertex3fv(cube[37]);
            glVertex3fv(cube[36]);
            glVertex3fv(cube[35]);

            glColor3f(0, 0, 1);
            glVertex3fv(cube[29]);
            glVertex3fv(cube[28]);
            glVertex3fv(cube[37]);
            glVertex3fv(cube[38]);

            //Cara azul-roja

            glColor3f(1, 1, 1);
            glVertex3fv(cube[35]);
            glVertex3fv(cube[36]);
            glVertex3fv(cube[40]);
            glVertex3fv(cube[41]);

            glColor3f(1, 1, 1);
            glVertex3fv(cube[46]);
            glVertex3fv(cube[47]);
            glVertex3fv(cube[9]);
            glVertex3fv(cube[8]);

            glColor3f(1, 1, 1);
            glVertex3fv(cube[41]);
            glVertex3fv(cube[40]);
            glVertex3fv(cube[47]);
            glVertex3fv(cube[46]);

            //Cara roja
            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[11]);
            glVertex3fv(cube[48]);
            glVertex3fv(cube[16]);
            glVertex3fv(cube[0]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[48]);
            glVertex3fv(cube[51]);
            glVertex3fv(cube[17]);
            glVertex3fv(cube[16]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[51]);
            glVertex3fv(cube[28]);
            glVertex3fv(cube[18]);
            glVertex3fv(cube[17]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[50]);
            glVertex3fv(cube[37]);
            glVertex3fv(cube[28]);
            glVertex3fv(cube[51]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[40]);
            glVertex3fv(cube[36]);
            glVertex3fv(cube[37]);
            glVertex3fv(cube[50]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[47]);
            glVertex3fv(cube[40]);
            glVertex3fv(cube[50]);
            glVertex3fv(cube[49]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[9]);
            glVertex3fv(cube[47]);
            glVertex3fv(cube[49]);
            glVertex3fv(cube[10]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[10]);
            glVertex3fv(cube[49]);
            glVertex3fv(cube[48]);
            glVertex3fv(cube[11]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[51]);
            glVertex3fv(cube[50]);
            glVertex3fv(cube[49]);
            glVertex3fv(cube[48]);
            glEnd();

            glPopMatrix();
            if (_angle == 90)
                mov = 0;
        }
        else if (_angle >= 90.0f)
        {
            glBegin(GL_QUADS);

            //Cara blanca-roja

            glColor3f(1, 1, 1);
            glVertex3fv(cube[8]);
            glVertex3fv(cube[9]);
            glVertex3fv(cube[10]);
            glVertex3fv(cube[15]);

            glColor3f(1, 1, 1);
            glVertex3fv(cube[10]);
            glVertex3fv(cube[11]);
            glVertex3fv(cube[12]);
            glVertex3fv(cube[15]);

            glColor3f(1, 1, 1);
            glVertex3fv(cube[0]);
            glVertex3fv(cube[1]);
            glVertex3fv(cube[12]);
            glVertex3fv(cube[11]);

            //Cara verde-roja

            glColor3f(1, 0, 0);
            glVertex3fv(cube[0]);
            glVertex3fv(cube[1]);
            glVertex3fv(cube[25]);
            glVertex3fv(cube[16]);

            glColor3f(1, 0, 0);
            glVertex3fv(cube[26]);
            glVertex3fv(cube[17]);
            glVertex3fv(cube[18]);
            glVertex3fv(cube[19]);

            glColor3f(1, 0, 0);
            glVertex3fv(cube[25]);
            glVertex3fv(cube[16]);
            glVertex3fv(cube[17]);
            glVertex3fv(cube[26]);

            //Cara amarillo-roja

            glColor3f(0, 0, 1);
            glVertex3fv(cube[18]);
            glVertex3fv(cube[19]);
            glVertex3fv(cube[29]);
            glVertex3fv(cube[28]);

            glColor3f(0, 0, 1);
            glVertex3fv(cube[38]);
            glVertex3fv(cube[37]);
            glVertex3fv(cube[36]);
            glVertex3fv(cube[35]);

            glColor3f(0, 0, 1);
            glVertex3fv(cube[29]);
            glVertex3fv(cube[28]);
            glVertex3fv(cube[37]);
            glVertex3fv(cube[38]);

            //Cara azul-roja

            glColor3f(1, 1, 1);
            glVertex3fv(cube[35]);
            glVertex3fv(cube[36]);
            glVertex3fv(cube[40]);
            glVertex3fv(cube[41]);

            glColor3f(1, 1, 1);
            glVertex3fv(cube[46]);
            glVertex3fv(cube[47]);
            glVertex3fv(cube[9]);
            glVertex3fv(cube[8]);

            glColor3f(1, 1, 1);
            glVertex3fv(cube[41]);
            glVertex3fv(cube[40]);
            glVertex3fv(cube[47]);
            glVertex3fv(cube[46]);

            //Cara roja
            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[11]);
            glVertex3fv(cube[48]);
            glVertex3fv(cube[16]);
            glVertex3fv(cube[0]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[48]);
            glVertex3fv(cube[51]);
            glVertex3fv(cube[17]);
            glVertex3fv(cube[16]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[51]);
            glVertex3fv(cube[28]);
            glVertex3fv(cube[18]);
            glVertex3fv(cube[17]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[50]);
            glVertex3fv(cube[37]);
            glVertex3fv(cube[28]);
            glVertex3fv(cube[51]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[40]);
            glVertex3fv(cube[36]);
            glVertex3fv(cube[37]);
            glVertex3fv(cube[50]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[47]);
            glVertex3fv(cube[40]);
            glVertex3fv(cube[50]);
            glVertex3fv(cube[49]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[9]);
            glVertex3fv(cube[47]);
            glVertex3fv(cube[49]);
            glVertex3fv(cube[10]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[10]);
            glVertex3fv(cube[49]);
            glVertex3fv(cube[48]);
            glVertex3fv(cube[11]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[51]);
            glVertex3fv(cube[50]);
            glVertex3fv(cube[49]);
            glVertex3fv(cube[48]);
            glEnd();
        }
    }
    else if (mov == 2)
    {
        if (_angle < 90.0f)
        {
            glPushMatrix();
            glRotatef(-_angle, 0.0f, 0.0f, 1.0f);

            glBegin(GL_QUADS);

            //Cara blanca-roja

            glColor3f(1, 0, 0);
            glVertex3fv(cube[8]);
            glVertex3fv(cube[9]);
            glVertex3fv(cube[10]);
            glVertex3fv(cube[15]);

            glColor3f(1, 0, 0);
            glVertex3fv(cube[10]);
            glVertex3fv(cube[11]);
            glVertex3fv(cube[12]);
            glVertex3fv(cube[15]);

            glColor3f(1, 0, 0);
            glVertex3fv(cube[0]);
            glVertex3fv(cube[1]);
            glVertex3fv(cube[12]);
            glVertex3fv(cube[11]);

            //Cara verde-roja

            glColor3f(0, 1, 0);
            glVertex3fv(cube[0]);
            glVertex3fv(cube[1]);
            glVertex3fv(cube[25]);
            glVertex3fv(cube[16]);

            glColor3f(0, 1, 0);
            glVertex3fv(cube[26]);
            glVertex3fv(cube[17]);
            glVertex3fv(cube[18]);
            glVertex3fv(cube[19]);

            glColor3f(0, 1, 0);
            glVertex3fv(cube[25]);
            glVertex3fv(cube[16]);
            glVertex3fv(cube[17]);
            glVertex3fv(cube[26]);

            //Cara amarillo-roja

            glColor3f(0, 0, 1);
            glVertex3fv(cube[18]);
            glVertex3fv(cube[19]);
            glVertex3fv(cube[29]);
            glVertex3fv(cube[28]);

            glColor3f(0, 0, 1);
            glVertex3fv(cube[38]);
            glVertex3fv(cube[37]);
            glVertex3fv(cube[36]);
            glVertex3fv(cube[35]);

            glColor3f(0, 0, 1);
            glVertex3fv(cube[29]);
            glVertex3fv(cube[28]);
            glVertex3fv(cube[37]);
            glVertex3fv(cube[38]);

            //Cara azul-roja

            glColor3f(1, 1, 1);
            glVertex3fv(cube[35]);
            glVertex3fv(cube[36]);
            glVertex3fv(cube[40]);
            glVertex3fv(cube[41]);

            glColor3f(1, 1, 1);
            glVertex3fv(cube[46]);
            glVertex3fv(cube[47]);
            glVertex3fv(cube[9]);
            glVertex3fv(cube[8]);

            glColor3f(1, 1, 1);
            glVertex3fv(cube[41]);
            glVertex3fv(cube[40]);
            glVertex3fv(cube[47]);
            glVertex3fv(cube[46]);

            //Cara roja
            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[11]);
            glVertex3fv(cube[48]);
            glVertex3fv(cube[16]);
            glVertex3fv(cube[0]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[48]);
            glVertex3fv(cube[51]);
            glVertex3fv(cube[17]);
            glVertex3fv(cube[16]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[51]);
            glVertex3fv(cube[28]);
            glVertex3fv(cube[18]);
            glVertex3fv(cube[17]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[50]);
            glVertex3fv(cube[37]);
            glVertex3fv(cube[28]);
            glVertex3fv(cube[51]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[40]);
            glVertex3fv(cube[36]);
            glVertex3fv(cube[37]);
            glVertex3fv(cube[50]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[47]);
            glVertex3fv(cube[40]);
            glVertex3fv(cube[50]);
            glVertex3fv(cube[49]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[9]);
            glVertex3fv(cube[47]);
            glVertex3fv(cube[49]);
            glVertex3fv(cube[10]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[10]);
            glVertex3fv(cube[49]);
            glVertex3fv(cube[48]);
            glVertex3fv(cube[11]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[51]);
            glVertex3fv(cube[50]);
            glVertex3fv(cube[49]);
            glVertex3fv(cube[48]);
            glEnd();

            glPopMatrix();
            if (_angle == 90)
                mov = 0;
        }
        else if (_angle >= 90.0f)
        {
            glBegin(GL_QUADS);

            //Cara blanca-roja

            glColor3f(0,1,0);
            glVertex3fv(cube[8]);
            glVertex3fv(cube[9]);
            glVertex3fv(cube[10]);
            glVertex3fv(cube[15]);

            glColor3f(0,1,0);
            glVertex3fv(cube[10]);
            glVertex3fv(cube[11]);
            glVertex3fv(cube[12]);
            glVertex3fv(cube[15]);

            glColor3f(0,1,0);
            glVertex3fv(cube[0]);
            glVertex3fv(cube[1]);
            glVertex3fv(cube[12]);
            glVertex3fv(cube[11]);

            //Cara verde-roja

            glColor3f(0,0,1);
            glVertex3fv(cube[0]);
            glVertex3fv(cube[1]);
            glVertex3fv(cube[25]);
            glVertex3fv(cube[16]);

            glColor3f(0,0,1);
            glVertex3fv(cube[26]);
            glVertex3fv(cube[17]);
            glVertex3fv(cube[18]);
            glVertex3fv(cube[19]);

            glColor3f(0,0,1);
            glVertex3fv(cube[25]);
            glVertex3fv(cube[16]);
            glVertex3fv(cube[17]);
            glVertex3fv(cube[26]);

            //Cara amarillo-roja

            glColor3f(0, 0, 1);
            glVertex3fv(cube[18]);
            glVertex3fv(cube[19]);
            glVertex3fv(cube[29]);
            glVertex3fv(cube[28]);

            glColor3f(0, 0, 1);
            glVertex3fv(cube[38]);
            glVertex3fv(cube[37]);
            glVertex3fv(cube[36]);
            glVertex3fv(cube[35]);

            glColor3f(0, 0, 1);
            glVertex3fv(cube[29]);
            glVertex3fv(cube[28]);
            glVertex3fv(cube[37]);
            glVertex3fv(cube[38]);

            //Cara azul-roja

            glColor3f(1, 1, 1);
            glVertex3fv(cube[35]);
            glVertex3fv(cube[36]);
            glVertex3fv(cube[40]);
            glVertex3fv(cube[41]);

            glColor3f(1, 1, 1);
            glVertex3fv(cube[46]);
            glVertex3fv(cube[47]);
            glVertex3fv(cube[9]);
            glVertex3fv(cube[8]);

            glColor3f(1, 1, 1);
            glVertex3fv(cube[41]);
            glVertex3fv(cube[40]);
            glVertex3fv(cube[47]);
            glVertex3fv(cube[46]);

            //Cara roja
            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[11]);
            glVertex3fv(cube[48]);
            glVertex3fv(cube[16]);
            glVertex3fv(cube[0]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[48]);
            glVertex3fv(cube[51]);
            glVertex3fv(cube[17]);
            glVertex3fv(cube[16]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[51]);
            glVertex3fv(cube[28]);
            glVertex3fv(cube[18]);
            glVertex3fv(cube[17]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[50]);
            glVertex3fv(cube[37]);
            glVertex3fv(cube[28]);
            glVertex3fv(cube[51]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[40]);
            glVertex3fv(cube[36]);
            glVertex3fv(cube[37]);
            glVertex3fv(cube[50]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[47]);
            glVertex3fv(cube[40]);
            glVertex3fv(cube[50]);
            glVertex3fv(cube[49]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[9]);
            glVertex3fv(cube[47]);
            glVertex3fv(cube[49]);
            glVertex3fv(cube[10]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[10]);
            glVertex3fv(cube[49]);
            glVertex3fv(cube[48]);
            glVertex3fv(cube[11]);

            glColor3f(1, 0.5, 0);
            glVertex3fv(cube[51]);
            glVertex3fv(cube[50]);
            glVertex3fv(cube[49]);
            glVertex3fv(cube[48]);
            glEnd();
        }
    }
    else
    {
        glBegin(GL_QUADS);

        //Cara blanca-roja

        glColor3f(1, 0, 0);
        glVertex3fv(cube[8]);
        glVertex3fv(cube[9]);
        glVertex3fv(cube[10]);
        glVertex3fv(cube[15]);

        glColor3f(1, 0, 0);
        glVertex3fv(cube[10]);
        glVertex3fv(cube[11]);
        glVertex3fv(cube[12]);
        glVertex3fv(cube[15]);

        glColor3f(1, 0, 0);
        glVertex3fv(cube[0]);
        glVertex3fv(cube[1]);
        glVertex3fv(cube[12]);
        glVertex3fv(cube[11]);

        //Cara verde-roja

        glColor3f(0, 1, 0);
        glVertex3fv(cube[0]);
        glVertex3fv(cube[1]);
        glVertex3fv(cube[25]);
        glVertex3fv(cube[16]);

        glColor3f(0, 1, 0);
        glVertex3fv(cube[26]);
        glVertex3fv(cube[17]);
        glVertex3fv(cube[18]);
        glVertex3fv(cube[19]);

        glColor3f(0, 1, 0);
        glVertex3fv(cube[25]);
        glVertex3fv(cube[16]);
        glVertex3fv(cube[17]);
        glVertex3fv(cube[26]);

        //Cara amarillo-roja

        glColor3f(0, 0, 1);
        glVertex3fv(cube[18]);
        glVertex3fv(cube[19]);
        glVertex3fv(cube[29]);
        glVertex3fv(cube[28]);

        glColor3f(0, 0, 1);
        glVertex3fv(cube[38]);
        glVertex3fv(cube[37]);
        glVertex3fv(cube[36]);
        glVertex3fv(cube[35]);

        glColor3f(0, 0, 1);
        glVertex3fv(cube[29]);
        glVertex3fv(cube[28]);
        glVertex3fv(cube[37]);
        glVertex3fv(cube[38]);

        //Cara azul-roja

        glColor3f(1, 1, 1);
        glVertex3fv(cube[35]);
        glVertex3fv(cube[36]);
        glVertex3fv(cube[40]);
        glVertex3fv(cube[41]);

        glColor3f(1, 1, 1);
        glVertex3fv(cube[46]);
        glVertex3fv(cube[47]);
        glVertex3fv(cube[9]);
        glVertex3fv(cube[8]);

        glColor3f(1, 1, 1);
        glVertex3fv(cube[41]);
        glVertex3fv(cube[40]);
        glVertex3fv(cube[47]);
        glVertex3fv(cube[46]);

        //Cara roja
        glColor3f(1, 0.5, 0);
        glVertex3fv(cube[11]);
        glVertex3fv(cube[48]);
        glVertex3fv(cube[16]);
        glVertex3fv(cube[0]);

        glColor3f(1, 0.5, 0);
        glVertex3fv(cube[48]);
        glVertex3fv(cube[51]);
        glVertex3fv(cube[17]);
        glVertex3fv(cube[16]);

        glColor3f(1, 0.5, 0);
        glVertex3fv(cube[51]);
        glVertex3fv(cube[28]);
        glVertex3fv(cube[18]);
        glVertex3fv(cube[17]);

        glColor3f(1, 0.5, 0);
        glVertex3fv(cube[50]);
        glVertex3fv(cube[37]);
        glVertex3fv(cube[28]);
        glVertex3fv(cube[51]);

        glColor3f(1, 0.5, 0);
        glVertex3fv(cube[40]);
        glVertex3fv(cube[36]);
        glVertex3fv(cube[37]);
        glVertex3fv(cube[50]);

        glColor3f(1, 0.5, 0);
        glVertex3fv(cube[47]);
        glVertex3fv(cube[40]);
        glVertex3fv(cube[50]);
        glVertex3fv(cube[49]);

        glColor3f(1, 0.5, 0);
        glVertex3fv(cube[9]);
        glVertex3fv(cube[47]);
        glVertex3fv(cube[49]);
        glVertex3fv(cube[10]);

        glColor3f(1, 0.5, 0);
        glVertex3fv(cube[10]);
        glVertex3fv(cube[49]);
        glVertex3fv(cube[48]);
        glVertex3fv(cube[11]);

        glColor3f(1, 0.5, 0);
        glVertex3fv(cube[51]);
        glVertex3fv(cube[50]);
        glVertex3fv(cube[49]);
        glVertex3fv(cube[48]);
        glEnd();
    }


glutSwapBuffers();
}

void update(int value)
{
    _angle += 1.0f;
    if (_angle > 360)
    {
        _angle -= 360;
    }

    glutPostRedisplay(); /*Tell GLUT that the scene has changed*/
    glutTimerFunc(10, update, 0);
}

int main(int argc, char **argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);

    //Create the window
    glutCreateWindow("Color");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);          /*Enable color*/
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f); /*Change the background to sky blue*/

    glutDisplayFunc(drawScene);

    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);

    glutTimerFunc(25, update, 0); /*Add a timer*/

    glutMainLoop();
    return 0;
}
