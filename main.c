/*first attempt to check cube.h*/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "interface.h"

int main(void)
{
  rect *r2;

  int columns, lines, i, center[2];
  int incr_l, h, l, incr_h, times = 15, hh,ll;
  rect *r;

  r2 = rect_init(5, 5, 100, 100);
  
  terminal_clear();

  print_element("./txt_files/cubo3.txt",r2);
  
  while(scanf("%c",&i)!=1){
    continue;
  }


    columns = get_columnsfromterm();
    lines = get_linesfromterm();

    center[0] = columns / 2;
    center[1] = lines / 2;

    incr_h = lines / (2 * times);
    incr_l = columns / (2 * times);

    l = incr_l;
    h = incr_h;

    hh=h;
    ll=l;

    

    if (!(r = rect_init(center[1], center[0], 2 * incr_l, 2 * incr_h)))
      return ERROR;

    for (i = 0; i < times; i++){

      if (i != 0)
      {
        rect_color(r, WHITE);
      }

      l += incr_l;
      h += incr_h;

      rect_setheight(r, 2 *h );
      rect_setlength(r, 2 * l);

      rect_setline(r, center[1] - h);
      rect_setcolumn(r, center[0] - l);
      usleep(60000);
    }

    printf("H era %i y L era %i",hh,ll);
    rect_free(r);

    terminal_clear();
   
    return 0;
}