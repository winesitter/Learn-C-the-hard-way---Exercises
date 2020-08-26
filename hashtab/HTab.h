/*
 * HTab is a simple hash table data structure written in C.
 * It is based on the code given in "K&R". 
 *
 * This code was written by Florian Setzwein in 2020, 
 * and is covered under the MIT License.
 * Refer to the accompanying documentation for details
 * on usage and license.
*/
#ifndef HTAB_H
#define HTAB_H

/***********************************************************
* Globals
***********************************************************/
#define HTAB_HASHSIZE 101
#define HTAB_SUCCESS 0
#define HTAB_ERROR -1

/***********************************************************
* Structs
***********************************************************/
typedef struct HTabEntry HTabEntry;
typedef HTabEntry* HTab;

/***********************************************************
* Struct: HTabEntry
*-----------------------------------------------------------
* This structure holds a dictionary entry
***********************************************************/
typedef struct HTabEntry {
  HTabEntry *next;         /* next entry in chain  */  
  char       *key;         /* key for dict entry   */
  void       *val;         /* value for dict entry */
} HTabEntry;

/***********************************************************
* Function: hash()
*-----------------------------------------------------------
* Forms a hash value from a given string
***********************************************************/
static inline unsigned hash(char *s)
{
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HTAB_HASHSIZE;
}



/***********************************************************
* Function: HTab_create()
*-----------------------------------------------------------
* Creates a new dictionary
***********************************************************/
HTab *HTab_create(void);

/***********************************************************
* Function: HTab_destroy()
*-----------------------------------------------------------
* Frees the memory of a given dictionary
***********************************************************/
void HTab_destroy(HTab *htab);

/***********************************************************
* Function: HTab_get()
*-----------------------------------------------------------
* This function looks for an entry of a give key s in a
* HTab structure
***********************************************************/
HTabEntry *HTab_get(char *s, HTab *htab);

/***********************************************************
* Function: HTab_add()
*-----------------------------------------------------------
* Add a (key, val) pair to a hashtab
***********************************************************/
HTabEntry* HTab_add(char *key, void *val, HTab *htab);

/***********************************************************
* Function: HTab_remove()
*-----------------------------------------------------------
* Removes a (key, val) pair from a hashtab and returns 
* the respective entry.
***********************************************************/
HTabEntry* HTab_remove(char *key, HTab *htab);

/***********************************************************
* Function: HTab_delete()
*-----------------------------------------------------------
* Removes a (key, val) pair from a hashtab and frees its 
* memory.
***********************************************************/
int HTab_delete(char *key, HTab *htab);

#endif
