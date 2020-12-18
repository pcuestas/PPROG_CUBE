/**
 * @file ftobuff.c
 * @author Pablo Cuesta Sierra
 * @brief functions to read files of the project to buffers
 *        to avoid constant file reading
 */

#include "ftobuff.h"

extern char *strndup(const char *, size_t );

/**
 * @brief This function reads the whole file with name 
 * in string file and stores it in a new char with size
 * just equal to the size of the data in the file. The
 * string will have a '\0' at the end. This function
 * allocates memory for the new string.
 * The maximum size to be read is MAX_BUF
*/
char *ftobuffer(char*file){
    FILE* pfrom=NULL;
    char buf[MAX_BUF], *new=NULL;
    int count;

    if(file==NULL)
        return NULL;

    if(!(pfrom=fopen(file, "r"))){
        printf("Could not open %s\n", file);
        return NULL;
    }
    count=fread(buf, sizeof(char), MAX_BUF, pfrom);
    
    new=strndup(buf, count);

    fclose(pfrom);
    return new;
}