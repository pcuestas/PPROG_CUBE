/**
 * This file is only a test for the future menu of the game 
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "interface.h"

#include "menu.h"

#define UP -1
#define DOWN 1
#define ENTER 0
#define OTHER 2

/*FILES WHERE ARE THE GRAPHIC CONTENT*/
#define MAINMENU "menu.txt"
#define NEWGAMEMNU "newgame.txt"
#define ARROW "arrow.txt"

/**
 line 2-9: new game -->pos 0
 line 12-9: ...     -->pos 1
 line 22-31: ...    -->pos2

 si se hace una funcin que solo mueva la flecha va a quedar más fluido. Problema como borrar solo la flecha y no el resto del menu
 submenus!

 nueva partida
 cargar partida
 Instrucciones?

 **/


int ShowMainMenu(){
    int pos = 0;
    int letter;
    rect *r_menu, *r_arrow, *r_arrowblock;

    r_menu = rect_init(2, 29, 113, 29);
    r_arrow = rect_init(2, 4, 20, 29);
    r_arrowblock = rect_init(2, 4, 20, 30);

    printf("%c[2J", 27);

    print_element(MAINMENU, r_menu);
    print_element(ARROW, r_arrow);

    do
    {

        letter = read_keyMenu();

        if (letter == ENTER) /*Enter*/{
            rect_free(r_menu);
            rect_free(r_arrowblock);
            rect_free(r_arrow);
            return pos;
        }
        else if (letter == UP) /*Poner flecha hacia arriba*/{
            if (pos > 0){
                pos--;
            }
        }
        else if (letter == DOWN) /*Poner flecha hacia arriba*/{
            if (pos < 2){
                pos++;
            }
        }

        rect_clear(r_arrowblock);
        rect_setline(r_arrow, 13 * pos + 2);
        print_element(ARROW, r_arrow);

    } while (1);

    rect_free(r_menu);
    rect_free(r_arrowblock);
    rect_free(r_arrow);

    return 0;
}

int ShowNewGameMenu()
{
    int pos = 0;
    int letter;
    rect *r_menu, *r_arrow, *r_arrowblock;

    r_menu = rect_init(2, 29, 113, 29);
    r_arrow = rect_init(2, 4, 20, 29);
    r_arrowblock = rect_init(2, 4, 20, 30);

    printf("%c[2J", 27);

    print_element(NEWGAMEMNU, r_menu);
    print_element(ARROW, r_arrow);

    do
    {

        letter = read_keyMenu();

        if (letter == ENTER)
        {
            if (pos == 0)
            {
                /*3x3 Cube*/
                continue;
            }
            else if (pos == 1)
            {
                /*2x2 Cube*/
                continue;
            }
            else
            {
                rect_free(r_menu);
                rect_free(r_arrowblock);
                rect_free(r_arrow);
                return ShowMainMenu();
            }
            break; /*printear submenus*/
        }
        else if (letter == UP)
        {
            if (pos > 0)
            {
                pos--;
            }
        }
        else if (letter == DOWN)
        {
            if (pos < 2)
            {
                pos++;
            }
        }

        rect_clear(r_arrowblock);
        rect_setline(r_arrow, 13 * pos + 2);
        print_element(ARROW, r_arrow);

    } while (1);

    rect_free(r_menu);
    rect_free(r_arrowblock);
    rect_free(r_arrow);

    return 0;
}

int read_keyMenu()
{
    char choice;
    choice = fgetc(stdin);

    if (choice == 10)
        return ENTER;

    if (choice == 27 && fgetc(stdin) == '[')
    { /* The key is an arrow key */
        choice = fgetc(stdin);

        switch (choice)
        {
        case ('A'):
            return UP;
        case ('B'):
            return DOWN;
        default:
            return OTHER;
        }
    }
    else
        return choice;
}

void print_menu(int pos)
{

    Bool rep = FALSE;
    int c, column, line, incr = 1, posi;
    char menu[30], arrow[30];
    FILE *fp;

    posi = pos * 10 + 2;

    /*WHERE TO START PRINTING VIEW*/
    line = 2;
    column = 29;

    strcpy(menu, "menu.txt");
    strcpy(arrow, "arrow.txt");

    fp = fopen(menu, "r");
    printf("%c[2J", 27); /*Cleans the screen*/

print:
    printf("%c[%i;%iH", 27, line, column); /*Positionates the cursor to start printing */

    do
    {
        c = fgetc(fp);
        if (feof(fp))
            break;

        if (c == '\n')
        { /*new line read --> update cursor position*/
            printf("%c[%i;%iH", 27, line + incr, column);
            incr++;
            continue;
        }

        fprintf(stdout, "%c", c);

    } while (1);

    if (rep == FALSE)
    { /*update values for printing secondary view*/
        fclose(fp);
        rep = TRUE;
        incr = 1;
        fp = fopen(arrow, "r");
        column = 1;
        line = posi;
        goto print;
    }

    fclose(fp);
    return;
}
