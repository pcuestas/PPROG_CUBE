#include "cube_interface.h"

#define MAX_CAD 100

#ifndef SCRAMBLES_TXT
#define SCRAMBLES_TXT "./txt_files/scrambles.txt"
#endif


/*
 * si se escribe cualquier letra que corresponda a un movimiento, se realizara en el cubo en pantalla
 * si se presiona 'w'. se mezclará el cubo con una mezcla aleatoria elegida de entre las mezclas del fichero SRAMBLES_TXT
 * si se presiona 'q', se terminará el programa.
*/
int c_interface(int option, int use_saved_game, char *save_game_file){
    Cube3 *c = NULL;
    char cad[MAX_CAD], letter, *solution = NULL;
    short flag=0;
    char scramblefile[MAX_CAD]=SCRAMBLES_TXT;

    cprint_from_stickers2 pcube=c_print3;
    rect *rvista1, *rvista2;
    pthread_t pth;
    counter_data *dat;
    int stop = 0,firstmove=0;

    rvista1 = rect_init(25, 2, 177, 76);
    /*rvista2 = rect_init(32, 120, 40, 40);*/

    if (!(dat = counter_data_init(dat)))
        return -1;

    counter_data_set_rects(dat, 2, 2, 15, 17);

    srand(time(NULL));

    c = c_init();
    if (!c)
        return ERROR;
    
    if (use_saved_game==TRUE)
        if (read_saved_cube(c, save_game_file, &option)==ERROR){
            c_free(c);
            rect_free(rvista1);
            rect_free(rvista2);
            return ERROR;
        }

    switch(option){/*when 2x2 file is ready*/
        case 2:
            break;
        case 3:
            break;
        default:
            break;
    }

    _term_init();/*modifica los parámetros de la terminal para poder leer las letras sin que se presione enter*/

    terminal_clear();

    if (refresh_cube2(c,rvista1,rvista2,pcube) == ERROR){
        c_free(c);
        rect_free(rvista1);
        rect_free(rvista2);
        tcsetattr(fileno(stdin), TCSANOW, &initial);/*deshace los cambios hechos por _term_init()*/
        return ERROR;
    }

    pthread_create(&pth,NULL,counter,dat);
    
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
            counter_data_set_time(dat, 0, 0);
            counter_data_set_mode(dat,0);
            firstmove=0;
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
        
        else if (letter == 'o')
        {
            terminal_clear();
            /*PINTAR BORDES OTRA VEZ*/
        }
        else if (letter == 32){ /*stop crono*/
            if (stop == 0){ /*counter was running*/
               counter_data_set_mode(dat,-1);
               stop = 1;
            }else{
                counter_data_set_mode(dat, 1);
                stop = 0;
            }
        }else{
            cad[0]=letter;
            cad[1]='\0';
            if (c_moves(c, cad) == ERROR){
                flag = 1;
                break;
            }

            if(firstmove==0){
                counter_data_set_mode(dat,1);
                terminal_clear();
                firstmove=1;
            }

        }

        if (refresh_cube2(c, rvista1, rvista2, pcube) == ERROR)
        {
            flag = 1;
            break;
        }
        }

    rect_free(rvista1);

    tcsetattr(fileno(stdin), TCSANOW, &initial);/*deshace los cambios hechos por _term_init()*/

    /*in case the loop gets any error*/
    if (flag == 1)
        return ERROR;

    if(save_cube(c, save_game_file, &option)==ERROR)
        printf("There was an error when saving the game.\n");

    pthread_cancel(pth);
    c_free(c);
    counter_data_free(dat);

    return OK;
}
