#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAMELEN 100

/*---------------------------------------------------------------------
 * Person struct
 *-------------------------------------------------------------------*/
struct Person{
  char name[MAXNAMELEN];
  int age;
  int height;
  int weight;
};

/*---------------------------------------------------------------------
 * Function to create person
 *-------------------------------------------------------------------*/
struct Person Person_create(char *name, int age, int height, int weight)
{
  struct Person who;
  int namelen = sizeof(name) / sizeof(char);

  int i = 0;
  for (i = 0; i<=namelen; i++){
    who.name[i] = name[i];
  }
  who.age = age;
  who.height = height;
  who.weight = weight;
  return who;
}


/*---------------------------------------------------------------------
 * Function to print person data
 *-------------------------------------------------------------------*/
void Person_print(struct Person who)
{
  printf("Name: %s \n", who.name);
  printf("Age: %d \n", who.age);
  printf("Height: %d \n", who.height);
  printf("Weight: %d \n", who.weight);
}

/*---------------------------------------------------------------------
 * Main Function
 *-------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
  struct Person joe = Person_create("Joe", 10, 50, 160);

  Person_print(joe);

  joe.height = 1000;

  Person_print(joe);

  printf("Finished\n");


  return 0;

}

