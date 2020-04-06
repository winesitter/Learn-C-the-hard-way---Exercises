#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 

/*******************************************************************************
* Matrix structure
*******************************************************************************/
typedef struct {
	int m, n;
	double ** v;
} mat_t, *mat;



/*******************************************************************************
* Create a new matrix structure
*******************************************************************************/
mat matrix_new(int m, int n)
{
  int i;
	mat x = malloc(sizeof(mat_t));
	x->v = malloc(sizeof(double*) * m);
	x->v[0] = calloc(sizeof(double), m * n);
	for (i = 0; i < m; i++)
		x->v[i] = x->v[0] + n * i;
	x->m = m;
	x->n = n;
	return x;
}
 
/*******************************************************************************
* Delete a matrix structure
*******************************************************************************/
void matrix_delete(mat m)
{
	free(m->v[0]);
	free(m->v);
	free(m);
}
 
/*******************************************************************************
* Transpose a matrix structure
*******************************************************************************/
void matrix_transpose(mat m)
{
  int i, j;
	for (i = 0; i < m->m; i++) {
		for (j = 0; j < i; j++) {
			double t = m->v[i][j];
			m->v[i][j] = m->v[j][i];
			m->v[j][i] = t;
		}
	}
}

/*******************************************************************************
* Copy a matrix
*******************************************************************************/
mat matrix_newcopy(mat a)
{
  int i,j;
	mat x = matrix_new(a->m, a->n);
	for (i = 0; i < a->m; i++)
		for (j = 0; j < a->n; j++)
			x->v[i][j] = a->v[i][j];
	return x;
}

/*******************************************************************************
* Copy a matrix
*******************************************************************************/
void matrix_copy(mat a, mat x)
{
  int i,j;
  if (a->m != x->m || a->n != x->n)
    printf("ERROR IN matrix_copy()\n");
    
	for (i = 0; i < a->m; i++)
		for (j = 0; j < a->n; j++)
			x->v[i][j] = a->v[i][j];
}
 
/*******************************************************************************
* Copy the input of an arry to a new matrix 
*******************************************************************************/
mat matrix_copy_array(int n, double a[][n], int m)
{
  int i,j;
	mat x = matrix_new(m, n);
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			x->v[i][j] = a[i][j];
	return x;
}
 
/*******************************************************************************
* Multiplication of two matrices
*******************************************************************************/
mat matrix_mul(mat x, mat y)
{
  int i,j,k;
	if (x->n != y->m) return 0;
	mat r = matrix_new(x->m, y->n);
	for (i = 0; i < x->m; i++)
		for (j = 0; j < y->n; j++)
			for (k = 0; k < x->n; k++)
				r->v[i][j] += x->v[i][k] * y->v[k][j];
	return r;
}
 
/*******************************************************************************
* Copy minor dxd entries of matrix d into new matrix m
*******************************************************************************/
mat matrix_minor(mat x, int d)
{
  int i,j;
	mat m = matrix_new(x->m, x->n);
	for (i = 0; i < d; i++)
		m->v[i][i] = 1;
	for (i = d; i < x->m; i++)
		for (j = d; j < x->n; j++)
			m->v[i][j] = x->v[i][j];
	return m;
}
 
/*******************************************************************************
* c = a + b * s 
*******************************************************************************/
double *vmadd(double a[], double b[], double s, double c[], int n)
{
  int i;
	for (i = 0; i < n; i++)
		c[i] = a[i] + s * b[i];
	return c;
}
 
/*******************************************************************************
* m = I - v v^T 
*******************************************************************************/
mat vmul(double v[], int n)
{
  int i,j;
	mat x = matrix_new(n, n);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			x->v[i][j] = -2 *  v[i] * v[j];
	for (i = 0; i < n; i++)
		x->v[i][i] += 1;
 
	return x;
}
 
/*******************************************************************************
* ||x|| 
*******************************************************************************/
double vnorm(double x[], int n)
{
  int i;
	double sum = 0;
	for (i = 0; i < n; i++) sum += x[i] * x[i];
	return sqrt(sum);
}
 
/*******************************************************************************
* y = x / d 
*******************************************************************************/
double* vdiv(double x[], double d, double y[], int n)
{
  int i;
	for (i = 0; i < n; i++) y[i] = x[i] / d;
	return y;
}
 
/*******************************************************************************
* take c-th column of m, put in v 
*******************************************************************************/
double* mcol(mat m, double *v, int c)
{
  int i;
	for (i = 0; i < m->m; i++)
		v[i] = m->v[i][c];
	return v;
}
 
/*******************************************************************************
* Print matrix
*******************************************************************************/
void matrix_show(mat m)
{
  int i,j;
	for(i = 0; i < m->m; i++) {
		for (j = 0; j < m->n; j++) {
			printf(" %8.3f", m->v[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
 
/*******************************************************************************
* Householder QR-decomposition
*******************************************************************************/
void householder(mat m, mat *R, mat *Q)
{
  int i,k;
	mat q[m->m];
	mat z = m, z1;
	for (k = 0; k < m->n && k < m->m - 1; k++) {
		double e[m->m], x[m->m], a;
		z1 = matrix_minor(z, k);
		if (z != m) matrix_delete(z);
		z = z1;
 
		mcol(z, x, k);
		a = vnorm(x, m->m);
		if (m->v[k][k] > 0) a = -a;
 
		for (i = 0; i < m->m; i++)
			e[i] = (i == k) ? 1 : 0;
 
		vmadd(x, e, a, e, m->m);
		vdiv(e, vnorm(e, m->m), e, m->m);
		q[k] = vmul(e, m->m);
		z1 = matrix_mul(q[k], z);
		if (z != m) matrix_delete(z);
		z = z1;
	}
	matrix_delete(z);
	*Q = q[0];
	*R = matrix_mul(q[0], m);
	for (i = 1; i < m->n && i < m->m - 1; i++) {
		z1 = matrix_mul(q[i], *Q);
		if (i > 1) matrix_delete(*Q);
		*Q = z1;
		matrix_delete(q[i]);
	}
	matrix_delete(q[0]);
	z = matrix_mul(*Q, m);
	matrix_delete(*R);
	*R = z;
	matrix_transpose(*Q);
}

/*******************************************************************************
* Compute the inverse of a matrix 
*******************************************************************************/
mat matrix_inverse(mat A0)
{
  int i, j, k;
  mat A = matrix_newcopy(A0);
  mat A_inv = matrix_new(A0->m, A0->n);
  double c;

  /*----------------------------------------------------------------------------
  | Initialize inverse
  ----------------------------------------------------------------------------*/
  for(i = 0; i < A->m; i++) {
    for (j=0; j < A->n; j++) {
      if (j == i)
        A_inv->v[i][j] = 1.0;
      else
        A_inv->v[i][j] = 0.0;
    }
  }
  
  /*----------------------------------------------------------------------------
  | Pivoting elements
  ----------------------------------------------------------------------------*/
  for (j = 0; j < A->n; j++) {
    for (i = 0; i < A->m; i++) {
      if (i != j) {
        c = A->v[i][j] / A->v[j][j];
        for (k = 0; k < A->m; k++) {
          A->v[i][k] = A->v[i][k] - c * A->v[j][k];
          A_inv->v[i][k] = A_inv->v[i][k] - c * A_inv->v[j][k];
        }
      }
    }
  }

  /*----------------------------------------------------------------------------
  | Normalization
  ----------------------------------------------------------------------------*/
  for (i = 0; i < A->m; i++)
    for (j = 0; j < A->n; j++)
      A_inv->v[i][j] /= A->v[i][i];

  matrix_delete(A);
  return A_inv;

}
 
/*******************************************************************************
* Init new matrix
*******************************************************************************/
double in[][3] = {
	{  cos(0.5),   1,   sin(0.5)},
	{         0,   1,          0},
	{ -sin(0.5),   0,   cos(0.5)},
};

/*
double in[][3] = {
	{  12., -51., 4.},
	{  6., 167., -68.},
	{  -4., 24., -41.},
};
*/
 

/*******************************************************************************
* Main function
*******************************************************************************/
int main()
{
  int i;

	mat R, Q;
	mat A = matrix_copy_array(3, in, 3);

  puts("A"); matrix_show(A);

  for (i = 0; i < 10000000; i++) {
    householder(A, &R, &Q);

    mat Q_inv = matrix_inverse(Q);
    mat A_k1 = matrix_mul(Q_inv, A);
    mat A_k2 = matrix_mul(A_k1, Q);
    matrix_copy(A_k2, A);

    matrix_delete(A_k1);
    matrix_delete(A_k2);
    matrix_delete(Q_inv);
    /*
    mat A_k = matrix_mul(Q, R);
    matrix_copy(A_k, A);
    matrix_delete(A_k);
    */
  }

  puts("A"); matrix_show(A);

	matrix_delete(A);
	matrix_delete(R);
	matrix_delete(Q);

	return 0;
}
