#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#include "menu.h"

struct termios initial;

#define MAX_CAD 100

/*
  Initializes the terminal in such a way that we can read the input
  without echo on the screen
*/
void _term_init()
{
  struct termios new; /*a termios structure contains a set of attributes about 
					  how the terminal scans and outputs data*/

  tcgetattr(fileno(stdin), &initial); /*first we get the current settings of out 
						 terminal (fileno returns the file descriptor 
						 of stdin) and save them in initial. We'd better 
						 restore them later on*/
  new = initial;                      /*then we copy them into another one, as we aren't going 
						to change ALL the values. We'll keep the rest the same */
  new.c_lflag &= ~ICANON;             /*here we are setting up new. This line tells to stop the 
						canonical mode (which means waiting for the user to press 
						enter before sending)*/
  new.c_lflag &= ~ECHO;               /*by deactivating echo, we tell the terminal NOT TO 
						show the characters the user is pressing*/
  new.c_cc[VMIN] = 1;                 /*this states the minimum number of characters we have 
					       to receive before sending is 1 (it means we won't wait 
					       for the user to press 2,3... letters)*/
  new.c_cc[VTIME] = 0;                /*I really have no clue what this does, it must be somewhere in the book tho*/
  new.c_lflag &= ~ISIG;               /*here we discard signals: the program won't end even if we 
						press Ctrl+C or we tell it to finish*/

  tcsetattr(fileno(stdin), TCSANOW, &new); /*now we SET the attributes stored in new to the 
						    terminal. TCSANOW tells the program not to wait 
						    before making this change*/
}

/*
 * si se escribe cualquier letra que corresponda a un movimiento, se realizara en el cubo en pantalla
 * si se presiona 'w'. se mezclará el cubo con una mezcla aleatoria elegida de entre las mezclas del fichero SCRAMBLES_TXT
 * si se presiona 'q', se terminará el programa.
*/
int main(void)
{ 

  int ret;

  _term_init(); /*modifica los parámetros de la terminal para poder leer las letras sin que se presione enter*/

  /*ret=MenusDisplay();*/

  tcsetattr(fileno(stdin), TCSANOW, &initial); /*deshace los cambios hechos por _term_init()*/

  return 0;
}
