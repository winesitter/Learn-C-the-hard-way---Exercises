#include <stdio.h>
#include <stdlib.h>
#include "fact.h"
#include "sinus.h"


/*****************************************************************************
 *
 * Tutorial from:
 * segfault.in/blog/2008/04/25/how-to-create-static-libraries-with-gcc/
 *
 *  stackoverflow.com/questions/15906286/static-libraries-and-headers-in-another-directories-with-gcc
 *
 ****************************************************************************/

int main(int argc, char *argv[])
{
  
  int k = 0;
  if (argc > 1)
  {
    int a = atoi(argv[1]);
    printf("Factorial of %d is %d \n", a, fact(a));
    k = a;
  }

  double f = 3.14;
  printf("Sinus of 3.14 is: %lf \n", sinus(k, f));

  printf("IT WORKED!!! :-) \n");
  

  return 0;
}
