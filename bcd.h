#ifndef BCD_H
#define BCD_H

#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

void bcd_a(int line, int column);

void bcd_b(int line, int column);
void bcd_c(int line, int column);

void bcd_d(int line, int column);
void bcd_e(int line, int column);
void bcd_f(int line, int column);
void bcd_g(int line, int column);

int bcd_display(int n, rect *r);


/**
* @brief implements a counter to be used in a thread.
* 
**/
void *counter(void*a);

#endif