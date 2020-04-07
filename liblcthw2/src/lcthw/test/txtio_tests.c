#include <lcthw/minunit.h>
#include <lcthw/txtio.h>
#include <lcthw/bstrlib.h>
#include "txtio_tests.h"

const char *testfile = "/home/florian/datadisk/Code/learn-C-the-hard-way/liblcthw2/src/lcthw/test/data/filio_test.txt";

/*************************************************************
* Unit test function to handle creation and 
* destruction of bstrings
*************************************************************/
char *test_txtio_readfile()
{
  printf("Reading file: %s\n", testfile);

  bstring file_path = bfromcstr( testfile );

  Txtio* file = Txtio_create( file_path );


  printf("\n%s\n", file->txt->data);


  int i;
  bstring *txt_ptr = file->txtlist->entry;
  for (i = 0; i < file->txtlist->qty; i++)
    printf("%3d: %s\n", i, txt_ptr[i]->data);


  Txtio_destroy( file );

  printf("\nDONE\n\n");

  return NULL;
}
