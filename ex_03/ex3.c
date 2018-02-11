#include <stdio.h>

int main()
{
  int age = 10;
  int height = 12;

  printf("I am %d years old.\n", age);
  printf("I am %d inches tall.\n", height);


  /*-----------------------------------------------------
   | Escape sequences in C
   ----------------------------------------------------*/
  printf("Newline characters: \n");
  printf("Another possibility for a new line is %%c.%c", 0x0a);
  printf("\\a makes a beep sound. \a \n");
  printf("\\t makes \t a horizontal tabstop.\n");
  printf("\\v makes \v a vertical tabstop.\n");
  printf("This\vis\vnice\vfor\vprinting\vstuff!\n");
  printf("\n\nThis is \f a form feed. \n");
  printf("Form\fFeed\fForm\fFeed.\n");
  printf("This is a backspace - \bbackspace\n");
  printf("Single quote\', double quote\'' \n");
  printf("A null character \\0 terminates the string\n.");
  printf("Carriage control \r test test \n");

  return 0;
}
