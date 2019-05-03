#include "dbg.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glob.h>

#define BUFFLEN 1024

/*-------------- Colors for printf() function --------------*/
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"




/*************************************************************
* Removes a specific character from a given string
*
* Arguments:
* ----------
*  buffer...... string with characters to replace
*  char1....... old character to replace
*  char2....... new character to store in
*  max......... size of string  (-> sizeof buffer)
*  
*************************************************************/
void charrem(char *buffer, char ch)
{
  int count0, count1;
  count0 = 0;
  count1 = 0;
  char new_buffer[BUFFLEN]; 

  while( (buffer[count0] != '\0') && (count0 < BUFFLEN) )
  {
    if ( buffer[count0] != ch )
    {
      new_buffer[count1] = buffer[count0];
      count1++;
    }
    count0++;
  }
  new_buffer[count1] = '\0';
  strcpy(buffer, new_buffer);

}

/*************************************************************
* Read a line from a file
*
* Arguments:
* ----------
*  f_in........ file to read line from
*  buffer...... string to store line in
*  max......... size of string  (-> sizeof buffer)
*************************************************************/
int read_line(FILE *f_in, char *buffer, size_t max)
{
  return fgets(buffer, max, f_in) == buffer;
}

/*************************************************************
* Read a complete logfile and print lines, which contain
* a query
*
* Arguments:
* ----------
*  logFile..... path to logFile
*  query....... query string to look for
*************************************************************/
int read_logfile(char *logFile, char *query)
{
  char *ret;

  /***********************************************************
  * Remove newline from logFile path
  ***********************************************************/
  FILE *f_in;
  charrem(logFile, '\n'); 

  /***********************************************************
  * Read the logfile line by line 
  ***********************************************************/
  if ( (f_in = fopen(logFile, "r")) != NULL )
  {
    char line[BUFFLEN];
    int i = 0;
    /* Read line by line */
    while ( read_line(f_in, line, sizeof line) )
    {
      i++;
      ret = strstr(line, query);
      if (ret)
      {
        printf(ANSI_COLOR_YELLOW "%s line %d:\t" ANSI_COLOR_RESET, logFile, i);
        int position = ret - line;
        printf("%.*s", position, line);
        printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, query); 
        printf("%s", ret + strlen(query));
      }
    }
    fclose(f_in);
    return 0;
  }
  printf("ERROR: Can't open logfile %s\n", logFile);
  return 1;
}



int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("winefind \"query\"\n");
    return 0;
  }

  /***********************************************************
  * Get list with all logfiles from glob
  ***********************************************************/
  //char *logtype = "*.c";

  int fileInd;
  int argInd;
  char logtype[BUFFLEN];
  FILE *f_in;

  if ( (f_in = fopen("logfind", "r")) != NULL )
  {
    while ( read_line(f_in, logtype, sizeof(logtype) ) )
    {
      fileInd = 0;
      argInd = 1;

      /***********************************************************
      * Remove newline from logtype string
      ***********************************************************/
      charrem(logtype, '\n'); 

      /*****************************************************************
      * GLOB_NOSPACE -> In case of running out of memory
      * GLOB_NOMATCH -> In case of no match                        
      ****************************************************************/
      glob_t globlist;

      if (glob(logtype, GLOB_PERIOD, NULL, &globlist) == GLOB_NOSPACE) {
        printf("ERROR: Running out of memory because of %s files\n", logtype);
        return 0;
      }
      if (glob(logtype, GLOB_PERIOD, NULL, &globlist) == GLOB_NOMATCH) {
        //printf("No match found for %s files\n", logtype);
        continue;
      }
      if (glob(logtype, GLOB_PERIOD, NULL, &globlist) == GLOB_ABORTED) {
        printf("ERROR: Read error for %s files\n", logtype);
        continue;
      }

      /*****************************************************************
      * Loop over all files that have been found by glob in current 
      * directory
      ****************************************************************/
      while (globlist.gl_pathv[fileInd]) 
      {
        read_logfile(globlist.gl_pathv[fileInd], argv[argInd]);
        fileInd++;
      }

      /*****************************************************************
      * Free globlist
      ****************************************************************/
      globfree(&globlist);

    }
    fclose(f_in);
  }




  /***********************************************************
  * Read the logfile list 
  ***********************************************************
  FILE *f_in;

  for (i = 1; i < argc; i++)
    if ( (f_in = fopen("logfind", "r")) != NULL )
    {
      char line[BUFFLEN];

      // Read line by line 
      while ( read_line(f_in, line, sizeof line) )
        read_logfile(line, argv[i]);
      
      fclose(f_in);
    }
  */
  
  return 0;
}
