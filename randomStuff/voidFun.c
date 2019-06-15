#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 100


double (*init_3array(int t))[3]
{
  double (*array)[3] = calloc(t, 3 * sizeof(double));
  int i;
  for (i = 0; i < t; i++)
  {
    array[i][0] = (double) i;
    array[i][1] = 2.0 * (double) i;
    array[i][2] = 4.0 * (double) i;
  }

  return array;
}

double (*init_6array(int t))[6]
{
  double (*array)[6] = calloc(t, 6 * sizeof(double));
  int i;
  for (i = 0; i < t; i++)
  {
    array[i][0] = (double) i;
    array[i][1] = 2.0 * (double) i;
    array[i][2] = 4.0 * (double) i;

    array[i][3] = (double) i;
    array[i][4] = 0.5 * (double) i;
    array[i][5] = 0.25 * (double) i;
  }

  return array;
}


double (*calc_grad(int s, double (*array)[s], int axis, int t))[3]
{
  double (*grad)[3] = calloc(t, 3 * sizeof(double));

  int i;
  for (i = 0; i < t; i++)
  {
    grad[i][0] = array[i][axis] / 2.;
    grad[i][1] = array[i][axis] / 4.;
    grad[i][2] = array[i][axis] / 8.;
  }
  
  return grad;
}




int main(int argc, char *argv[])
{

  double (*array3)[3] = init_3array(N);
  double (*array6)[6] = init_6array(N);


  double (*gradx)[3] = calc_grad(3, array3, 0, N);
  double (*grady)[3] = calc_grad(3, array3, 1, N);
  double (*gradz)[3] = calc_grad(3, array3, 2, N);

  double (*grad6x)[3] = calc_grad(6, array6, 0, N);
  double (*grad6y)[3] = calc_grad(6, array6, 3, N);
  double (*grad6z)[3] = calc_grad(6, array6, 5, N);

  free(grad6x);
  free(grad6y);
  free(grad6z);

  int i;
  for (i = 0; i < N; i++)
  {
    printf("array3[%d]: (%3.2f, %3.2f, %3.2f)\n", i, array3[i][0],array3[i][1],array3[i][2]);
    printf("gradx[%d]:  (%3.2f, %3.2f, %3.2f)\n", i, gradx[i][0],gradx[i][1],gradx[i][2]);
    printf("grady[%d]:  (%3.2f, %3.2f, %3.2f)\n", i, grady[i][0],grady[i][1],grady[i][2]);
    printf("gradz[%d]:  (%3.2f, %3.2f, %3.2f)\n", i, gradz[i][0],gradz[i][1],gradz[i][2]);
    printf("\n");
  }


  free(array3);
  free(array6);
  free(gradx);
  free(grady);
  free(gradz);

  return 0;
}
