/*first attempt to check cube.h*/

#include <stdio.h>
#include "interface.h"


int main(void) {

  printf("hpañaña");
  printf("%c[8;%i;%it%c[3J", 27, 100, 100, 27);

  return 0;
}