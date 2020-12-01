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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void*hilo(void*dat){ /*same function as counter in bcd.c but using locks in crucial parts (painting with ANSI ESC and moving the cursor*/
    rect **r;
    counter_data *d;
    int blank = 0, stop = 0;

    d = (counter_data *)dat;

    r = d->rcounter;

    while (1){

        while (d->mode == 0){ /*Print time 0*/
        stop=0;
            if (blank == 0){
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

        while (d->mode == -1){ /*Counter stopped*/
        blank=0;
            if (stop == 0){
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

        while (d->mode == 1) /*Counter running*/{
            stop=0;
            blank=0;
            pthread_mutex_lock(&mutex);
            bcd_display(d->min % 10, r[1]);
            bcd_display(d->min / 10, r[0]);
            bcd_display(d->sec % 10, r[3]);
            bcd_display(d->sec / 10, r[2]);
            fflush(stdout);
            pthread_mutex_unlock(&mutex);
            d->sec++;

            if (d->sec == 60){
                pthread_mutex_lock(&mutex);
                bcd_display(d->min % 10, r[1]);
                bcd_display(d->min / 10, r[0]);
                fflush(stdout);
                pthread_mutex_unlock(&mutex);
                d->min += 1;
                d->sec = 0;
            }
            if (d->min == 60){
                d->min = 0;
            }
            sleep(1);
        }
    }

    return 0;
}

int c_interface(int option, int use_saved_game, char *save_game_file){
    Cube3 *c = NULL;
    char cad[MAX_CAD], letter, *solution = NULL;
    short flag=0;
    char scramblefile[MAX_CAD]=SCRAMBLES_TXT;

    cprint_from_stickers2 pcube=c_print3;
    rect *rvista1,*rcrono,*rborder1;
    pthread_t pth;
    counter_data *dat;
    int stop = 0,firstmove=0;


    if (!(dat = counter_data_init(dat)))
        return -1;

    counter_data_set_rects(dat, 4, 12, 15, 17);
    rvista1 = rect_init(25, 7, 177, 76);
    rcrono=rect_init(2,8,17*5,19);
    rborder1=rect_expand(rvista1,2,2);

    srand(time(NULL));

    c = c_init(option);
    if (!c)
        return ERROR;
    
    if (use_saved_game==TRUE)
        if (read_saved_cube(c, save_game_file)==ERROR){
            c_free(c);
            rect_free(rvista1);
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
    rect_border(rborder1);
    rect_border(rcrono);

    if (refresh_cube2(c, rvista1, NULL, pcube) == ERROR){
        c_free(c);
        rect_free(rvista1);
        tcsetattr(fileno(stdin), TCSANOW, &initial);/*deshace los cambios hechos por _term_init()*/
        return ERROR;
    }

    pthread_create(&pth,NULL,hilo,dat); /*Call the counter. It has been initialized in mode 0 (stopped and time=0)*/
    
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
            pthread_mutex_lock(&mutex);
            counter_data_set_time(dat, 0, 0); 
            counter_data_set_mode(dat,0);
            pthread_mutex_unlock(&mutex);
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
            slow_moves(c, pcube, solution, 450000, rvista1, NULL); /*4th arg is miocroseconds between moves*/
            free(solution);
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
                pthread_mutex_unlock(&mutex);
                stop = 1;
                continue;
            }else{
                pthread_mutex_lock(&mutex);
                counter_data_set_mode(dat, 1);
                pthread_mutex_unlock(&mutex);
                stop = 0;
                continue;
            }
        }else{
            cad[0]=letter;
            cad[1]='\0';
            if (c_moves(c, cad) == ERROR){
                flag = 1;
                break;
            }

            if(firstmove==0){
                pthread_mutex_lock(&mutex);
                counter_data_set_mode(dat,1);
                pthread_mutex_unlock(&mutex);
                firstmove=1;
            }

        }
        pthread_mutex_lock(&mutex);
        if (refresh_cube2(c, rvista1, NULL, pcube) == ERROR){
            flag = 1;
            break;
        }
        pthread_mutex_unlock(&mutex);
        }

    rect_free(rvista1);
    rect_free(rcrono);
    rect_free(rborder1);

    tcsetattr(fileno(stdin), TCSANOW, &initial);/*deshace los cambios hechos por _term_init()*/


    if(save_cube(c, save_game_file)==ERROR)
        printf("There was an error when saving the game.\n");

    pthread_detach(pth);
    pthread_cancel(pth);
    c_free(c);
    counter_data_free(dat);

    /*in case the loop gets any error*/
    if (flag == 1)
        return ERROR;

    return OK;
}
