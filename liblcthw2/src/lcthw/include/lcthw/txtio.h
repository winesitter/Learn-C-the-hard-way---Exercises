#ifndef _lcthw_Txtio_h
#define _lcthw_Txtio_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <lcthw/bstrlib.h>

#define FILIO_ERR -1

/*************************************************************
* Txtio structure
*************************************************************/
struct Txtio;
typedef struct Txtio {
  bstring          path;    /* Path of file                 */
  bstring          txt;     /* bstring with file data       */
  struct bstrList *txtlist; /* file, splitted for newlines  */

  long             length;  /* Number of chars in total file*/
                            /* -> including '\0' at end     */


} Txtio;

/*************************************************************
* Function to create a new file reader structure
*************************************************************/
Txtio *Txtio_create(bstring file_path);

/*************************************************************
* Function to destroy a file reader structure
*************************************************************/
int Txtio_destroy(Txtio *file);



#endif
