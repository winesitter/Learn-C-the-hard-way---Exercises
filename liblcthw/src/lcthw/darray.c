#include <lcthw/darray.h>

/***************************************************************
* Function to create a new DArray
***************************************************************/
DArray *DArray_create(size_t element_size, size_t initial_max)
{
  DArray *array = calloc(1, sizeof(DArray));
  check_mem(array);

  array->end = 0;
  array->max = initial_max;

  array->element_size = element_size;
  array->expand_rate = DEFAULT_EXPAND_RATE;

  array->contents = calloc(initial_max, element_size);
  check_mem(array->contents);

  return array;
error:
  return NULL;

}

/***************************************************************
* Function frees content pointer array and DArray struct memory
***************************************************************/
void DArray_destroy(DArray *array)
{
  if (array) {
    if (array->contents)
      free(array->contents);
    free(array);
  }
}

/***************************************************************
* Function frees memory for every content entry of DArray
***************************************************************/
void DArray_clear(DArray *array)
{
  int i = 0;
  if (array->element_size > 0) {
    for (i = 0; i < array->max; i++) {
      if (array->contents[i] != NULL) {
        free(array->contents[i]);
      }
    }
  }
}

/***************************************************************
* Function to fully clear a DArray memory
***************************************************************/
void DArray_clear_destroy(DArray *array)
{
  DArray_clear(array);
  DArray_destroy(array);
}
