#include "solver.h"
#include <string.h>

#define MAX_MOV 10000


char *solve_cube(Cube3* c1){
    char *sol=NULL;
    Cube3 *c2=NULL;
    if(!c1){
        return NULL;
    }
    if(!(c2=c_copy(c1))){
        return NULL;
    }
    if(!(sol = (char*)calloc(MAX_MOV, sizeof(char)))){
        c_free(c2);
        return NULL;
    }
    sol[0]='\0';
    /*resolvemos la cruz*/
    solve_cross(c2,sol);




    c_free(c2);
    return sol;
}
void solve_cross(Cube3 *c, char *sol){
    short cd, cf, i, pos;
    char cross[101]="";
    Piece *p;

    cd=cfrom(c, 'D');
    
    /*solve each cross piece*/
    for(i=0;i<4;i++){
        cross[0]=0;
        cf=cfrom(c, 'F');

        /*search for the piece that goes in FD*/
        pos=c_iofCol(c, cd+cf);
        p=&(c->pc[pos]);

        /*first we put our piece in UF*/

        if(p->p[2]==-1){
        /*  it is in the D layer */
            if(p->p[1]==1){
                /*it is in DR*/
                strncat(cross, "RRU",100);
            }else if(p->p[1]==-1){
                /*it is in DL*/
                strncat(cross, "LLu",100);
            }else if(p->p[0]==1){
                /*it is in DF*/
                strncat(cross, "FF",100);
            }else{
                /*it is in DB*/
                strncat(cross, "BBUU",100);
            }
        }else if(p->p[2]==0){
            /*it is in the middle layer*/            
            if(p->p[1]==1){
                /*it is in R*/
                if(p->p[0]==1){
                    /*it is in RF*/
                    strncat(cross, "f",100);
                }else{
                    /*it is in RB*/
                    strncat(cross, "rUR",100);
                }
            }else{
                /*it is in L*/
                if(p->p[0]==1){
                    /*it is in LF*/
                    strncat(cross, "F",100);
                }else{
                    /*it is in LB*/
                    strncat(cross, "Lul",100);
                }
            }
            
        }else{
            /*it is in the top layer*/
            if(p->p[0]==1){
                /*it is in the correct spot*/
            }else if(p->p[0]==-1){
                /*it is in UB*/
                strncat(cross, "UU",100);
            }else if(p->p[1]==1){
                /*it is in UR*/
                strncat(cross, "U",100);
            }else {
                /*it is in UL*/
                strncat(cross, "u",100);
            }
        }
        c_moves(c,cross);/*make the moves*/
        
        /*now that the piece is in UF*/
        pos=c_iofPos(c, 1, 0, 1);
        p=&(c->pc[pos]);
        if(p->c[2]==cd){
            /*facing up*/
            strncat(cross, "FF",100);
            c_moves(c,"FF");
        }else{
            /*facing front*/
            strncat(cross, "urFR",100);
            c_moves(c,"urFR");

        }
        /*rotate cube to find next piece*/
        strncat(cross, "Y", 100);
        c_moves(c, "Y");
        strncat(sol, cross, 100);
    }
}