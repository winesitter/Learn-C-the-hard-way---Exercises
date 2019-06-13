#include "minunit.h"
//#include <lcthw/list.h>
#include <assert.h>
#include "list_tests.h"
#include "list_algos_tests.h"
#include "darray_tests.h"
#include "darray_algos_tests.h"

/***************************************************************
* Run all unit test functions
***************************************************************/
char *all_tests()
{
  mu_suite_start();

  /*************************************************************
  * Unit tests for list structure
  *************************************************************
  mu_run_test(test_list_create);
  mu_run_test(test_list_push_pop);
  mu_run_test(test_list_unshift);
  mu_run_test(test_list_remove);
  mu_run_test(test_list_shift);
  mu_run_test(test_list_join);
  mu_run_test(test_list_destroy);*/

  /*************************************************************
  * Unit tests for list algorithms
  *************************************************************
  mu_run_test(test_list_algos_bubble_sort);
  mu_run_test(test_list_algos_merge_sort);*/

  /*************************************************************
  * Unit tests for dynamic arrays
  *************************************************************/
  mu_run_test(test_darray_create);
  mu_run_test(test_darray_new);
  mu_run_test(test_darray_set);
  mu_run_test(test_darray_get);
  mu_run_test(test_darray_remove);
  
  mu_run_test(test_darray_expand_contract);
  mu_run_test(test_darray_push_pop);
  mu_run_test(test_darray_destroy);

  mu_run_test(test_darray_qsort);

  return NULL;
}
RUN_TESTS(all_tests);
