#include "dbg.h"
#include <stdlib.h>
#include <stdio.h>

/***************************************************
 * Function: test_debug
 * -------------------------------------------------
 * Function to test the debug macro
 **************************************************/
void test_debug()
{
  // notice you dont need the \n
  debug("I have brown hair.");

  // passing in arguments like printf, because
  // of the ##__VA_ARGS__
  debug("I am %d years old.", 26);
}

/***************************************************
 * Function: test_log_err
 * -------------------------------------------------
 * Function to test the log_err macro
 **************************************************/
void test_log_err()
{
  log_err("I believe everything is broken.");
  log_err("There are %d problems in %s.", 99, "your code");
}


/***************************************************
 * Function: test_log_warn
 * -------------------------------------------------
 * Function to test the log_warn macro
 **************************************************/
void test_log_warn()
{
  log_warn("You can safely ignore this.");
  log_warn("Maybe consider looking at: %s.", "/etc/password");
}


/***************************************************
 * Function: test_log_info
 * -------------------------------------------------
 * Function to test the log_info macro
 **************************************************/
void test_log_info()
{
  log_info("Well I did something mondane.");
  log_info("It happened %d times doday.", 8);
}



/***************************************************
 * Function: test_check
 * -------------------------------------------------
 * Function to test the macro <check_mem> and 
 * <check>
 **************************************************/
int test_check(char *file_name)
{
  FILE *input = NULL;
  char *block = NULL;

  block = malloc(100);
  check_mem(block);

  input = fopen(file_name, "r");
  check(input, "Failed to open %s.", file_name);

  free(block);
  fclose(input);
  return 0;

error:
  if (block) free(block);
  if (input) fclose(input);
  return -1;

}


/***************************************************
 * Function: test_sentinel
 * -------------------------------------------------
 * Function to test sentinel macro 
 **************************************************/
int test_sentinel(int code)
{
  char *temp = malloc(100);
  check_mem(temp);

  switch(code) {
    case 1:
      log_info("It worked.");
      break;
    default:
      sentinel("I shouldn't run.");
  }
  free(temp);
  return 0;

error:
  printf("Go to error label.\n");
  if(temp)
    free(temp);
  return -1;
}


/***************************************************
 * Function: test_check_mem
 * -------------------------------------------------
 * Function to test the check_mem macro
 **************************************************/
int test_check_mem()
{
  char *test = NULL;
  check_mem(test);

  free(test);
  return 1;

error:
  return(-1);
}



/***************************************************
 * Function: test_check_debug
 * -------------------------------------------------
 * Function to test the check_debug macro
 **************************************************/
int test_check_debug()
{
  int i = 0;
  check_debug(i != 0, "Oops, I was 0.");
  return 0;

error:
  return -1;
}


/***************************************************
 * Function: main
 * -------------------------------------------------
 * The main function
 **************************************************/
int main(int argc, char *argv[])
{
  check(argc == 2, "Need an argument.");

  test_debug();
  test_log_err();
  test_log_warn();
  test_log_info();
  check(test_check("testfile.dat") == 0, "failed with ex20.c");
  check(test_check(argv[1]) == -1, "failed with argv[1]");
  test_sentinel(0);
  test_check_mem();
  test_check_debug();

  return 0;


error:
  return -1;
}
