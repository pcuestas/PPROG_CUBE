/**
 * This file is only a test for the future menu of the game 
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include "terminal_funct.h"
#include "types.h"
#include "interface.h"

#include "menu.h"

#define UP -1
#define DOWN 1
#define ENTER 0
#define OTHER 2

/*FILES WHERE ARE THE GRAPHIC CONTENT*/
#define MAIN_MENU "./txt_files/menu.txt"
#define NEW_GAME_MENU "./txt_files/newgame.txt"
#define ARROW "./txt_files/arrow.txt"

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

int MenusDisplay(int *use_saved_game){
    int choice1 = 0, choice2 = 0, ret=0;

    /*modifica los parámetros de la terminal para poder leer las letras sin que se presione enter*/
    _term_init();


MainMenu_choice:
    choice1 = ShowMainMenu();

    switch (choice1)
    {
    case 0:
        /*NEW GAME*/
        (*use_saved_game)=FALSE;
        choice2 = ShowNewGameMenu();
        goto Newgame_choice;
        break;
    case 1:
        /*LAST GAME*/
        (*use_saved_game)=TRUE;
        ret=2;/*da igual*/
        goto End_MenusDisplay;
        break;

    case 2:
        ret=0;
        goto End_MenusDisplay;
        break;
    }

Newgame_choice:
    switch (choice2)
    {
    case 0:
        /*EMPEZAR JUEGO CON 3x3*/
        printf("3x3\n");
        ret=3;
        break;
    case 1:
        /*EMPEZAR JUEGO CON 2x2*/
        printf("2x2\n");
        ret=2;
        break;

    case 2:
        goto MainMenu_choice;
        break;
    }

End_MenusDisplay:
    /*deshace los cambios hechos por _term_init()*/
    tcsetattr(fileno(stdin), TCSANOW, &initial); 

    return ret;
}

int ShowMainMenu()
{
    int pos = 0;
    int letter;
    rect *r_menu, *r_arrow, *r_arrowblock;

    r_menu = rect_init(2, 29, 113, 29);
    r_arrow = rect_init(2, 4, 20, 29);
    r_arrowblock = rect_init(2, 4, 20, 30);

    printf("%c[2J", 27);

    print_element(MAIN_MENU, r_menu);
    print_element(ARROW, r_arrow);

    do
    {

        letter = read_keyMenu();

        if (letter == ENTER) /*Enter*/
        {

            rect_free(r_menu);
            rect_free(r_arrowblock);
            rect_free(r_arrow);
            return pos;
        }
        else if (letter == UP) /*Poner flecha hacia arriba*/
        {
            if (pos > 0)
            {
                pos--;
            }
        }
        else if (letter == DOWN) /*Poner flecha hacia arriba*/
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

    print_element(NEW_GAME_MENU, r_menu);
    print_element(ARROW, r_arrow);

    do
    {

        letter = read_keyMenu();

        if (letter == ENTER)
        {

            rect_free(r_menu);
            rect_free(r_arrowblock);
            rect_free(r_arrow);
            return pos;
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
    char menu[30]=MAIN_MENU, arrow[30]=ARROW;
    FILE *fp;

    posi = pos * 10 + 2;

    /*WHERE TO START PRINTING VIEW*/
    line = 2;
    column = 29;

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
