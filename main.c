/*first attempt to check cube.h*/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "interface.h"



int main(void) {
   char *letters="RUFLBDMESXYZruflbdmesxyz";
   char **buff;
   int i;
   rect *r;

   r=rect_init(5,5,100,100);
   terminal_clear();

   buff=(char**)calloc(34,sizeof(char*));
   for(i=0;i<34;i++){
     buff[i]=NULL;
   }



   fill_buffer_letter(letters, buff);


   /*print_buffer(buff[hash_letter('R')],-2,r);*/
  /*for(i=0;i<strlen(letters);i++){
    printf("letra %c posicion %i \n", letters[i], hash_letter(letters[i]));
    if (buff[hash_letter(letters[i])]==NULL){
      printf("\testa NULL\n");
    }
  }*/



   print_solution_2("BFubmxYz",r,buff,5);
   rect_free(r);



   return 0;
}