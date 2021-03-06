#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100



/****************************************
 * Function: read_string
 * --------------------------------------
 * 
 ***************************************/
int read_string(char **out_string, int max_buffer)
{
  *out_string = calloc(1, max_buffer +1);
  check_mem(*out_string);

  char *result = fgets(*out_string, max_buffer, stdin);
  check(result != NULL, "Input error.");
  return 0;

error:
  if (*out_string) free(out_string);
  *out_string = NULL;
  return -1;
}


/****************************************
 * Function: read_int
 * --------------------------------------
 * 
 ***************************************/
int read_int(long *out_int)
{
  char *input = NULL;
  char *end   = NULL;
  int rc = read_string(&input, MAX_DATA);
  check(rc == 0, "Failed to read number");

  *out_int = strtol(input, &end, 10);
  check((*end == '\0' || *end == '\n') &&
      *input != '\0', "Invalid number: %s", 
      input);
  free(input);
  return 0;
error:
  free(input);
  return -1;
}



/****************************************
 * Function: read_scan
 * --------------------------------------
 * 
 ***************************************/
int read_scan(const char *fmt, ...) 
{
  int i  = 0;
  int rc = 0;
  long *out_int  = NULL;
  char *out_char = NULL;
  char **out_string = NULL;
  int max_buffer = 0;


  /* -- variable argument list -- */
  va_list argp;
  /*------------------------------------*
   * va_start(va_list ap, last):
   * Initializes ap for subsequent use by
   * va_arg() and va_end() and must be 
   * called first.
   * The argument <last> is the last 
   * argument before the variable 
   * argument list.
   *------------------------------------*/
  va_start(argp, fmt);

  for (i = 0; fmt[i] != '\0'; i++) {
    if (fmt[i] == '%') {
      i++;
      switch (fmt[i]) {
        case '\0':
          sentinel("Invalid format, you ended with %%.");
          break;

        case 'd':
          /*------------------------------------*
           * Return the next variable argument 
           * and change argp, that in the next
           * call of va_arg a new arugment is
           * returned
           *------------------------------------*/
          out_int = va_arg(argp, long *);
          rc = read_int(out_int);
          check(rc == 0, "Failed to read int.");
          break;
          
        case 'c':
          out_char = va_arg(argp, char *);
          *out_char = fgetc(stdin);
          break;

        case 's':
          max_buffer = va_arg(argp, int);
          out_string = va_arg(argp, char **);
          rc = read_string(out_string, max_buffer);
          check(rc == 0, "Failed to read string.");
          break;

        default:
          sentinel("Invalid format.");
      }
    } else {
      fgetc(stdin);
    }

    check(!feof(stdin) && !ferror(stdin), "Input error");
  }

  va_end(argp);
  return 0;

error:
  va_end(argp);
  return -1;
}

/****************************************
 * Function: main
 * --------------------------------------
 * The main function
 ***************************************/
int main(int argc, char *argv[])
{
  char *first_name = NULL;
  char initial = ' ';
  char *last_name = NULL;
  long age = 0;
  int rc;

  printf("What is your first name? ");
  rc = read_scan("%s", MAX_DATA, &first_name);
  check(rc == 0, "Failed to read first name.");

  printf("What is your initial? ");
  rc = read_scan("%c\n", &initial);
  check(rc == 0, "Failed to read initial.");

  printf("Whats your last name? ");
  rc = read_scan("%s", MAX_DATA, &last_name);
  check(rc == 0, "Failed to read last name.");

  printf("How old are you? ");
  rc = read_scan("%d", &age);
  check(rc == 0, "Failed to read age.");

  printf("===== Results =====\n");
  printf("First name: %s", first_name);
  printf("Initial: '%c'\n", initial);
  printf("Last name: %s", last_name);
  printf("Age: %ld\n", age);

  free(first_name);
  free(last_name);

  return 0;
error:
  return -1;
}
