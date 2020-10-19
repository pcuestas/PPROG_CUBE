#include "print_c.h"


Status refresh_cube(Cube3* c, FILE* pf, cprint_from_stickers print_cube){
    short *s=NULL;
    
    if(!(s = (short*) calloc (54,sizeof(short)))){
        return ERROR;
    }

    if (colour_stickers(c, s) == ERROR){
        return ERROR;
    }

    print_cube(pf, s);

    free(s);

    return OK;
}

int c_print(FILE *f, short *s)
{

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

short *sticker_to_color(short *s)
{
    int i;
    short *c;

    if (!s)
        return NULL;

    if (!(c = (short *)calloc(54, sizeof(short))))
        return NULL;

    for (i = 0; i < 54; i++)
    {
        switch (s[i])
        {
        case W:
            c[i] = 7;
            break;
        case Y:
            c[i] = 103;
            break;
        case O:
            c[i] = 43;
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

    return c;
}

int c_print2(FILE *f, short *s)
{
    /*Liberar el array col!!!*/
    Bool flag = 0;
    int color, aux;
    short *col;

    FILE *fp;
    int c;

    printf("%c[2J", 27);
    printf("%c[1;1H", 27);

    fp = fopen("cubo.txt", "r"); /*de donde leo*/
    col = sticker_to_color(s);

    do
    {
        c = fgetc(fp);
        if (feof(fp))
        {
            break;
        }
        if (c >= 65 && c <= 91)
        {
            aux = c;
            fprintf(f, "%c", c);
            color = col[aux - 65]; /*limits of rectangles are between 65 and 91 -> col[0] to col[26]*/
            fprintf(f, "%c[;;%im", 27, color);
            do
            {
                c = fgetc(fp);
                if (feof(fp))
                {
                    flag = 1;
                    break;
                }

                if (c == aux) /*we have reach the 'wall' of the rectangle*/
                {
                    fprintf(f, "%c[0m", 27);
                    break;
                }

                fprintf(f, "%c", c);

            } while (1);
        }

        if (flag == 1)
            break;

        fprintf(f, "%c", c);
    } while (1);

    free(col);
    fclose(fp);
    return (0);
}