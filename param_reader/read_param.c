#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define OCT_MAX_LINE_LEN     512
#define OCT_MAX_FILENAME_LEN 1024

#define STRING_PARAM          0 /* Arbitrary string value parameter         */
#define INTEGER_PARAM         1 /* Integer value parameter                  */
#define DOUBLE_PARAM          2 /* Double value parameter                   */
#define INTEGER_ARRAY_PARAM   3 /* Space-separated integer values parameter */
#define DOUBLE_ARRAY_PARAM    4 /* Space-separated double values parameter  */
#define STRING_ARRAY_PARAM    5 /* Space separated string values parameter  */
#define HEADER_PARAM_DUMMY    6 /* Dummy parameter to print header          */


/***********************************************************
* Container for IO parameter
***********************************************************/
typedef struct FileIoParam
{
  char grid_file[OCT_MAX_FILENAME_LEN + 1];
  char restart_prefix[OCT_MAX_FILENAME_LEN + 1];
  char output_prefix[OCT_MAX_FILENAME_LEN + 1];

} FileIoParam_t;

/***********************************************************
* Container for timestep parameters 
***********************************************************/
typedef struct TimeParam
{

  double timestep;
  int    max_no_timesteps;
  int    output_period;

} TimeParam_t;


/***********************************************************
* Structure defining a parameter
***********************************************************/
typedef struct Parameters
{
  const char *key; /* Key for parameter used in parameter file */
  const int type; /* Type of parameter used in parameter file */

  int specified; /* Boolean, if the value must be specified of not */
  void *value; /* Pointer to data with correct type, required */
  
  int no; /* Number of entries if the parameter is a list */

} Parameters_t;


/***********************************************************
* 
***********************************************************/
FileIoParam_t file_para;
TimeParam_t   time_para;

/***********************************************************
* All File/IO parameter definitions
***********************************************************/
static Parameters_t parameter_file_io[] = 
{
  /*------------------------------------------------------*/
  {"Files/IO", HEADER_PARAM_DUMMY, FALSE, NULL },
  /*------------------------------------------------------*/
  {
    "Grid filename", STRING_PARAM,
    TRUE, file_para.grid_file
  },
  {
    "Output files prefix", STRING_PARAM,
    TRUE, file_para.output_prefix
  },
  {
    "Restart-data prefix", STRING_PARAM,
    FALSE, file_para.restart_prefix
  }
}; /* parameter_file_io[] */


/***********************************************************
* All temporal parameter definitions
***********************************************************/
static Parameters_t parameter_time[] = 
{
  /*------------------------------------------------------*/
  {"Time parameters", HEADER_PARAM_DUMMY, FALSE, NULL },
  /*------------------------------------------------------*/
  {
    "Timestep", DOUBLE_PARAM,
    TRUE, &time_para.timestep
  },
  {
    "Maximal timestep number", INTEGER_PARAM,
    TRUE, &time_para.max_no_timesteps
  },
  {
    "Output period", INTEGER_PARAM,
    TRUE, &time_para.output_period
  } 
}; /* parameter_time[] */

/***********************************************************
* Function to read a line from a file
***********************************************************/
static char *read_line(FILE *fin) 
{
  char *buffer;
  char *tmp;

  int   read_chars = 0;
  int   bufsize    = OCT_MAX_LINE_LEN;

  char *line = malloc(bufsize);

  if ( !line ) 
    return NULL;

  buffer = line;

  while ( fgets(buffer, bufsize - read_chars, fin) )
  {
    read_chars = strlen(line);

    if ( line[read_chars - 1] == '\n' )
    {
      line[read_chars - 1] = '\0';
      return line;
    }
    else
    {
      bufsize = 2 * bufsize;
      tmp = realloc(line, bufsize);
      if (tmp)
      { line = tmp;
        buffer = line + read_chars;
      }
      else
      {
        free(line);
        return NULL;
      }
    }
  }
  return NULL;

} /* read_line() */


/***********************************************************
* Function finds parameters in a given parameter file
***********************************************************/
static char *find_parameter(FILE *fp, const char *param_key)
{
  char *line;

  while( (line = read_line(fp)) ) 
  {
    if ( strstr(line, param_key) ) 
      return line;
    else
      free(line); 
  }
  return NULL;

} /* find_parameter() */

/***********************************************************
* Function finds parameters in a given parameter file
***********************************************************/
static int get_parameter_value(char *line, Parameters_t *param)
{
  char *substr;
  char copy[OCT_MAX_LINE_LEN];

  if ( param->type == STRING_PARAM )
  {
    strcpy(copy, line);
    substr = strtok(copy, ":");
    substr = strtok(NULL, "\0");
    strcpy(param->value, substr);
  }
  else if ( param->type == INTEGER_PARAM )
  {
    strcpy(copy, line);
    substr = strtok(copy, ":");
    substr = strtok(NULL, "\0");
    *( (int*) param->value) = atoi(substr);
  }
  /*
  else if ( param->type == DOUBLE_PARAM )
  {
    strcpy(copy, line);
    substr = strtok(copy, ":");
    substr = strtok(NULL, "\0");
    param->value = atof(substr);
  }
  */

  return 0;

} /* get_parameter_value() */

/***********************************************************
* Function finds parameters in a given parameter file
***********************************************************/
static int parse_parameters(const char *parafile, Parameters_t param[])
{
  FILE *fp;
  int i;

  for (i = 0; param[i].key != NULL; i++)
  {
    if (( fp = fopen(parafile, "r") ) != NULL)
    {
      char *param_line = find_parameter(fp, param[i].key);

      if (param_line != NULL)
      {
        get_parameter_value(param_line, &param[i]);
      }
      else
      {
        printf("%s: NO PARAMETER PROVIDED\n", param[i].key);
      }

      fclose(fp);

    }
    else
    {
      printf("ERROR: Could not read parameterfile %s.\n", 
          parafile);
    }
  }

  return 0;

} /* parse_parameters() */
                          


/***********************************************************
* The main function
***********************************************************/
int main(int argc, char *argv[])
{
  const char *parafile;
  const char *logfile;

  /*--------------------------------------------------------
  | Get .para file name from argument list 
  --------------------------------------------------------*/
  if (argc != 2 && argc != 3) {
    printf("Usage: %s <parameterfile> <optional logfile>\n", 
        argv[0]);
    return -1;
  }
  parafile = argv[1];
  if (argc == 3)
    logfile = argv[2];
  else
    logfile = NULL;

  printf("Parameterfile: %s\n", parafile);
  printf("Logfile: %s\n", logfile);

  /*--------------------------------------------------------
  | Read through parameterfile
  --------------------------------------------------------*/
  parse_parameters(parafile, parameter_file_io);

  /*
  int linecount = 0;
  while (fgets(line, sizeof line, fp) != NULL)
  {
    printf("%4d| %s", linecount++, line);
  }
  */

  int i;
  for (i = 0; parameter_file_io[i].key != NULL; i++)
  {
    printf("%s: %s\n", parameter_file_io[i].key, (char *) parameter_file_io[i].value);
  }
  printf("-------------------\n");

  /*
  for (i = 0; parameter_time[i].key != NULL; i++)
  {
    int *val = (int *) parameter_time[i].value;
    printf("%s: %d\n", parameter_time[i].key, &val);
  }
  */

  return 0;

} /* main() */
