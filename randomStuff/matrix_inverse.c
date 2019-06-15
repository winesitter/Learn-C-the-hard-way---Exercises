#include <math.h>
#include <stdio.h>
#include <stdlib.h>


/****************************************************************
* print matrix to command line
****************************************************************/
void print_matrix(int m, int n, double (*A)[n])
{
  int i,j;
  for (i = 0; i < m; i++)
  {
    printf("|");
    for (j = 0; j < n; j++)
    {
      if (fabs(A[i][j]) > 1e-10)
        printf(" %9.5f ", A[i][j]);
      else
        printf("           ");
    }

    printf("|\n");
  }
}

/****************************************************************
* init matrix
****************************************************************/
void init_matrix(int n, double (*A)[n])
{
  srand((unsigned) 0);
  int i,j;
  for(i = 0; i < n; i++)
    for (j=0; j < n; j++)
      A[i][j] = (double) (rand() % 50);
}


/****************************************************************
* Matrix product
****************************************************************/
void matrix_product(int n, double (*A)[n], double (*B)[n], double (*C)[n])
{
  int i,j,k;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    {
      C[i][j] = 0.0;
      for (k = 0; k < n; k++)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
}


/****************************************************************
* Gauss-Jordan elimination 
****************************************************************/
void gauss_jordan_elimination(int n, double (*A)[n], double (*A_inv)[n])
{
  int i, j, k;
  double c;

  /* Init inverse */
  for(i = 0; i < n; i++)
  {
    for (j=0; j < n; j++)
    {
      if (j == i)
        A_inv[i][j] = 1.0;
      else
        A_inv[i][j] = 0.0;
    }
  }
  
  /* Pivoting elements */
  for (j = 0; j < n; j++)
  {
    for (i = 0; i < n; i++)
    {
      if (i != j)
      {
        c = A[i][j] / A[j][j];
        for (k = 0; k < n; k++)
        {
          A[i][k] = A[i][k] - c * A[j][k];
          A_inv[i][k] = A_inv[i][k] - c * A_inv[j][k];
        }
      }
    }
  }

  /* Normalization to 1 */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      A_inv[i][j] /= A[i][i];


}

/****************************************************************
* main function
****************************************************************/
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("matrix_inverse <n>\n");
    exit(0);
  }

  int i,j;
  int n = atoi(argv[1]);

  /* Init matrix A */
  double (*A)[n]     = calloc(n, n*sizeof(double));
  double (*A_inv)[n] = calloc(n, n*sizeof(double));
  double (*A0)[n]    = calloc(n, n*sizeof(double));
  init_matrix(n, A);

  /* Store initial matrix */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      A0[i][j] = A[i][j];

  /* Print initial matrix */
  printf("\n%d x %d Matrix A:\n", n, n);
  print_matrix(n, n, A);

  /* Perform Gauss-Jordan elimination */
  gauss_jordan_elimination(n, A, A_inv);

  /* Print inverse of matrix */
  printf("\nInverse Matrix A:\n");
  print_matrix(n, n, A_inv);

  /* Check correctness */
  double (*I)[n] = calloc(n, n*sizeof(double));

  printf("\nI = A * inv(A): \n");
  matrix_product(n, A0, A_inv, I);
  print_matrix(n, n, I);

  free(A);
  free(A0);
  free(A_inv);
  free(I);

  return 0;

}
