#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "bcd.h"

#define GROSOR 3 /*grosor del tramo*/
#define LONG 5   /*longitud del tramo*/
#define CHAR 32  /*char used to draw bcd*/
#define COLOR 7

/*

          aaaaa
         f     b
         f     b
         f     b
          ggggg
         e     c      
         e     c 
         e     c 
          dddd
*/

void bcd_a(int l, int c)
{
    int line, column, i, j;
    line = l;
    column = c;

    printf("%c[%i;%iH", 27, line + 1, column + GROSOR);
    for (i = 0; i < GROSOR - 1; i++)
    {
        printf("%c[%i;%iH", 27, line + 1 + i, column + GROSOR);
        for (j = 0; j < LONG; j++)
        {
            printf("%c[;;%im", 27, COLOR);
            printf("%c", CHAR);
        }
    }
    printf("%c[0m", 27); /*reset color*/
    fflush(stdout);
}

void bcd_b(int l, int c)
{
    int line, column, i, j;
    line = l;
    column = c;

    printf("%c[%i;%iH", 27, line + GROSOR, column + GROSOR + LONG);
    for (i = 0; i < LONG; i++)
    {
        printf("%c[%i;%iH", 27, line + GROSOR + i, column + GROSOR + LONG);
        for (j = 0; j < GROSOR; j++)
        {
            printf("%c[;;%im", 27, COLOR);
            printf("%c", CHAR);
        }
    }
    printf("%c[0m", 27);
    fflush(stdout);
}

void bcd_c(int l, int c)
{
    int line, column, i, j;
    line = l;
    column = c;

    printf("%c[%i;%iH", 27, line + 2 * GROSOR + LONG - 1, column + LONG + GROSOR);
    for (i = 0; i < LONG; i++)
    {
        printf("%c[%i;%iH", 27, line + 2 * GROSOR + LONG - 1 + i, column + LONG + GROSOR);
        for (j = 0; j < GROSOR; j++)
        {
            printf("%c[;;%im", 27, COLOR);
            printf("%c", CHAR);
        }
    }
    printf("%c[0m", 27);
    fflush(stdout);
}

void bcd_d(int l, int c)
{
    int line, column, i, j;
    line = l;
    column = c;

    printf("%c[%i;%iH", 27, line + 2 * LONG + 2 * GROSOR - 1, column + GROSOR);
    for (i = 0; i < GROSOR - 1; i++)
    {
        printf("%c[%i;%iH", 27, line + i + 2 * LONG + 2 * GROSOR - 1, column + GROSOR);
        for (j = 0; j < LONG; j++)
        {
            printf("%c[;;%im", 27, COLOR);
            printf("%c", CHAR);
        }
    }
    printf("%c[0m", 27);
    fflush(stdout);
}

void bcd_e(int l, int c)
{
    int line, column, i, j;
    line = l;
    column = c;

    printf("%c[%i;%iH", 27, line + 2 * GROSOR + LONG - 1, column);
    for (i = 0; i < LONG; i++)
    {
        printf("%c[%i;%iH", 27, line + 2 * GROSOR + LONG - 1 + i, column);
        for (j = 0; j < GROSOR; j++)
        {
            printf("%c[;;%im", 27, COLOR);
            printf("%c", CHAR);
        }
    }
    printf("%c[0m", 27);
    fflush(stdout);
}

void bcd_f(int l, int c)
{
    int line, column, i, j;
    line = l;
    column = c;

    printf("%c[%i;%iH", 27, line + GROSOR, column);
    for (i = 0; i < LONG; i++)
    {
        printf("%c[%i;%iH", 27, line + GROSOR + i, column);
        for (j = 0; j < GROSOR; j++)
        {
            printf("%c[;;%im", 27, COLOR);
            printf("%c", CHAR);
        }
    }
    printf("%c[0m", 27);
    fflush(stdout);
}

void bcd_g(int l, int c)
{
    int line, column, i, j;
    line = l;
    column = c;

    printf("%c[%i;%iH", 27, line + LONG + GROSOR, column + GROSOR);
    for (i = 0; i < GROSOR - 1; i++)
    {
        printf("%c[%i;%iH", 27, line + i + LONG + GROSOR, column + GROSOR);
        for (j = 0; j < LONG; j++)
        {
            printf("%c[;;%im", 27, COLOR);
            printf("%c", CHAR);
        }
    }
    printf("%c[0m", 27);
    fflush(stdout);
}

int bcd_display(int n, rect *r)
{

    int l, c;

    if (!r || n < 0 || n > 9)
        return -1;

    rect_clear(r); /*Prepare area*/

    l = rect_getline(r);
    c = rect_getcolumn(r);

    switch (n)
    {
    case 0:
        bcd_a(l, c);
        bcd_b(l, c);
        bcd_c(l, c);
        bcd_d(l, c);
        bcd_e(l, c);
        bcd_f(l, c);
        break;

    case 1:
        bcd_b(l, c);
        bcd_c(l, c);
        break;
    case 2:
        bcd_a(l, c);
        bcd_b(l, c);
        bcd_d(l, c);
        bcd_e(l, c);
        bcd_g(l, c);
        break;
    case 3:
        bcd_a(l, c);
        bcd_b(l, c);
        bcd_d(l, c);
        bcd_c(l, c);
        bcd_g(l, c);
        break;
    case 4:
        bcd_c(l, c);
        bcd_g(l, c);
        bcd_b(l, c);
        bcd_f(l, c);
        break;
    case 5:
        bcd_a(l, c);
        bcd_f(l, c);
        bcd_g(l, c);
        bcd_c(l, c);
        bcd_d(l, c);
        break;
    case 6:
        bcd_a(l, c);
        bcd_f(l, c);
        bcd_g(l, c);
        bcd_c(l, c);
        bcd_d(l, c);
        bcd_e(l, c);
        break;
    case 7:
        bcd_a(l, c);
        bcd_b(l, c);
        bcd_c(l, c);
        break;
    case 8:
        bcd_a(l, c);
        bcd_b(l, c);
        bcd_c(l, c);
        bcd_d(l, c);
        bcd_e(l, c);
        bcd_f(l, c);
        bcd_g(l, c);
        break;
    case 9:
        bcd_a(l, c);
        bcd_b(l, c);
        bcd_c(l, c);
        bcd_f(l, c);
        bcd_g(l, c);
        break;
    }

    return 0;
}
