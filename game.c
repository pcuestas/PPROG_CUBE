#include "menu.h"
#include "cube_interface.h"

#define SAVE_FILE "./txt_files/save_game.dat"

int main(void){
    int option=0, use_saved_game=TRUE;

    while ((option=MenusDisplay(&use_saved_game))!=0){
        c_interface(option, use_saved_game, SAVE_FILE);
    }

    return 0;
}