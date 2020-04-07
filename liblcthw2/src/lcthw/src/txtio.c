#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <lcthw/dbg.h>
#include <lcthw/txtio.h>
#include <lcthw/bstrlib.h>



/*************************************************************
* Function to create a new file reader
*
* Reference:
* https://stackoverflow.com/questions/14002954/c-programming-how-to-read-the-whole-file-contents-into-a-buffer
*************************************************************/
Txtio *Txtio_create(bstring file_path)
{
  /*---------------------------------------------------------
  | Allocate memory for txtio structure 
  ---------------------------------------------------------*/
  Txtio *txtfile = calloc(1, sizeof(Txtio));
  check_mem(txtfile);

  txtfile->path = file_path;

  /*---------------------------------------------------------
  | Open text file and copy its data 
  ---------------------------------------------------------*/
  FILE *fptr = NULL;
  fptr = fopen(txtfile->path->data, "rb");
  check(fptr, "Failed to open %s.", txtfile->path->data);

  /* Estimate length of chars in whole file                */
  fseek(fptr, 0, SEEK_END);
  long length = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);

  /* Read total file into buffer                           */
  char *buffer = (char *) malloc(length + 1);
  buffer[length] = '\0';
  fread(buffer, 1, length, fptr);

  /* Copy relevant data to Txtio structure                 */
  bstring bbuffer = bfromcstr( buffer );
  txtfile->txt    = bbuffer;
  txtfile->length = length + 1;

  /* Split buffer according to newlines                    */
  char splitter = '\n';
  txtfile->txtlist = bsplit(bbuffer, splitter);

  fclose(fptr);
  free(buffer);

  return txtfile;
error:
  return NULL;
}


/*************************************************************
* Function to destroy a file reader structure
*************************************************************/
int Txtio_destroy(Txtio *file)
{
  bstrListDestroy(file->txtlist);
  bdestroy(file->txt);
  bdestroy(file->path);
  free(file);
  return 0;
}
  

