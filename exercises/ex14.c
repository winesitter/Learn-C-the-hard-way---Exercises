#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declaration
int can_print_it(char ch);
void print_letters(char arg[], int slen);

void print_arguments(int argc, char *argv[])
{
  int i = 0;

  for (i = 0; i < argc; i++){
    int slen = strlen(argv[i]);
    print_letters(argv[i], slen);
  }

}

void print_letters(char arg[], int slen)
{
  int i = 0;

  for (i = 0; i < slen; i++){
    char ch = arg[i];

    if (can_print_it(ch)){
      printf("'%c' == %d ", ch, ch);
    }
  }
  printf("\n");
}


int can_print_it(char ch)
{ 
  return isalpha((int)ch) || isblank((int)ch);
}


int main(int argc, char *argv[])
{
  print_arguments(argc, argv);
  return 0;
}
