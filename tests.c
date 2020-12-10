/*testing binary files game saving*/

#include "menu.h"
#include "cube_interface.h"
#include "interface.h"

#ifndef SAVE_FILE
#define SAVE_FILE "./txt_files/save_game.dat"
#endif

int main(void){
    int option=0, r1=0, r2=0;
    Piece p, q;

    p.p[0]=7;
    p.p[1]=1;
    p.p[2]=2;
    
    p.c[0]=3;
    p.c[1]=4;
    p.c[2]=12;

    r1=save_cube(&p, SAVE_FILE);

    r2=read_saved_cube(&q, SAVE_FILE);

    printf("\n%d, %d\n", r1, r2);

    p_print(stdout, &q);

    return 0;
}