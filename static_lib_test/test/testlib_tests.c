#include "minunit.h"
#include "../src/fact.h"
#include "../src/sinus.h"
#include <assert.h>

char *test_create()
{
  int factorial;
  factorial = fact(2);

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_create);

  return NULL;

}

RUN_TESTS(all_tests);
