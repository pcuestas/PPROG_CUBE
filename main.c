/*first attempt to check cube.h*/

#include <stdio.h>
#include <stdlib.h>
#include "ftobuff.h"

#define MAX_BUF (15000)
#define CUBE__3 "./txt_files/cubo3.txt"

#define _TEST_ "test.txt"

int main(void) {
    char *new=NULL;

    printf("Size of new1:%d\n", (int)sizeof(new));

    new=ftobuffer(_TEST_);

    if(!new){
        printf("err in ftobuffer");
        return -1;
    }

    printf("Size of new2:%d\n", (int)sizeof(new));

    printf("string:|%s|\n", new);

    free(new);
    return 0;
}