#include <stdio.h>

int main(int argc, char *argv[])
{
  char full_name[] = {
    'Z','e','d',' ',
    'A','.',' ',
    'S','h','a','w'};
  int areas[] = {10, 12, 14, 16 ,18};
  char name[] = "Zed";

  printf("The size of an int: %ld\n", sizeof(int));
  printf("The size of areas (int[]): %ld\n", sizeof(areas));
  printf("The number of ints in areas: %ld\n",
          sizeof(areas) / sizeof(int));
  printf("The first area is %d, the second area is %d\n", 
          areas[0], areas[1]);

  printf("The size of an char: %ld\n", sizeof(char));
  printf("The size of name (char[]): %ld\n", sizeof(name));
  printf("The number of chars in name: %ld\n",
          sizeof(name) / sizeof(char));

  printf("The size of full_name (char[]): %ld\n", sizeof(full_name));
  printf("The number of chars in full_name: %ld\n",
          sizeof(full_name) / sizeof(char));

  printf("Name %s and full name %s\n", name, full_name);
}
