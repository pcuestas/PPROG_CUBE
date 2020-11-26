#include "cube_interface.h"

#define MAX_CAD 100



/*
 * si se escribe cualquier letra que corresponda a un movimiento, se realizara en el cubo en pantalla
 * si se presiona 'w'. se mezclará el cubo con una mezcla aleatoria elegida de entre las mezclas del fichero "scrambles.txt"
 * si se presiona 'q', se terminará el programa.
*/
int c_interface(int option, int new){
    Cube3 *c = NULL;
    char cad[MAX_CAD], letter, *solution = NULL;
    short flag=0;
    char scramblefile[MAX_CAD]="scrambles.txt";
    cprint_from_stickers printcube = c_print2; /* This is the only place in the routine where 
                                               * the function that prints the cube must be changed*/

    cprint_from_stickers2 pcube=c_print3;
    rect *rvista1, *rvista2;
    pthread_t pth;

    rvista1 = rect_init(2, 2, 100, 70);
    rvista2 = rect_init(32, 120, 40, 40);

    srand(time(NULL));

    c = c_init();
    if (!c)
        return 1;

    _term_init();/*modifica los parámetros de la terminal para poder leer las letras sin que se presione enter*/

    terminal_clear();

    if (refresh_cube2(c,rvista1,rvista2,pcube) == ERROR){
        c_free(c);
        tcsetattr(fileno(stdin), TCSANOW, &initial);/*deshace los cambios hechos por _term_init()*/
        return 1;
    }

    pthread_create(&pth, NULL, counter, NULL);

    
    while (TRUE){
        letter=fgetc(stdin);

        if (letter=='q'){
            break;
        }
        else if(letter=='w'){
            if(scramble_cube(c, scramblefile) == ERROR){
                flag = 1;
                break;
            }
        }
        else if(letter=='W'){
            solution = solve_cube(c);
            c_moves(c, solution);
            free(solution);
        }
        else if(letter=='A'){
            solution = solve_cube(c);
            printf("%s", solution);
            free(solution);
            continue;
        }
        else if(letter=='a'){
            solution = solve_cube(c);
            slow_moves(c, pcube, solution, 150000000,rvista1,rvista2);
            free(solution);
            continue;
        }
        else if(letter==' '){/*DEL: this is just for trials--solver.c*/
            solve_permcorners(c, cad);
            printf("%s\n", cad);
            cad[0]=0;
            continue;
        }
        else{
            cad[0]=letter;
            cad[1]='\0';
            if (c_moves(c, cad) == ERROR){
                flag = 1;
                break;
            }
        }

        if (refresh_cube2(c, rvista1, rvista2, pcube) == ERROR)
        {
            flag = 1;
            break;
        }
    }

    c_free(c);
    rect_free(rvista1);
    rect_free(rvista2);

    tcsetattr(fileno(stdin), TCSANOW, &initial);/*deshace los cambios hechos por _term_init()*/

    /*in case the loop gets any error*/
    if (flag == 1)
        return -1;

    return 0;
}
