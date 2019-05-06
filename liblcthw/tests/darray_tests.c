#include "minunit.h"
#include <lcthw/darray.h>
#include "darray_tests.h"

/***************************************************************
* Definition of unit test variables 
***************************************************************/
static DArray *array = NULL;
static int *val1 = NULL;
static int *val2 = NULL;

/***************************************************************
* Definition of unit test functions 
***************************************************************/
char *test_darray_create()
{
  array = DArray_create(sizeof(int), 100);
  
  mu_assert(array != NULL, "DArray_create failed.");
  mu_assert(array->contents != NULL, 
      "contents are wrong in darray.");
  mu_assert(array->end == 0, 
      "DArray end isn't at the right spot.");
  mu_assert(array->element_size == sizeof(int),
      "DArray element_size is wrong.");
  mu_assert(array->max == 100, 
      "DArray max is wrong.");

  return NULL;
}
