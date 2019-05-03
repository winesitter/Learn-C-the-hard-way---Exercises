#include <stdio.h>

int main(int argc, char *argv[])
{
  if (argc != 2){
    printf("ERROR: You need one argument.\n");
    // This is how to abort a program
    return 1;
  }

  int i = 0;
  for (i = 0; argv[1][i] != '\0'; i++){
    char letter = argv[1][i];

    switch (letter) {
      
      case 'a':
      case 'A':
        printf("%d: %c - ASCII numer: %d \n", i, letter, letter);
        break;

      case 'e':
      case 'E':
        printf("%d: %c - ASCII numer: %d \n", i, letter, letter);
        break;

      case 'i':
      case 'I':
        if (i > 2){
          printf("%d: %c - ASCII numer: %d \n", i, letter, letter);
        }
        break;

      case 'o':
      case 'O':
        printf("%d: %c - ASCII numer: %d \n", i, letter, letter);
        break;

      case 'u':
      case 'U':
        printf("%d: %c - ASCII numer: %d \n", i, letter, letter);
        break;


      default: 
        printf("%d: %c is not a vowel.\n", i, letter);

    }

  }



}
