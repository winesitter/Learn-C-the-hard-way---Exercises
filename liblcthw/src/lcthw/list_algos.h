#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <lcthw/list.h>


/***************************************************************
* Function pointer to compare function
***************************************************************/
typedef int (*List_compare) (const void *a, const void *b);


/***************************************************************
* Bubble sort function
***************************************************************/
int List_bubble_sort(List *list, List_compare cmp);


#endif /* lcthw_List_algos_h */
