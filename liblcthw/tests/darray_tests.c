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

char *test_darray_destroy()
{
  DArray_destroy(array);

  return NULL;
}

char *test_darray_new()
{
  val1 = DArray_new(array);
  mu_assert(val1 != NULL, "failed to make a new element.");

  val2 = DArray_new(array);
  mu_assert(val2 != NULL, "failed to make a new element.");

  return NULL;
}

char *test_darray_set()
{
  DArray_set(array, 0, val1);
  DArray_set(array, 1, val2);

  return NULL;
}

char *test_darray_get()
{
  mu_assert(DArray_get(array, 0) == val1, 
      "Wrong first value.");
  mu_assert(DArray_get(array, 1) == val2, 
      "Wrong first value.");

  return NULL;
}

char *test_darray_remove()
{
  int *val_check =  DArray_remove(array, 0);
  mu_assert(val_check != NULL, "Should not get NULL.");
  mu_assert(*val_check == *val1, "Should get the first value.");
  mu_assert(DArray_get(array, 0) == NULL, "Should be gone.");
  DArray_free(val_check);

  val_check =  DArray_remove(array, 1);
  mu_assert(val_check != NULL, "Should not get NULL.");
  mu_assert(*val_check == *val2, "Should get the first value.");
  mu_assert(DArray_get(array, 1) == NULL, "Should be gone.");
  DArray_free(val_check);

  return NULL;

}
