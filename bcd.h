#ifndef BCD_H
#define BCD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "interface.h"

typedef struct _counter_data counter_data;


/**
 * @brief Allocates a new counter_data structure
 * @return Pointer to counter_data or NULL 
 */
counter_data* counter_data_init();

/**
 * @brief Frees the counter_data strcuture
 */
void counter_data_free(counter_data *dat);

Status counter_data_set_time(counter_data* dat,int min, int sec);
Status counter_data_set_mode(counter_data* dat, int mode);

/**
 * @brief Stablish the data of each rectangle of the struct. Should be called with l=15,h=17
 */
Status counter_data_set_rects(counter_data* dat,int line, int column,int l,int h);
rect **counter_data_get_rect(counter_data* dat);
int counter_data_get_min(counter_data*dat);
int counter_data_get_sec(counter_data *dat);
int counter_data_get_mode(counter_data *dat);

/**Prints the segmenst of a bcd. Arguments line and column define the upper left corner**/
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
* @param a Pointer to a structure of type counter_data_set_time
* 
**/
void *counter(void*a);

#endif