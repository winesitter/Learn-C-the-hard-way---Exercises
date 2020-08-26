/*
 * HTab is a simple hash table data structure written in C.
 * It is based on the code given in "K&R". 
 *
 * This code was written by Florian Setzwein in 2020, 
 * and is covered under the MIT License.
 * Refer to the accompanying documentation for details
 * on usage and license.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HTab.h"

/***********************************************************
* Function: HTab_create()
*-----------------------------------------------------------
* Creates a new dictionary
***********************************************************/
HTab *HTab_create(void)
{
  int i;
  HTab *htab;

  htab = (HTab*) malloc(HTAB_HASHSIZE*sizeof(HTab*));

  for (i = 0; i < HTAB_HASHSIZE; i++)
    htab[i] = NULL;

  return htab;

} /* HTab_create() */

/***********************************************************
* Function: HTab_destroy()
*-----------------------------------------------------------
* Frees the memory of a given dictionary
***********************************************************/
void HTab_destroy(HTab *htab)
{
  int i;

  for (i = 0; i < HTAB_HASHSIZE; i++)
  {
    if (htab[i] != NULL)
      free(htab[i]->key);
    free(htab[i]);
  }
  
  free(htab);

} /* HTab_destroy() */

/***********************************************************
* Function: HTab_get()
*-----------------------------------------------------------
* This function looks for an entry of a give key s in a
* HTab structure
***********************************************************/
HTabEntry *HTab_get(char *s, HTab *htab)
{
  HTabEntry *e;

  for (e = htab[hash(s)]; e != NULL; e = e->next)
    if (strcmp(s, e->key) == 0)
      return e;  /* found     */
  return NULL;    /* not found */

} /* HTab_get() */

/***********************************************************
* Function: HTab_add()
*-----------------------------------------------------------
* Add a (key, val) pair to a hashtab
***********************************************************/
HTabEntry* HTab_add(char *key, void *val, HTab *htab)
{
  HTabEntry *e;
  unsigned hashval;

  /*--------------------------------------------------------
  | If key is not found in hash table, add a new entry
  | In case of hash collision, push new entry to 
  | beginning of entry list.
  --------------------------------------------------------*/
  if ((e = HTab_get(key, htab)) == NULL) 
  {
    e = (HTabEntry *) malloc(sizeof(HTabEntry));
    
    if (e == NULL || (e->key = strdup(key)) == NULL)
      return NULL;

    hashval = hash(key);
    e->next = htab[hashval];
    htab[hashval] = e;
  }

  /*--------------------------------------------------------
  | Set new value in entry. Old values are overwritten
  --------------------------------------------------------*/
  if ((e->val = val) == NULL)
    return NULL;

  return e;

} /* HTab_add() */

/***********************************************************
* Function: HTab_remove()
*-----------------------------------------------------------
* Removes a (key, val) pair from a hashtab and returns 
* the respective entry.
***********************************************************/
HTabEntry* HTab_remove(char *key, HTab *htab)
{
  HTabEntry *e;
  unsigned hashval;

  /*--------------------------------------------------------
  | If key is not found in hash table, return NULL
  --------------------------------------------------------*/
  if ((e = HTab_get(key, htab)) == NULL) 
    return NULL;

  hashval = hash(key);
  htab[hashval] = e->next;
  e->next = NULL;

  return e;

} /* HTab_remove() */

/***********************************************************
* Function: HTab_delete()
*-----------------------------------------------------------
* Removes a (key, val) pair from a hashtab and frees its 
* memory.
***********************************************************/
int HTab_delete(char *key, HTab *htab)
{
  HTabEntry *e;

  if ((e = HTab_remove(key, htab)) == NULL)
    return HTAB_SUCCESS;

  free(e->key);
  free(e);
  return HTAB_SUCCESS;

} /* HTab_delete() */

/***********************************************************
* Function: main()
*-----------------------------------------------------------
* The main function
***********************************************************/
int main(int argc, char *argv[])
{
  (void) argc;
  (void) argv;

  HTabEntry *e;
  HTab *htab = HTab_create();

  char *key_1  = "Test_1";
  double val_1 = 1.2345;

  char *key_2 = "Test_2";
  int val_2 = 123;

  char *key_3 = "Test_3";
  char *val_3 = "ABCDE";

  HTab_add(key_1, &val_1, htab);
  e = HTab_get(key_1, htab);
  printf("e->val: %f\n", *(double*)e->val);

  HTab_add(key_1, &val_2, htab);
  printf("e->val: %d\n", *(int*)e->val);

  HTab_add(key_2, &val_2, htab);
  HTab_add(key_3, &val_3, htab);
  e = HTab_get(key_3, htab);
  printf("e->val: %s\n", *(char**)e->val);

  printf("Remove e->val: %s\n", *(char**)e->val);
  HTab_delete(key_3, htab);
  e = HTab_get(key_3, htab);
  if (e != NULL)
    printf("e is not NULL\n");
  else
    printf("Succeeded.\n");

  HTab_destroy(htab);

  return 0;
}
