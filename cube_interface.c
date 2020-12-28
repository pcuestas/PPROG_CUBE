#include "cube_interface.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <termios.h>

#include "terminal_funct.h"
#include "cube.h"
#include "solver.h"
#include "print_c.h"
#include "interface.h"
#include "bcd.h"
#include "utils.h"

#define MAX_CAD 100

#ifndef SCRAMBLES_TXT
#define SCRAMBLES_TXT "./txt_files/scrambles.txt"
#endif

/*
 * si se escribe cualquier letra que corresponda a un movimiento, se realizara en el cubo en pantalla
 * si se presiona 'w'. se mezclará el cubo con una mezcla aleatoria elegida de entre las mezclas del fichero SRAMBLES_TXT
 * si se presiona 'q', se terminará el programa.
*/

extern int fileno(FILE *);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *hilo(void *dat)
{ /*same function as counter in bcd.c but using locks in crucial parts (painting with ANSI ESC and moving the cursor*/
    rect **r;
    counter_data *d;
    int blank = 0, stop = 0;

    if (dat == NULL)
        return NULL;

    d = (counter_data *)dat;

    r = d->rcounter;

    while (1)
    {

        while (d->mode == 0)
        { /*Print time 0*/
            stop = 0;
            if (blank == 0)
            {
                pthread_mutex_lock(&mutex);
                bcd_display(0, r[3]);
                bcd_display(0, r[2]);
                bcd_display(0, r[1]);
                bcd_display(0, r[0]);
                fflush(stdout);
                pthread_mutex_unlock(&mutex);
                blank = 1;
            }
        }

        while (d->mode == -1)
        { /*Counter stopped*/
            blank = 0;
            if (stop == 0)
            {
                pthread_mutex_lock(&mutex);
                bcd_display(d->sec % 10, r[3]);
                bcd_display(d->sec / 10, r[2]);
                bcd_display(d->min % 10, r[1]);
                bcd_display(d->min / 10, r[0]);
                fflush(stdout);
                pthread_mutex_unlock(&mutex);
                stop = 1;
            }
        }

        while (d->mode == 1) /*Counter running*/
        {
            stop = 0;
            blank = 0;
            pthread_mutex_lock(&mutex);
            bcd_display(d->min % 10, r[1]);
            bcd_display(d->min / 10, r[0]);
            bcd_display(d->sec % 10, r[3]);
            bcd_display(d->sec / 10, r[2]);
            fflush(stdout);
            pthread_mutex_unlock(&mutex);
            d->sec++;

            if (d->sec == 60)
            {
                pthread_mutex_lock(&mutex);
                bcd_display(d->min % 10, r[1]);
                bcd_display(d->min / 10, r[0]);
                fflush(stdout);
                pthread_mutex_unlock(&mutex);
                d->min += 1;
                d->sec = 0;
            }
            if (d->min == 60)
            {
                d->min = 0;
            }
            sleep(1);
        }
    }

    return 0;
}

int c_interface(int option, int use_saved_game, char *save_game_file)
{
    Cube3 *c = NULL;
    char cad[MAX_CAD], letter, *solution = NULL;
    short flag = 0;
    char scramblefile[MAX_CAD] = SCRAMBLES_TXT, scramble[MAX_LINE];
    int letters_per_line = 11, size;
    char *cube_file=NULL;
    char *letters = "RUFLBDMESXYZruflbdmesxyz",**l_buff=NULL;

    cprint_from_stickers3 pcube = c_print4;
    rect *rvista1=NULL, *rcrono=NULL, *rborder1=NULL, *rsol=NULL,*rsol_border=NULL;
    pthread_t pth;
    counter_data *dat = NULL;
    int stop = 0, firstmove = 0;

    _term_init(); /*modifica los parámetros de la terminal para poder leer las letras sin que se presione enter*/

    if (!(dat = counter_data_init())){
        return -1;
    }

    if((l_buff=allocate_array_lettersbuffer(34))==NULL){
        flag=1;
        goto free;
    }

    fill_buffer_letter(letters,l_buff);

    /*Read the files and fill in the buffers*/
    if (option == 3){
        size = ftobuffer(CUBE_3, &cube_file);
        if (size == -1){
            flag=1;
            goto free;
        }
            
    }
    else{
        size = ftobuffer(CUBE_222, &cube_file);
        if (size == -1){
            flag=1;
            goto free;
        }
    }

    /*Initialize rectangles for all the elements of the interface*/
    counter_data_set_rects(dat, 15+2, 15+198, 15, 17);
    rvista1 = rect_init(15+3, 15+7, 180, 78);
    rcrono = rect_init(15+1, 15+192, 17 * 5+3, 19);
    rborder1 = rect_expand(rvista1, 3, 2);
    rsol = rect_init(15+24, 15+194, 88, 57); /*8 letters per line, 10 lines --> 80 letters */
    rsol_border=rect_expand(rsol,2,2);

    if(!rvista1||!rcrono||!rborder1||!rsol){
        flag=1;
        goto free;
    }

    srand(time(NULL));

    c = c_init(option);
    if (!c)
        return ERROR;

    if (use_saved_game == TRUE)
        if (read_saved_cube(c, save_game_file) == ERROR){
            flag=1;
            goto free;
        }


    terminal_clear();
    rect_border(rborder1);
    rect_border(rcrono);
    rect_border(rsol_border);

    if (refresh_cube3(c, rvista1, cube_file, size, pcube) == ERROR){
        flag = 1;
        goto free;
    }

    pthread_create(&pth, NULL, hilo, dat); /*Call the counter. It has been initialized in mode 0 (stopped and time=0)*/
    
    while (TRUE){
        letter = fgetc(stdin);

        if (letter == 'q'){
            pthread_mutex_lock(&mutex);
            counter_data_set_mode(dat, 1);
            pthread_mutex_unlock(&mutex);

            break;
        }
        else if (letter == 'w'){
            if (scramble_cube(c, scramblefile, scramble) == ERROR){
                flag = 1;
                break;
            }
            pthread_mutex_lock(&mutex);
            print_solution_2(scramble, rsol, l_buff, letters_per_line);
            counter_data_set_time(dat, 0, 0);
            counter_data_set_mode(dat, 0);
            pthread_mutex_unlock(&mutex);
            firstmove = 0;
        }

        else if (letter == 'W'){
            solution = solve_cube(c);
            pthread_mutex_lock(&mutex);
            print_solution_2(solution, rsol, l_buff, letters_per_line);
            pthread_mutex_unlock(&mutex);
            c_moves(c, solution);
            free(solution);
        }

        else if (letter == 'A'){
            solution = solve_cube(c);
            pthread_mutex_lock(&mutex);
            print_solution_2(solution, rsol, l_buff, letters_per_line);
            pthread_mutex_unlock(&mutex);
            free(solution);
            continue;
        }

        else if (letter == 'a'){
            solution = solve_cube(c);
            pthread_mutex_lock(&mutex);
            print_solution_2(solution, rsol,l_buff, letters_per_line);
            pthread_mutex_unlock(&mutex);
            slow_moves2(c, pcube, solution, 450000, rvista1, cube_file, size); /*4th arg is microseconds between moves*/
            free(solution);
            firstmove = 0;
            continue;
        }

        else if (letter == 'o'){
            terminal_clear();
            rect_border(rborder1);
            rect_border(rcrono);
        }
        else if (letter == 32){ /*stop crono*/
            if (stop == 0){ /*counter was running*/
                pthread_mutex_lock(&mutex);
                counter_data_set_mode(dat, -1);
                counter_data_set_time(dat,0,0);
                pthread_mutex_unlock(&mutex);
                stop = 1;
                continue;
            }
            else{
                pthread_mutex_lock(&mutex);
                counter_data_set_mode(dat, 1);
                pthread_mutex_unlock(&mutex);
                stop = 0;
                continue;
            }
        }
        else{
            cad[0] = letter;
            cad[1] = '\0';
            if (c_moves(c, cad) == ERROR){
                flag = 1;
                break;
            }

            if (firstmove == 0){
                pthread_mutex_lock(&mutex);
                counter_data_set_mode(dat, 1);
                pthread_mutex_unlock(&mutex);
                firstmove = 1;
            }
        }
        pthread_mutex_lock(&mutex);
        if (refresh_cube3(c, rvista1, cube_file, size, pcube) == ERROR){
            flag = 1;
            break;
        }
        pthread_mutex_unlock(&mutex);
    }


    if (save_cube(c, save_game_file) == ERROR)
        printf("There was an error when saving the game.\n");

    

    pthread_mutex_lock(&mutex);
    pthread_detach(pth);
    pthread_cancel(pth);
    pthread_mutex_unlock(&mutex);
  
    dat = NULL;

    free:

    tcsetattr(fileno(stdin), TCSANOW, &initial); /*deshace los cambios hechos por _term_init()*/
    
    if(l_buff!=NULL)
        free_array_lettersbuffer(l_buff,34);
    
    if(dat!=NULL)
        counter_data_free(dat);

    if(rvista1!=NULL)
        rect_free(rvista1);
    if (rcrono != NULL)
        rect_free(rcrono);
    if (rborder1 != NULL)
        rect_free(rborder1);
    if (rsol != NULL)
        rect_free(rsol);
    if(rsol_border!=NULL)
        rect_free(rsol_border);
    if(c!=NULL)
        c_free(c);
    
    if(cube_file!=NULL)
        free(cube_file);

    /*in case the loop gets any error*/
    if (flag == 1)
        return ERROR;

    return OK;
}
