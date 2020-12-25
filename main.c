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

   r=rect_init(20,20,100,100);
   terminal_clear();

  print_element("test.txt",r); 


  usleep(50000);
  fade_to_black(50,50,1000);
  

   return 0;
}