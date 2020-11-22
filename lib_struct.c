#ifndef _LIB_STRUCTS_
#define _LIB_STRUCTS_

#include "lib_funct.h"

sCube *sCube_init(){
    sCube *sc=NULL;

    if((sc=(sCube*)calloc(1, sizeof(sCube)))==NULL)
        return NULL;

    /*declaration of the whole cube: */
    sc->pc[0].st[0].num = 29;
    sc->pc[0].st[1].num = 36;
    sc->pc[0].st[2].num =  0;

    return sc;
}

#endif