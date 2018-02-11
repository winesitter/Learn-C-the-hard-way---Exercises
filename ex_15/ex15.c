#include <stdio.h>
#include <string.h>
#include <math.h>


int main(int argc, char *argv[])
{
  int ages[] = { 23, 43, 12, 89, 2 };
  char *names[] = {
    "Frank", "Anne", "Klaus", "Peter", "Heinz"
  };

  // get the size of ages
  int count = sizeof(ages) / sizeof(int);
  int i = 0;

  // first way using indexing
  for (i = 0; i < count; i++){
    printf("%s has %d years alive.\n", names[i], ages[i]);
  }

  printf("====\n");


  // setup the pointers to the start of arrays
  int *cur_age = ages;
  char **cur_name = names;

  // second way usig pointers
  for (i = 0; i < count; i++){
    printf("%s is %d years old \n",
            *(cur_name + i), *(cur_age + i));
  }

  printf("====\n");

  // third way, pointers are just an array
  for (i = 0; i < count; i++){
    printf("%s is %d years old again \n", cur_name[i], cur_age[i]);
  }
  printf("====\n");

  // stupid way to use pointers
  for (cur_name = names, cur_age = ages;
       (cur_age - ages) < count; cur_name++, cur_age++) {
    printf("%s lived %d years on this planet\n", *cur_name, *cur_age);
  }

  return 0;

}
