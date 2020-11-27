#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

struct _rect{
    int line, column; /*Upper left corner*/
    int l,h; /*length and height*/
};

rect *rect_init(int line, int column, int l, int h){
    rect *r;

    if(line<1||column<1||l<1||h<1)
        return NULL;
    
    if(!(r=(rect*)calloc(1,sizeof(rect))))
        return NULL;
    
    r->column=column;
    r->line=line;
    r->h=h;
    r->l=l;

    return r;
}

void rect_free(rect*r){
    if(r)
        free(r);
}

Status rect_setline(rect*r,int line){
    if(!r||line<1)
        return ERROR;

    r->line=line;
    return OK;
}

Status rect_setcolumn(rect *r, int column){
    if (!r || column < 1)
        return ERROR;

    r->column = column;
    return OK;
}

Status rect_setlength(rect *r, int l){
    if (!r || l < 0)
        return ERROR;

    r->l = l;
    return OK;
}

Status rect_setheight(rect *r, int h){
    
    if (!r || h < 1)
        return ERROR;

    r->h = h;
    return OK;
}

int rect_getline(rect *r){
    if(!r)
        return -1;
    return r->line;
}
int rect_getcolumn(rect *r){
    if(!r)
        return -1;
    return r->column;
}
int rect_getl(rect *r){
    if(!r)
        return -1;
    return r->l;
}
int rect_geth(rect *r){
    if(!r)
        return -1;
    return r->h;
}

Status print_element(char*filename, rect*r){

    int line,column,incr=1,c;
    FILE *pf;

    if(!filename||!r)
        return ERROR;

    if(!(pf=fopen(filename,"r")))
        return ERROR;

    line = r->line;
    column = r->column;

    rect_clear(r);

    printf("%c[%i;%iH", 27, line, column);

    do{
        c = fgetc(pf);
        if (feof(pf))
            break;

        if (c == '\n')
        { /*new line read --> update cursor position*/
            printf("%c[%i;%iH", 27, line + incr, column);
            incr++;
            continue;
        }

        fprintf(stdout, "%c", c);

    } while (1);


    fclose(pf);
    return OK;
}


void rect_clear(rect*r){

    int line, column, h,l;
    int i,j;

    if(!r)
        return;
    
    line=r->line;
    column=r->column;
    h=r->h;
    l=r->l;

    for(i=0;i<h;i++){
    printf("%c[%i;%iH", 27, line+i, column);
        for(j=0;j<l;j++){
            printf(" ");
        }
    }
    
}

Status rect_border(rect *r)
{

    int line, column, l, h, i;

    if (!r)
        return ERROR;

    line = r->line;
    column = r->column;
    l = r->l;
    h = r->h;

    positionate_cursor(line, column);
    for (i = 0; i < l; i++){
        printf("%s", "━");
    }

    positionate_cursor(line + h, column);
    for (i = 0; i < l; i++){
        printf("%s", "━");
    }

    positionate_cursor(line, column);
    for (i = 0; i < h; i++){
        positionate_cursor(line + 1 + i, column);
        printf("%s", "┃");
    }

    positionate_cursor(line, column + l);
    for (i = 0; i < h; i++){
        positionate_cursor(line + 1 + i, column + l);
        printf("%s", "┃");
    }

    positionate_cursor(line, column);
    printf("%s", "┏");

    positionate_cursor(line + h, column);
    printf("%s", "┗");

    positionate_cursor(line, column + l);
    printf("%s", "┓");

    positionate_cursor(line + h, column + l);
    printf("%s", "┛");

    return OK;
}

void terminal_clear(){
    printf("%c[2J", 27);
}

Status positionate_cursor(int line, int column){

    if(line<1||column<1)
        return ERROR;

    printf("%c[%i;%iH", 27, line, column);
    return OK;
}

rect* rect_expand(rect *r, int x, int y){

    rect *r2;

    if(!r||r->column-x<1||r->line-y<1)
        return NULL;

    if (!(r2 = rect_init(r->line - y, r->column - x, r->l + x, r->h + y)))
        return NULL;

    return r2;
}