/*first attempt to check cube.h*/

#include <stdio.h>
#include "cube.h"
#include "print_c.h"


int main(void) {
  Cube3 *c= NULL;
  short s[54];
  int i;

  c=c_init();
  if(!c) return 1;


  if(colour_stickers(c,s)==ERROR) {
    c_free(c);
    return 1;
  }

  c_print(stdout, s);

  printf("\n\n\n\n\n\n");

  c_free(c);
	return 0;
}