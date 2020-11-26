#ifndef _CUBE_INTERFACE_H_
#define _CUBE_INTERFACE_H_


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

/*calls the cube interface with the option (2 or 3)*/
int c_interface(int option);

#endif