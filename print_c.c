#include "print_c.h"
#include <string.h>
#include "types.h"


Status refresh_cube(Cube3* c, FILE* pf, cprint_from_stickers print_cube){
    short s[54];

    if (colour_stickers(c, c->sitckers) == ERROR){
        return ERROR;
    }

    print_cube(pf, s);

    return OK;
}

Status refresh_cube2(Cube3 *c, rect *r1, rect *r2, cprint_from_stickers2 print_cube){

    
    if (colour_stickers(c, c->sitckers) == ERROR)
        return ERROR;
    


    /*print_cube(c->sitckers,c->colorsESC,r1, r2);*/

    c_print3(c->sitckers, c->colorsESC, r1, r2);

    return OK;
}

int c_print(FILE *f, short *s){

  fprintf(f,"%c[2J",27);

    printf("%c[%i;%iH", 27, 10+2, 3);
    fprintf(f,"   ");
    fprintf(f,"%hd",s[35]);
    fprintf(f,"%hd", s[34]);
    fprintf(f,"%hd", s[33]);

    printf("%c[%i;%iH", 27, 10+3, 3);
    fprintf(f,"   ");
    fprintf(f,"%hd", s[32]);
    fprintf(f,"%hd", s[31]);
    fprintf(f,"%hd", s[30]);

    printf("%c[%i;%iH", 27, 10+4, 3);
    fprintf(f,"   ");
    fprintf(f,"%hd", s[29]);
    fprintf(f,"%hd", s[28]);
    fprintf(f,"%hd", s[27]);

    printf("%c[%i;%iH", 27, 10+6, 3);
    fprintf(f,"%hd", s[42]);
    fprintf(f,"%hd", s[39]);
    fprintf(f,"%hd", s[36]);
    fprintf(f, "%hd", s[0]);
    fprintf(f, "%hd", s[1]);
    fprintf(f, "%hd", s[2]);
    fprintf(f, "%hd", s[20]);
    fprintf(f, "%hd", s[23]);
    fprintf(f, "%hd", s[26]);

    printf("%c[%i;%iH", 27, 10+7, 3);
    fprintf(f, "%hd", s[43]);
    fprintf(f, "%hd", s[40]);
    fprintf(f, "%hd", s[37]);
    fprintf(f, "%hd", s[3]);
    fprintf(f, "%hd", s[4]);
    fprintf(f, "%hd", s[5]);
    fprintf(f, "%hd", s[19]);
    fprintf(f, "%hd", s[22]);
    fprintf(f, "%hd", s[25]);

    printf("%c[%i;%iH", 27, 10+8, 3);
    fprintf(f, "%hd", s[44]);
    fprintf(f, "%hd", s[41]);
    fprintf(f, "%hd", s[38]);
    fprintf(f, "%hd", s[6]);
    fprintf(f, "%hd", s[7]);
    fprintf(f, "%hd", s[8]);
    fprintf(f, "%hd", s[18]);
    fprintf(f, "%hd", s[21]);
    fprintf(f, "%hd", s[24]);

    printf("%c[%i;%iH", 27, 10+10, 3);
    fprintf(f, "   ");
    fprintf(f, "%hd", s[9]);
    fprintf(f, "%hd", s[10]);
    fprintf(f, "%hd", s[11]);

    printf("%c[%i;%iH", 27, 10+11, 3);
    fprintf(f, "   ");
    fprintf(f, "%hd", s[12]);
    fprintf(f, "%hd", s[13]);
    fprintf(f, "%hd", s[14]);

    printf("%c[%i;%iH", 27, 10+12, 3);
    fprintf(f, "   ");
    fprintf(f, "%hd", s[15]);
    fprintf(f, "%hd", s[16]);
    fprintf(f, "%hd", s[17]);

    printf("%c[%i;%iH", 27, 10+14, 3);
    fprintf(f, "   ");
    fprintf(f, "%hd", s[45]);
    fprintf(f, "%hd", s[46]);
    fprintf(f, "%hd", s[47]);

    printf("%c[%i;%iH", 27, 10+15, 3);
    fprintf(f, "   ");
    fprintf(f, "%hd", s[48]);
    fprintf(f, "%hd", s[49]);
    fprintf(f, "%hd", s[50]);

    printf("%c[%i;%iH", 27, 10+16, 3);
    fprintf(f, "   ");
    fprintf(f, "%hd", s[51]);
    fprintf(f, "%hd", s[52]);
    fprintf(f, "%hd", s[53]);

    fprintf(f,"\n\n");
    return 1;
}

Status sticker_to_color(short *s,short *c){
    int i;
    
    if(!s||!c)
        return ERROR;

    for (i = 0; i < 54; i++){
        switch (s[i]){
        case W:
            c[i] = 7;
            break;
        case Y:
            c[i] = 103;
            break;
        case O:
            c[i] = 45;
            break;
        case G:
            c[i] = 42;
            break;
        case B:
            c[i] = 44;
            break;
        case R:
            c[i] = 101;
            break;

        default:
            break;
        }
    }

    return OK;
}

double **sticker_colorSDL(short *s){ /*CAMBIAR PARA QUE NO SE ALOQUE*/
    int i,j;
    double **c;

    if (!s)
        return NULL;

    if (!(c = (double **)calloc(54, sizeof(double*))))
        return NULL;

    for(i=0;i<54;i++){
        if(!(c[i]=(double*)calloc(3,sizeof(double)))){
            for(j=0;j<i;j++){
                free(c[j]);
            }
            free(c);
            return NULL;
        }
    }

    for (i = 0; i < 54; i++){
        switch (s[i]){
            case W:
                c[i][0] = 1;
                c[i][1] = 1;
                c[i][2] = 1;
                break;
            case Y:
                c[i][0] = 1;
                c[i][1] = 1;
                c[i][2] = 0;
                break;
            case O:
                c[i][0] = 1;
                c[i][1] = 0.5;
                c[i][2] = 0;
                break;
            case G:
                c[i][0] = 0;
                c[i][1] = 1;
                c[i][2] = 0;
                break;
            case B:
                c[i][0] = 0;
                c[i][1] = 0;
                c[i][2] = 1;
                break;
            case R:
                c[i][0] = 1;
                c[i][1] = 0;
                c[i][2] = 0;
                break;

            default:
                break;
        }
    }

    return c;
}

void colorSDL_free(double **s){

    int i;

    if(s){
        for(i=0;i<54;i++){
            free(s[i]);
        }
        free(s);
    }
}

int c_print2(FILE *f, short *s,short *col){

    Bool flag = FALSE,rep=FALSE;
    int c, color, aux,column,line,incr=1,code=65,min=65; 
    FILE *fp;
    char firstview[30],secondview[30];

    /*
                                VARIABLES EXPLAINED
    (U): this variable has to be updated before printing second view
    column, line: where to start printing. (U)
     code: relation between the char that delimitates a sticker in the .txt and the postion in the array col (U).
     min: smallest char that is used to delimitate a sticker in the .txt
     rep: inidicates if you are printing first view (FALSE) or second (TRUE)
    */
   
   if(!s||!col){
        return -1;
   }

    /*WHERE TO START PRINTING 1st VIEW*/
    line = 3;
    column = 1;

    strcpy(firstview, "cubo.txt");
    strcpy(secondview, "cubo2.txt");

    sticker_to_color(s,col);
    if(col==NULL)
        return -1;

    fp = fopen(firstview, "r");
    printf("%c[2J", 27); /*Cleans the screen*/

    print:
    printf("%c[%i;%iH", 27, line, column); /*Positionates the cursor to start printing */

    do{
        c = fgetc(fp);
        if (feof(fp))
            break;

        if (c >= min && c <= min + 26){ /*If you have reached the begining of a sticker */
                
                aux = c;
                fprintf(f, " ");
                color = col[aux - code];           /*limits of stickers are letters between ASCII(min) and ACII(min+26).*/
                fprintf(f, "%c[;;%im", 27, color); /*stablish color of the sticker*/
                
                do{
                    c = fgetc(fp);
                    if (feof(fp))
                    {
                        flag = TRUE;
                        break;
                    }

                    if (c == aux){     /*we have reached the end of the sticker*/
                        fprintf(f, "%c[0m", 27); /*reset color*/
                        break;
                    }

                    fprintf(f, " ");

                } while (1);
            }

            if (c == '\n')
            { /*new line read --> update cursor position*/
                printf("%c[%i;%iH", 27, line + incr, column);
                incr++;
                continue;
            }

            if (flag == TRUE)
                break;

            fprintf(f, " ");
        }while (1);

        if (rep == FALSE)
        { /*update values for printing secondary view*/
            fclose(fp);
            rep = TRUE;
            code = 70;
            min = 97;
            incr = 1;
            fp = fopen(secondview, "r"); 
            column = column + 100;
            line = line + 30;
            goto print;
    }

    
    fclose(fp);
    return (0);
}

int c_print3(short *s,short*col, rect *r1, rect *r2){ /*Like cprint2 but using rectangles*/

    Bool flag = FALSE, rep = FALSE;
    int c, color, aux, column, line, incr = 1, code = 65, min = 65;
    FILE *fp;
    char firstview[30], secondview[30];

    if (!r1 || !r2||!s||!col)
        return -1;

    line = rect_getline(r1);
    column = rect_getcolumn(r1);

    strcpy(firstview, "cubo.txt");
    strcpy(secondview, "cubo2.txt");

    sticker_to_color(s,col);
  

    fp = fopen(firstview, "r");
    /*rect_clear(r1); // always printing in the same rect.*/

print:
    printf("%c[%i;%iH", 27, line, column); 

    do
    {
        c = fgetc(fp);
        if (feof(fp))
            break;

        if (c >= min && c <= min + 26)
        { /*If you have reached the begining of a sticker */

            aux = c;
            printf(" ");
            color = col[aux - code];       /*limits of stickers are letters between ASCII(min) and ACII(min+26).*/
            printf("%c[;;%im", 27, color); /*stablish color of the sticker*/

            do
            {
                c = fgetc(fp);
                if (feof(fp))
                {
                    flag = TRUE;
                    break;
                }

                if (c == aux){           
                    printf("%c[0m", 27); 
                    break;
                }

                printf(" ");

            } while (1);
        }

        if (c == '\n'){ 
            printf("%c[%i;%iH", 27, line + incr, column);
            incr++;
            continue;
        }

        if (flag == TRUE)
            break;

        printf(" ");
    } while (1);

    if (rep == FALSE)
    { /*update values for printing secondary view*/
        fclose(fp);
        rep = TRUE;
        code = 70;
        min = 97;
        incr = 1;
        fp = fopen(secondview, "r");
        column = rect_getcolumn(r2);
        line = rect_getline(r2);
        /*rect_clear(r2);*/
        goto print;
    }

    fclose(fp);
    return (0);
}

Status slow_moves(Cube3* c, cprint_from_stickers2 print_cube, char *moves, int delay,rect* r1, rect*r2){
    int i, len, j;

    if(!c||!moves||!r1||!r2||!print_cube){
        return ERROR;
    }

    len=strlen(moves);

    for(i=0;i<len;i++){
        c_make(c, moves[i]);
        refresh_cube2(c,r1,r2,print_cube);
        for(j=0;j<delay;j++);
    }
    return OK;
}


