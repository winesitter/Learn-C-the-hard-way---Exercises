
#include "fact.h"

/*****************************
 * Function to calucate the 
 * factorial of a number f
 ****************************/
int fact (int f)
{
  if (f == 0)
    return 1;
  else
    return (f * fact(f - 1));
}
