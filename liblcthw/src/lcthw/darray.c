#include <lcthw/darray.h>

/***************************************************************
* Function to create a new DArray
***************************************************************/
DArray *DArray_create(size_t element_size, size_t initial_max)
{
  DArray *array = calloc(1, sizeof(DArray));

  array->end = 0;
  array->max = initial_max;

  array->element_size = element_size;
  array->expand_rate = DEFAULT_EXPAND_RATE;

  array->contents = calloc(initial_max, element_size);

  return array;

}
