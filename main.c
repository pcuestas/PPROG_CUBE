/*first attempt to check cube.h*/

#include <stdio.h>
#include "interface.h"


int main(void) {

  char sol[30] = "bBdDeEfFILmMrRssuUxyYzz";
  rect *r;


  r = rect_init(4, 10, 54, 54);

  print_solution(sol, r, 6);

  rect_free(r);

  return 0;
}