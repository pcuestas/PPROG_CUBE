/*first attempt to check cube.h*/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "interface.h"

int main(void)
{
  char *letters = "RUFLBDMESXYZruflbdmesxyz", **l_buff = NULL;
  rect *r;
  int i;

  r = rect_init(5, 5, 100, 100);
  terminal_clear();
  positionate_cursor(1, 1);

  l_buff = allocate_array_lettersbuffer(34);
  fill_buffer_letter(letters, l_buff);


  for(i=0;i<strlen(letters);i++){
    printf("%c and %i \n", letters[i],hash_letter(letters[i]));
  }

  

  print_solution_2("BufsuirasdrB", r, l_buff, 5,0);

  free_array_lettersbuffer(l_buff, 34);

  rect_free(r);

  return 0;
}