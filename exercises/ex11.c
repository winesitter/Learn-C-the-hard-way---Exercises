#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int numbers[4] = { 0 };
  char name[4] = { 'a'};

  // first print them out raw
  printf("Numbers: %d %d %d %d\n",
          numbers[0], numbers[1], numbers[2], numbers[3]);

  printf("Name each: %c %c %c %c\n",
          name[0], name[1], name[2], name[3]);
  
  printf("Name: %s\n", name);

  // setup the numbers
  numbers[0] = 1;
  numbers[1] = 2;
  numbers[2] = 3;
  numbers[3] = 4;

  // setup the name
  name[0] = 'Z';
  name[1] = 'e';
  name[2] = 'd';
  name[3] = '\0';
  
  // then print them out initialized
  printf("numbers: %d %d %d %d\n",
          numbers[0], numbers[1], numbers[2], numbers[3]);
          
  printf("Name each: %c %c %c %c\n",
          name[0], name[1], name[2], name[3]);
  
  printf("Name: %s\n", name);

  // another way to use the name
  char *another = "Zed";

  printf("another: %s\n", another);
  
  printf("another each: %c %c %c %c\n",
          another[0], another[1], another[2], another[3]);



  printf("=======================\n");
  printf("Crazy hack \n");
  printf("=======================\n");
  // Array of 4 chars is 4 bytes long
  char char_4byte[4] = {'a','a','a','a'};
  // an integer is 4 bytes long
  int int_4byte = 11;

  // Trean char as an integer
  printf("Char as integer: %d \n", char_4byte);
  printf("Char as integer +11: %d \n", (char_4byte + int_4byte));

  // using memcpy:
  int a;
  char b[4] = {'a', 'a', 'a', 'a'};
  memcpy(b,a,sizeof(int));
  printf("b: %s\n", b);

}
