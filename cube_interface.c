#include <string.h>
#include "cube.h"
#include "print_c.h"

int main(void)
{
    Cube3 *c = NULL;
    short s[54];
    int i;
    char *cad = NULL;
    short flag;

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
        if (fscanf(stdin, "%s", cad) != 1)
        {
            flag = 1;
            break;
        }
        /*command to quit the game*/
        if (cad == "q")
        {
            free(cad);
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
        free(cad);
    }

    c_free(c);

    /*in case the loop gets any error*/
    if (flag == 1)
        return -1;

    return 0;
}
