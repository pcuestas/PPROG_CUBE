#include <stdio.h>

#include"types.h"
#include "menu.h"
#include "cube_interface.h"
#include "interface.h"
#include "SDL_interface.h"


#define SAVE_FILE "./txt_files/save_game.dat"

int main(void){
    int option=0, use_saved_game=TRUE, SDL_window=TRUE;

    while ((option=MenusDisplay(&use_saved_game, &SDL_window))!=0){
        if(SDL_window==FALSE){
            if(c_interface(option, use_saved_game, SAVE_FILE)==ERROR){
                printf("ERROR in c_interface()");
                return -1;
            }
        }
        else
            SDL_interface(option, use_saved_game, SAVE_FILE);
    }

    terminal_clear();
    positionate_cursor(1,1);
    return 0;
}