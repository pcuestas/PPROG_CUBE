#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#include "menu.h"

#define UP -1
#define DOWN 1
#define ENTER 0;

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
    int pos=0;
    int letter;

    char buf[16];

    /*imprimir menu principal*/
    /*imprimir flecha pos(0)*/
    
    print_menu(pos);

    do{

        letter=read_key();

        if (letter == -1) /*Poner flecha hacia arriba*/{
            if(pos>0){
                pos--;
                /*Mover flecha a pos*/
                print_menu(pos);
            }
                
        }
        
        if(letter==1) /*Poner flecha hacia arriba*/{
            if (pos<2){
                pos++;
                /*Mocer flecha a pos*/
                print_menu(pos);
            }
            
        }

        if(letter==0) /*Enter*/{
            break; /*printear submenus*/
        }


    }while(1);


    return 0;
}

int read_keyMenu()
{
    char choice;
    choice = fgetc(stdin);

    if (choice == 27 && fgetc(stdin) == '[')
    { /* The key is an arrow key */
        choice = fgetc(stdin);

        switch (choice)
        {
        case ('A'):
            return UP;
        case ('B'):
            return DOWN;
        case ('C'):
            return ENTER; /* la c hay que cambiarla por el codifo correspondiente a enter !!!!!*/
        default:
            return 0;
        }
    }
    else
        return choice;
}

void print_menu(int pos){

    Bool flag = FALSE, rep = FALSE;
    int c,column, line, incr = 1,posi;
    char menu[30], arrow[30];
    FILE *fp;

    posi=pos*10+2;

    /*WHERE TO START PRINTING 1st VIEW*/
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