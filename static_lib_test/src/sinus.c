
#include "sinus.h"
#include <math.h>

/*******************************************
 * Function to get sin(x) through the k-th
 * sinus series term
 ******************************************/
double sinus(int k, double x)
{
  double s = 0.0;
  int i;
  for (i=0; i<k; i++) 
  {
    s += pow(-1.0, i) * pow(x, 2.0*i+1.0) / (2.0 * (double) i + 1.0);
  }

  return s;

}

