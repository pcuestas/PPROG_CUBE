/*first attempt to check cube.h*/

#include <stdio.h>
#include "interface.h"


int main(void) {

  char sol[20] = "XrRFfyzswrTmzYx";
  rect *r;

  terminal_clear();

  r = rect_init(4, 10, 36, 63);

  print_solution(sol, r, 6);

  rect_free(r);

  return 0;
}