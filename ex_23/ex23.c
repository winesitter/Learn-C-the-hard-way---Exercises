#include <stdio.h>
#include <string.h>
#include "dbg.h"



/***********************************************
 * Function: normal_copy
 * ---------------------------------------------
 * Copies <count> chars <from> to <to>
 **********************************************/
int normal_copy(char *from, char *to, int count)
{
  int i = 0;

  for (i = 0; i < count; i++) {
    to[i] = from[i];
  }

  return i;
}



/***********************************************
 * Function: duffs_device
 * ---------------------------------------------
 * Copies <count> chars <from> to <to>
 **********************************************/
int duffs_device(char *from, char *to, int count)
{
  {
    int n = (count + 7) / 8;

    switch (count % 8) {
      case 0:
        do {
          *to++ = *from++;
          case 7:
          *to++ = *from++;
          case 6:
          *to++ = *from++;
          case 5:
          *to++ = *from++;
          case 4:
          *to++ = *from++;
          case 3:
          *to++ = *from++;
          case 2:
          *to++ = *from++;
          case 1:
          *to++ = *from++;
        } while (--n > 0);
    }
  }

  return count;
}



/***********************************************
 * Function: zeds_device
 * ---------------------------------------------
 * Copies <count> chars <from> to <to>
 **********************************************/
int zeds_device(char *from, char *to, int count)
{
  {
    int n = (count + 7) / 8;

    switch (count % 8) {
      case 0:
again:  *to++ = *from++;

      case 7:
        *to++ = *from++;
      case 6:
        *to++ = *from++;
      case 5:
        *to++ = *from++;
      case 4:
        *to++ = *from++;
      case 3:
        *to++ = *from++;
      case 2:
        *to++ = *from++;
      case 1:
        *to++ = *from++;
        if (--n > 0)
          goto again;
    }
  }
  return count;
}


/***********************************************
 * Function: valid_copy
 * ---------------------------------------------
 * Validates, if <count> chars in <data> are
 * the same character as <expects>
 **********************************************/
int valid_copy(char *data, int count, char expects)
{
  int i = 0;
  for(i = 0; i < count; i++) {
    if(data[i] != expects) {
      log_err("[%d] %c != %c", i, data[i], expects);
      return 0;
    }
  }

  return 1;
}




/***********************************************
 * Function: main
 * ---------------------------------------------
 * The main function
 **********************************************/
int main(int argv, char *argc[])
{
  char from[1000] = { 'a' };
  char to[1000]   = { 'c' };
  int rc = 0;

  /***************************************
   * setup the from to have some stuff
   * -------------------------------------
   * memset: fill memory with a constant 
   * byte
   * memset(void *s, int c, size_t n)
   * fill first n bytes of the memory
   * area pointed to by s with the
   * constant byte c
   **************************************/
  memset(from, 'x', 1000);

  /***************************************
   * set it to a failure mode
   **************************************/
  memset(to, 'y', 1000);
  check(valid_copy(to, 1000, 'y'), "Not initialized right.");

  /***************************************
   * use normal copy to
   **************************************/
  rc = normal_copy(from, to, 1000);
  check(rc == 1000, "Normal copy failed: %d", rc);
  check(valid_copy(to, 1000, 'x'), "Normal copy failed.");

  /***************************************
   * Reset
   **************************************/
  memset(to, 'y', 1000);

  /***************************************
   * duff's device
   **************************************/
  rc = duffs_device(from, to, 1000);
  check(rc == 1000, "Duff's device failed: %d", rc);
  check(valid_copy(to, 1000, 'x'), "Duff's device failed to copy");

  /***************************************
   * Reset
   **************************************/
  memset(to, 'y', 1000);

  /***************************************
   * zed's device
   **************************************/
  rc = zeds_device(from, to, 1000);
  check(rc == 1000, "Zeds's device failed: %d", rc);
  check(valid_copy(to, 1000, 'x'), "Zed's device failed to copy");




  return 0;

error:
  return -1;

}
