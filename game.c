#include "menu.h"
#include "cube_interface.h"

int main(void){
    int option=0;

    while ((option=MenusDisplay())!=0){
        c_interface(option);
    }

    return 0;
}