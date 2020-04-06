#include <stdio.h>
#include <stdlib.h>


#define N 10


int main(int argc, char *argv[])
{
  double (*a)[4] = calloc(N, 4*sizeof(double));

  int i;
  for (i=0; i < N; i++)
  {
    a[i][0] = (double) i;
    a[i][1] = (double) i * 0.123;
    a[i][2] = (double) i * 0.234;
    a[i][3] = (double) i * 0.345;
  }

  for (i=0; i < N; i++)
    printf("a: (%.3f, %.3f, %.3f, %.3f)\n", a[i][0], a[i][1], a[i][2], a[i][3]);

  for (i=0; i < N; i++)
  {
    double *sx = a[i];
    double *sy = a[i]+2;

    printf("sx: (%.3f, %.3f)\n", sx[0], sx[1]);
    printf("sy: (%.3f, %.3f)\n", sy[0], sy[1]);
  }

  for (i=0; i < N; i++)
    printf("a: (%.3f, %.3f, %.3f, %.3f)\n", a[i][0], a[i][1], a[i][2], a[i][3]);
    
  printf("DONE\n");
  free(a);


  return 0;
}
