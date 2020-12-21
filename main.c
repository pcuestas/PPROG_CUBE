/*first attempt to check cube.h*/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "interface.h"



int main(void) {
   int i;
   rect *r, *r2, *r3;
   char *victory;

   srand(time(NULL));
   terminal_clear();
   positionate_cursor(1, 1);

   

 r = rect_init(2, 5, 20, 50);
   r2=rect_init(25,20,1,1);
   r3=rect_init(2, 45, 1, 1);

   print_buffer(victory, ftobuffer("test.txt", &victory), r2);
   for(i=0;i<5;i++){
       print_confeti(r, 300);
       print_confeti(r3, 300);
   }
   
   rect_free(r);
   return 0;
}