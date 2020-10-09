#include "print_c.h"


Status colour_stickers(Cube3* c, short *s){
  int i;
  if(!s||!c){
    return ERROR;
  }
  i=c_iofPos(c, 1, 1, 1);
  s[8]=c->pc[i].c[2];
  s[18]=c->pc[i].c[1];
  s[11]=c->pc[i].c[0];

  i=c_iofPos(c, -1, 1, 1);
  s[2]=c->pc[i].c[2];
  s[20]=c->pc[i].c[1];
  s[27]=c->pc[i].c[0];

  i=c_iofPos(c, -1, -1, 1);
  s[0]=c->pc[i].c[2];
  s[36]=c->pc[i].c[1];
  s[29]=c->pc[i].c[0];

  i=c_iofPos(c, 1, -1, 1);
  s[6]=c->pc[i].c[2];
  s[38]=c->pc[i].c[1];
  s[9]=c->pc[i].c[0];

  i=c_iofPos(c, 1, 1, -1);
  s[47]=c->pc[i].c[2];
  s[24]=c->pc[i].c[1];
  s[17]=c->pc[i].c[0];

  i=c_iofPos(c, -1, 1, -1);
  s[53]=c->pc[i].c[2];
  s[26]=c->pc[i].c[1];
  s[33]=c->pc[i].c[0];

  i=c_iofPos(c, -1, -1, -1);
  s[51]=c->pc[i].c[2];
  s[42]=c->pc[i].c[1];
  s[35]=c->pc[i].c[0];

  i=c_iofPos(c, 1, -1, -1);
  s[45]=c->pc[i].c[2];
  s[44]=c->pc[i].c[1];
  s[15]=c->pc[i].c[0];


  i=c_iofPos(c, 0, 0, 1);
  s[4]=c->pc[i].c[2];

  i=c_iofPos(c, 0, 0, -1);
  s[49]=c->pc[i].c[2];

  i=c_iofPos(c, 0, 1, 0);
  s[22]=c->pc[i].c[1];

  i=c_iofPos(c, 0, -1, 0);
  s[40]=c->pc[i].c[1];

  i=c_iofPos(c, 1, 0, 0);
  s[13]=c->pc[i].c[0];

  i=c_iofPos(c, -1, 0, 0);
  s[31]=c->pc[i].c[0];


  i=c_iofPos(c, 1, 0, 1);
  s[7]=c->pc[i].c[2];
  s[10]=c->pc[i].c[0];

  i=c_iofPos(c, -1, 0, 1);
  s[1]=c->pc[i].c[2];
  s[28]=c->pc[i].c[0];
  
  i=c_iofPos(c, -1, 0, -1);
  s[52]=c->pc[i].c[2];
  s[34]=c->pc[i].c[0];

  i=c_iofPos(c, 1, 0, -1);
  s[46]=c->pc[i].c[2];
  s[16]=c->pc[i].c[0];


  i=c_iofPos(c, 1, 1, 0);
  s[14]=c->pc[i].c[0];
  s[21]=c->pc[i].c[1];

  i=c_iofPos(c, -1, 1, 0);
  s[30]=c->pc[i].c[0];
  s[23]=c->pc[i].c[1];

  i=c_iofPos(c, -1, -1, 0);
  s[32]=c->pc[i].c[0];
  s[39]=c->pc[i].c[1];
  
  i=c_iofPos(c, 1, -1, 0);
  s[12]=c->pc[i].c[0];
  s[41]=c->pc[i].c[1];

    
  i=c_iofPos(c, 0, 1, 1);
  s[5]=c->pc[i].c[2];
  s[19]=c->pc[i].c[1];
    
  i=c_iofPos(c, 0, 1, -1);
  s[50]=c->pc[i].c[2];
  s[25]=c->pc[i].c[1];
    
  i=c_iofPos(c, 0, -1, -1);
  s[48]=c->pc[i].c[2];
  s[43]=c->pc[i].c[1];
    
  i=c_iofPos(c, 0, -1, 1);
  s[3]=c->pc[i].c[2];
  s[37]=c->pc[i].c[1];

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
