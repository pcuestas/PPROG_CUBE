#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cube.h"
#include "print_c.h"

#define MAX_CAD 100

int main(void)
{
    Cube3 *c = NULL;
    short s[54];
    char cad[MAX_CAD];
    short flag=0;

    c = c_init();
    if (!c)
        return 1;

    if (colour_stickers(c, s) == ERROR)
    {
        c_free(c);
        return 1;
    }
    c_print(stdout, s);

    while (TRUE)
    {
        fscanf(stdin, "%s", cad);
        /*command to quit the game*/
        if (strcmp(cad,"q")==0)
        {
            break;
        }

        if (c_moves(c, cad) == ERROR)
        {
            flag = 1;
            break;
        }
        if (colour_stickers(c, s) == ERROR)
        {
            flag = 1;
            break;
        }
        c_print(stdout, s);
    }

    c_free(c);

    /*in case the loop gets any error*/
    if (flag == 1)
        return -1;

    return 0;
}
