#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


/**************************************************
 * Function: die
 * ------------------------------------------------
 * Quits the program and prints out an error 
 * function to the user
 *************************************************/
void die(const char *message)
{
  if(errno){
    /*----------------------------------------
     * perror: prints a system error message
     *--------------------------------------*/
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }
  exit(1);
}

/***************************************************
 * Define typedef for a function pointer
 **************************************************/
typedef int (*compare_cb) (int a, int b);



/**************************************************
 * Function: bubble_sort
 * ------------------------------------------------
 * A classic bubble sort function that uses the 
 * compare_cb to do the sorting
 *
 * Bubble sort algorithm:
 * Go from left to right through the array, 
 * Compare the actual element with its right 
 * neighbour. If the neighbour element is larger,
 * switch it to the left.
 *************************************************/
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
  int temp = 0;
  int i    = 0;
  int j    = 0;
  int *target = malloc(count * sizeof(int));

  if (!target)
    die("Memory Error");

  /*----------------------------------------
   * memcpy: copies <count * sizeof(int)> 
   * bytes from memory area <numbers> to
   * memory area <target>
   *--------------------------------------*/
  memcpy(target, numbers, count * sizeof(int));

  
  /*----------------------------------------
   * Bubble sort algorithm:
   *--------------------------------------*/
  for (i = 0; i < count; i++){
    for (j = 0; j < count - 1; j++){
      if (cmp(target[j], target[j+1]) > 0){
        temp = target[j+1];
        target[j+1] = target[j];
        target[j] = temp;
      }
    }
  }
  return target;
}


/**************************************************
 * function: sorted_order
 * ------------------------------------------------
 * Comparison function for bubble_sort function.
 * Returns  1, if a is larger than b
 * Returns -1, if a is smaller than b
 *************************************************/
int sorted_order(int a, int b)
{
  return (a > b) - (a < b);
}

/**************************************************
 * function: reverse_order
 * ------------------------------------------------
 * Comparison function for bubble_sort function.
 * Returns  1, if a is smaller than b
 * Returns -1, if a is larger than b
 *************************************************/
int reverse_order(int a, int b)
{
  return (a < b) - (a > b);
}

/**************************************************
 * function: strange_order
 * ------------------------------------------------
 * Comparison function for bubble_sort function.
 * Returns 0 if a or b equal 0, otherwise
 * it returns a modulo b
 *************************************************/
int strange_order(int a, int b)
{
  if (a == 0 || b == 0) {
   return 0;
  } else {
    return a % b;
  }
}


/**************************************************
 * function: test_sorting
 * ------------------------------------------------
 * Function is doing the bubble_sort and prints 
 * it out.
 *************************************************/
void test_sorting(int *numbers, int count, compare_cb cmp)
{ 
  int i = 0;
  int *sorted = bubble_sort(numbers, count, cmp);

  if (!sorted)
    die("Failed to sort as requested.");

  for (i = 0; i < count; i++) {
    printf("%d ", sorted[i]);
  }
  printf("\n");

  free(sorted);

  /*----------------------------------------
   * Print the raw assembler code of the 
   * function in hexadecimal numbers 
   *--------------------------------------*/
  unsigned char *data = (unsigned char *)cmp;

  for (i = 0; i < 25; i++) {
    printf("%02x:", data[i]);
  }

  printf("\n");
  


}


/**************************************************
 * function: main
 * ------------------------------------------------
 * The main function
 *************************************************/
int main(int argc, char *argv[])
{
  if (argc < 2)
    die("USAGE: ex18 4 3 1 5 6");

  int count = argc - 1;
  int i = 0;
  char **inputs = argv + 1;

  int *numbers = malloc(count * sizeof(int));
  if (!numbers)
    die("Memory error.");

  for (i = 0; i < count; i++) {
    numbers[i] = atoi(inputs[i]);
  }
  
  printf("==== sorted order ====\n");
  test_sorting(numbers, count, NULL); //sorted_order);

  printf("==== reverse order ====\n");
  test_sorting(numbers, count, reverse_order);

  printf("==== strange order ====\n");
  test_sorting(numbers, count, strange_order);


  free(numbers);

  return 0;
}

