#include "solver.h"
#include <string.h>

#define MAX_MOV 10000


char opposite_move(char c){
    if(c>='a' && c<='z'){
        return (c-'a'+'A');
    }else if(c>='A' && c<='Z'){
        return (c-'A'+'a');
    }else{
        return -1;
    }
}


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

    /*resolver las esquinas inferiores*/
    solve_d_corners(c2, sol);

    /*solve the second layer*/
    solve_finishF2L(c2, sol);
    
    /*solve the top cross*/
    solve_topcross(c2, sol);
    
    c_free(c2);
    clean_moves(sol);
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
        if(i<3){
            /*rotate cube to find next piece*/
            strncat(cross, "Y", 100);
            c_moves(c, "Y");
        }
        strncat(sol, cross, 100);
    }
}

void solve_d_corners(Cube3* c, char *sol){
    short cd, cf, cr, i, pos;
    char cor[101]="";
    Piece *p;

    cd=cfrom(c, 'D');
    
    /*solve each cross piece*/
    for(i=0;i<4;i++){
        cor[0]=0;
        cf=cfrom(c, 'F');
        cr=cfrom(c, 'R');

        /*search for the piece that goes in FD*/
        pos=c_iofCol(c, cd+cf+cr);
        p=&(c->pc[pos]);

        /*first we put our piece in URF*/

        if(p->p[2]==-1){
        /*  it is in the D layer */
            if(p->p[1]==1){
                /*it is in DRx */
                if(p->p[0]==1){
                    /*DRF*/
                    strncat(cor, "Rur", 100);
                }else{
                    /*DRB*/
                    strncat(cor, "rURU", 100);
                }
            }else{
                /*it is in DLx */
                if(p->p[0]==1){
                    /*DLF */
                    strncat(cor, "luL",100);
                }else{
                    /*DLB*/
                    strncat(cor, "Luul",100);
                }
            }
        }else{
        /*  it is in the U layer */
            if(p->p[1]==1){
                /*it is in URx */
                if(p->p[0]==1){
                    /*URF --  nothing to be done*/
                }else{
                    /*URB*/
                    strncat(cor, "U", 100);
                }
            }else{
                /*it is in ULx */
                if(p->p[0]==1){
                    /*ULF */
                    strncat(cor, "u",100);
                }else{
                    /*ULB*/
                    strncat(cor, "UU",100);
                }
            }
        }
        c_moves(c,cor);/*make the moves*/
        
        /*now that the piece is in URF*/
        pos=c_iofPos(c, 1, 1, 1);
        p=&(c->pc[pos]);
        if(p->c[2]==cd){
            /*facing up*/
            strncat(cor, "RuuruRUr",100);
            c_moves(c,"RuuruRUr");
        }else if(p->c[1]==cd){
            /*facing left*/
            strncat(cor, "RUr",100);
            c_moves(c,"RUr");
        }else {
            /*facing front*/
            strncat(cor, "URur",100);
            c_moves(c,"URur");
        }
        if(i<3){
            /*rotate cube to find next piece*/
            strncat(cor, "Y", 100);
            c_moves(c, "Y");
        }
        strncat(sol, cor, 100);
    }
}

void solve_finishF2L(Cube3*c, char *sol){
    short cf, cr, i, pos;
    char cor[101]="";
    Piece *p;
    
    /*solve each second layer piece*/
    for(i=0;i<4;i++){
        cor[0]=0;
        cf=cfrom(c, 'F');
        cr=cfrom(c, 'R');

        /*search for the piece that goes in FD*/
        pos=c_iofCol(c, cf+cr);
        p=&(c->pc[pos]);

        /*first we put our piece in UF*/

        if(p->p[2]==0){
        /*  it is in the middle layer */
            if(p->p[1]==1){
                /*it is in R */
                if(p->p[0]==1){
                    /*RF*/
                    if(p->c[0]==cf){
                        /*solved*/
                        strncat(sol, "Y", 100);
                        c_moves(c, "Y");
                        continue;
                    }else{
                        /*only orientation*/
                        strncat(sol, "RUUrURUUrUYluL", 100);
                        c_moves(c, "RUUrURUUrUYluL");
                        continue;
                    }
                }else{
                    /*RB*/
                    strncat(cor, "rURbRBr", 100);
                }
            }else{
                /*it is in L */
                if(p->p[0]==1){
                    /*LF */
                    strncat(cor, "lULfLFluu",100);
                }else{
                    /*LB*/
                    strncat(cor, "LulBlbL",100);
                }
            }
        }else{
        /*  it is in the U layer */
            if(p->p[0]==1){
                /*it is in UF --nothing to do*/
            }else if(p->p[1]==1){
                /*UR*/
                strncat(cor, "U", 100);
            }else if (p->p[1]==-1){
                /*it is in UL */
                strncat(cor, "u",100);
            }else{
                /*UB*/
                strncat(cor, "UU",100);
            }
        }
        
        c_moves(c,cor);/*make the moves*/
        
        /*now that the piece is in URF*/
        pos=c_iofPos(c, 1, 0, 1);
        p=&(c->pc[pos]);
        if(p->c[2]==cf){
            /*no mathc with center*/
            strncat(cor, "urfRURurF",100);
            c_moves(c,"urfRURurF");
        }else {
            /*matches with center*/
            strncat(cor, "URurFrfR",100);
            c_moves(c,"URurFrfR");
        }
        if(i<3){
            /*rotate cube to find next piece*/
            strncat(cor, "Y", 100);
            c_moves(c, "Y");
        }
        strncat(sol, cor, 100);
    }
}

void solve_topcross(Cube3* c, char *sol){
    short cu, pos;
    Piece *p1=NULL, *p2=NULL, *p3=NULL, *p4=NULL;
    char moves[101]="";
    int i, count, line=0;

    cu=cfrom(c, 'U');

    /*count oriented edges on the top*/
    for (i=count=0;i<4;i++){
        pos=c_iofPos(c, 1, 0, 1);
        if(cu==c->pc[pos].c[2]){
            count++;
        }
        c_moves(c, "U");
    }

    switch(count){
        case 0:{
            /*no edges oriented*/
            strncat(moves, "FRUruSRUrufs", 100);
        }
            break;
        case 2:{
            /*track the four edges on top*/
            pos=c_iofPos(c, 1, 0, 1);
            p1=&(c->pc[pos]);
            pos=c_iofPos(c, 0, 1, 1);
            p2=&(c->pc[pos]);
            pos=c_iofPos(c, -1, 0, 1);
            p3=&(c->pc[pos]);
            pos=c_iofPos(c, 0, -1, 1);
            p4=&(c->pc[pos]);
            /*look at all of the cases: */
            if(cu==p1->c[2]){
                if(cu==p3->c[2]){
                    line=1;
                }else if(cu==p2->c[2]){
                    line=-2;
                }else{
                    line=-1;
                }
            }else if(cu==p2->c[2]){
                if(cu==p4->c[2]){
                    line=2;
                }else{
                    line=-3;
                }
            }
            switch(line){
                case 1:
                    strncat(moves, "U", 100); /*no break on purpose*/
                case 2:
                    strncat(moves, "FRUruf", 100);
                    break;
                case -1:
                    strncat(moves, "u", 100); /*no break on purpose*/
                case -2:
                    strncat(moves, "u", 100); /*no break on purpose*/
                case -3:
                    strncat(moves, "u", 100); /*no break on purpose*/
                default:
                    strncat(moves, "FURurf", 100); /*no break on purpose*/
                    break;

            }
        }
            break;
        default:
            /* all oriented*/
            break;
    }
    c_moves(c, moves);
    strncat(sol, moves, 101);
}

void clean_moves(char* m){
    int i;
    if(!m){
        return ;
    }
    i=0;
    while(m[i]!=0){
        if(m[i]==m[i+1] && m[i]==m[i+2] && m[i]==m[i+3]){
            /*4 moves that are the same are useless*/
            m[i]=0;
            concatenate(m, m+i+4);
            i=0;
        }else if(m[i]==m[i+1] && m[i]==m[i+2] && m[i]!=m[i+3]){
            /*3 moves that are the same is equivalent to the opposite*/
            m[i]=opposite_move(m[i]);
            m[i+1]=0;
            concatenate(m, m+i+3);
            i=0;
        }else if(m[i]==opposite_move(m[i+1])){
            /*two opposite moves together are useless*/
            m[i]=0;
            concatenate(m, m+i+2);
            i=0;
        }else {
            i++;
        }
    }
}


void concatenate(char *a, char *b){
    int i, j;

    for(i=0; a[i]!=0; i++);

    for(j=0; b[j]!=0; i++, j++){
        a[i]=b[j];
    }
    a[i]=0;
}