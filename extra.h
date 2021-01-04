#ifndef EXTRA_H
#define EXTRA_H

#include <stdio.h>
#include "bcd.h"


/**
 * @brief manages all the events when the cube is solved
 * @param dat pointer to counter_data
 * @return Ok or ERROR in case of null pointer in argument
 */
Status congratulations(counter_data *dat);


#endif