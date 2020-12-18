/**
 * @file ftobuff.h
 * @author Pablo Cuesta Sierra
 * @brief functions to read files of the project to buffers
 *        to avoid constant file reading
 */

#ifndef _FILE_TO_BUFF_
#define _FILE_TO_BUFF_


#include <string.h>
#include <stdio.h>

#define MAX_BUF (15000)



/**
 * @brief This function reads the whole file with name 
 * in string file and stores it in a new char with size
 * just equal to the size of the data in the file. The
 * string will have a '\0' at the end. This function
 * allocates memory for the new string.
 * The maximum size to be read is MAX_BUF
*/
char *ftobuffer(char*file);

#endif