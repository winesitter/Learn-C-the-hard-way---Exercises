#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;

  // go through each string in argv
  for (i = 0; i<argc; i++){
    printf("Argv[%d]: %s\n", i, argv[i]);
  }

  // make own array of strings
  char *states[] = {
    "Rheinland-Pfalz", "Baden-Wuerttemberg",
    "Hessen", NULL, "Berlin"
  };
  
  int num_states = 5;
  printf("Num states: %d\n", num_states);

  for (i = -1; i < num_states-1; i++, printf("state[%d]: %s\n", i, states[i])){
  }


}
