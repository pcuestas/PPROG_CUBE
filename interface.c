#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

#define LETTERS_PATH "./txt_files/letters_small/"
#define MAX_LEN 1024

extern int usleep(unsigned int );

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

rect *rect_copy(rect *r){
    
    if(!r)
        return NULL;
    
    return rect_init(r->line,r->column,r->l,r->h);
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

    positionate_cursor(line, column);

    do{
        c = fgetc(pf);
        if (feof(pf))
            break;

        if (c == '\n')
        { /*new line read --> update cursor position*/
            positionate_cursor(line+incr, column);
            incr++;
            continue;
        }

        printf("%c", c);

    } while (1);


    fflush(stdout);
   

    fclose(pf);
    return OK;
}

Status print_buffer(char *buf, int size, rect *r){

    int line, column, incr = 1, c, i = 0;

    if (!buf || !r || size == -1)
        return ERROR;

    line = r->line;
    column = r->column;

    /*rect_clear(r);*/

    if(size==-2)
        size=strlen(buf);

    positionate_cursor(line, column);

    do{
        c = buf[i];
        i++;

        if (c == '\n'){
            positionate_cursor(line + incr, column);
            incr++;
            continue;
        }

        printf("%c", c);

    } while (i < size);

    fflush(stdout);

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

Status rect_border(rect *r){

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

Status terminal_resize(int h, int w){
    if(h<1 || w<1)
        return ERROR;
    
    printf("%c[8;%i;%it%c[3J",27,h,w,27);

    return OK;
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

/**
 * @brief Modifies the string files (and also returns a pointer to it) 
 * so that it contains the name of the file with 'letter' as an ascii banner. 
 * 
 * */
char *file_of_letter(char*file, char letter){
    int j;
    if(!letter)
        return NULL;

    strncpy(file, LETTERS_PATH, MAX_LEN);
    j=strlen(file);
    file[j]=letter;
    file[j+1]='\0';

    return file;
}

int hash_letter(char letter){
    
    if(letter>90){
        if(letter=='s')
            return 4;
        if(letter=='u')
            return 5;
        
        return letter%17;
    }else{
        if(letter=='U')
            return 17+6;
        if(letter=='S')
            return 17+9;
        
        return 17+letter%17;
    }
}

void free_letter_buffer(char **buff, int size){

    int i;

    if(buff){
        for(i=0;i<size;i++){
            if(buff[i]!=NULL)
                free(buff[i]);
        }
    }
}

char ** allocate_array_lettersbuffer(int size){
    int i;
    char **buff;

    if(!(buff=(char**)calloc(size,sizeof(char*))))
        return NULL;
    
    for(i=0;i<size;i++)
        buff[i]=NULL;
    
    return buff;
}

void free_array_lettersbuffer(char ** buff, int size){
    int i;

    if(buff){
        for(i=0;i<size;i++){
            if(buff[i]!=NULL)
                free(buff[i]);
        }
    }
}

Status fill_buffer_letter(char* letters, char **buff){

    int i,pos,size;
    char filename[MAX_LEN];

    if(!letters||!buff)
        return ERROR;
    
    size=strlen(letters);

    for(i=0;i<size;i++){
        pos=hash_letter(letters[i]);
        if(ftobuffer(file_of_letter(filename, letters[i]),&(buff[pos]))==-1){
            free_letter_buffer(buff,34); /*We are assuming the size of **buf*/
            return ERROR;
        }
        
    }

    return OK;
    
}

Status print_solution(char *sol, rect *r, int letters_per_line){

    int n,i,line,l,column,c,printed=0,max,total=0;
    int dist_inter_line=5,dist_inter_letter=8;
    char filename[MAX_LEN];
    rect *r_aux;

    if(!sol||!r||letters_per_line<1)
        return ERROR;

    /*l=strlen(LETTERS_PATH);*/
    if((r_aux=rect_copy(r))==NULL)
        return ERROR;
    
    r_aux->l=dist_inter_letter;
    r_aux->h=dist_inter_line;
    max=(r->l/dist_inter_letter)*(r->h/dist_inter_line);

    n=strlen(sol);
    column=rect_getcolumn(r);
    line=rect_getline(r);
    c=column;
    l=line;

    rect_clear(r);

    for(i=0;i<n && total<max;i++){
        if(file_of_letter(filename,sol[i])==NULL)
            return ERROR;
        
        if(printed==letters_per_line){
            l+=dist_inter_line;
            rect_setcolumn(r_aux,column);
            rect_setline(r_aux,l);
            c=column;
            printed=0;
        }
        
        if(print_element(filename,r_aux)==ERROR) /*an invalid letter*/
            continue;

        fflush(stdout);
        c+=dist_inter_letter;
        rect_setcolumn(r_aux,c);
        printed++;
    }
    
    rect_free(r_aux);
    return OK;
}

Status print_solution_2(char *sol, rect *r, char**l_buffer, int letters_per_line){

    int n, i, line, l, column, c, printed = 0, max, total = 0;
    int dist_inter_line = 5, dist_inter_letter = 8,pos;
    rect *r_aux;

    if (!sol || !r || letters_per_line < 1||!l_buffer)
        return ERROR;

    if ((r_aux = rect_copy(r)) == NULL)
        return ERROR;

    max = (r->l / dist_inter_letter) * (r->h / dist_inter_line);

    n = strlen(sol);
    column = rect_getcolumn(r);
    line = rect_getline(r);
    c = column;
    l = line;

    rect_clear(r);

    for (i = 0; i < n && total < max; i++){

        if (printed == letters_per_line){
            l += dist_inter_line;
            rect_setcolumn(r_aux, column);
            rect_setline(r_aux, l);
            c = column;
            printed = 0;
        }

   
        pos=hash_letter(sol[i]);
        if(pos>33)
            continue;

        if(print_buffer(l_buffer[pos],-2,r_aux)==ERROR) /*an invalid letter*/
            continue;

        fflush(stdout);
        c += dist_inter_letter;
        rect_setcolumn(r_aux, c);
        printed++;
    }

    rect_free(r_aux);
    return OK;
}

Status print_confeti(rect *r, int ndots){
    int line, column, height, width,i,j;
    int h_frac, w_frac,x,y;
    int **positions;

    if(ndots<1)
        return ERROR;
    
    if(!(positions=(int**)calloc(ndots,sizeof(int*))))
        return ERROR;
    
    for(i=0;i<ndots;i++){
        if(!(positions[i]=(int*)calloc(2,sizeof(int*)))){
            for (j = 0; j < i; i++){
                free(positions[j]);
            }
            free(positions);
            return ERROR;
        }
            
    }

    if(!r){
        line=1;
        column=1;
        height=100;
        width=100;
    }else{
        line=r->line;
        column=r->column;
        height=r->h;
        width=r->l;
    }

    h_frac=height/5;
    w_frac=width/5;

    for(i=0,j=0;i<ndots;i++){

        /*Distribute more dots in the center of the rectangle*/
        if(i%3==0){
            y=random_num(line, line + height);
            x=random_num(column, column + width);
            positionate_cursor(y,x);
            positions[i][0]=y;
            positions[i][1]=x;
        }else{
            y = random_num(line + h_frac, line + 4* h_frac);
            x = random_num(column + w_frac, column + 4* w_frac);
            positionate_cursor(y,x);
            positions[i][0] = y;
            positions[i][1] = x;
        }
        

        switch (random_num(1, 6)){
        case 1:
            printf(HRED, 27);
            break;
        case 2:
            printf(HBLU, 27);
            break;
        case 3:
            printf(HCYN, 27);
            break;
        case 4:
            printf(HMAG, 27);
            break;
        case 5:
            printf(HYEL, 27);
            break;
        case 6:
            printf(HWHT, 27);
            break;
        case 7:
            printf(HGRN, 27);
            break;
        }

        printf("x");
        usleep(1000);

        if(i>ndots/3){ /*33% of the dots have been printed. we start deleting them*/
            printf(color_reset, 27);
            positionate_cursor(positions[j][0],positions[j][1]);
            printf(" ");
        }

    }
    printf(color_reset, 27);

    for(;j<ndots;j++){
        printf(color_reset, 27);
        positionate_cursor(positions[j][0], positions[j][1]);
        printf(" ");
    }

    free(positions);

    return OK;
}

Status fade_to_black(int line, int column, int expand){

    int n,side=3,i;
    int l,c,w;
    rect *r;

    /*

        | side       side 
        |<--->center<--->|
        |                |
        |________________|


    */

    if(line<1||column<1||expand<1)
        return ERROR;
    
    if(!(r=rect_init(line-side,column-side,2*side,2*side)))
        return ERROR;

    n=expand/side;
    l=line-side;
    c=column-side;
    w=2*side;

    for(i=0;i<n && l>=1 && c>=1 && w>=1 ;i++){
        rect_clear(r);
        l-=side;
        c-=side;
        w*=2;
        rect_setcolumn(r,c);
        rect_setheight(r,w);
        rect_setlength(r,w);
        rect_setline(r,l);

        sleep(1);
    }   

    terminal_clear();

    rect_free(r);
    return OK;
}