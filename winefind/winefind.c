#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glob.h>

#define BUFFLEN 1024
#define LOGFIND "~/.logfind"

/*-------------- Colors for printf() function --------------*/
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"




char *concat(char *str_1, char *str_2)
{
  // + 1 for null terminator
  char *newStr = malloc(strlen(str_1) + strlen(str_2) + 1);  
  strcpy(newStr, str_1);
  strcat(newStr, str_2);
  return newStr;
}

/*************************************************************
* Digs through all directories and sub-directories of the
* current location and returns their path as a string
* in the globlist.
*
* Arguments:
* ----------
*  globlist.........glob struct, containing all paths
*  query............query term to search for 
*  init.............flag - set to 1 for initialization
*  
*************************************************************/
int get_globlist(glob_t *globlist, char *query, int globFlags)
{
  int status;

  /*************************************************************
  * Read all files and directories
  *************************************************************/
  status = glob(query, globFlags, NULL, globlist);

  /*************************************************************
  * Error handling
  *************************************************************/
  if (status == GLOB_NOSPACE) 
  {
    printf("ERROR: Query %s needs too much memory.\n", query);
    return status;
  }
  else if (status == GLOB_NOMATCH) 
  {
    //printf("FAILURE: No match found query %s.\n", query);
    return status;
  }
  else if (status == GLOB_ABORTED) 
  {
    printf("ERROR: Can not read files for query %s\n", query);
    return status;
  }

  /*************************************************************
  * Recursive handling of directories
  *************************************************************/
  int i=0;
  while (globlist->gl_pathv[i]) 
  {
    char *path = globlist->gl_pathv[i];
    int len    = strlen(path);

    if ( strcmp(&path[len - 1], "/") == 0 )
    {
      char *newQuery = concat(path, query);
      get_globlist(globlist, newQuery, globFlags | GLOB_APPEND);
      free(newQuery);
    }

    i++;
  }

  return status;
}


/*************************************************************
* Removes a specific character from a given string
*
* Arguments:
* ----------
*  buffer...... string with characters to replace
*  ch.......... character to remove from buffer
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
        printf(ANSI_COLOR_YELLOW "%s line %d: " ANSI_COLOR_RESET, logFile, i);
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



/*************************************************************
* The main function
*************************************************************/
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
  int fileInd, dirInd;
  int argInd;
  char logtype[BUFFLEN];
  FILE *f_in;

  glob_t globlist;
  get_globlist(&globlist, "*", GLOB_TILDE | GLOB_MARK | GLOB_ONLYDIR);

  if ( (f_in = fopen(LOGFIND, "r")) != NULL )
  {
    while ( read_line(f_in, logtype, sizeof(logtype) ) )
    {
      dirInd = 0;
      argInd = 1;

      /***********************************************************
      * Remove newline from logtype string
      ***********************************************************/
      charrem(logtype, '\n'); 

      while ( globlist.gl_pathv[dirInd] )
      {
        /***************************************************************
        * Find paths to all files with respective query type
        ***************************************************************/
        glob_t globFiles;
        char *fileQuery = concat(globlist.gl_pathv[dirInd], logtype);

        get_globlist(&globFiles, fileQuery, GLOB_TILDE | GLOB_MARK );
        free(fileQuery);
        dirInd++;

        /***************************************************************
        * Loop over all files that have been found by glob in current 
        * directory
        ***************************************************************/
        fileInd = 0;
        if (globFiles.gl_pathc > 0)
          while (globFiles.gl_pathv[fileInd]) 
          {
            read_logfile(globFiles.gl_pathv[fileInd], argv[argInd]);
            fileInd++;
          }
        /***************************************************************
        * Free globlist
        **************************************************************/
        globfree(&globFiles);
      }
    }

    fclose(f_in);

    /*****************************************************************
    * Free globlist
    ****************************************************************/
    globfree(&globlist);
  }
  printf("\n");

  
  return 0;
}




      /*
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
      */
