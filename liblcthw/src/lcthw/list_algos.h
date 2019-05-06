#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <lcthw/list.h>


/***************************************************************
* Function pointer to compare function
***************************************************************/
typedef int (*List_compare) (const void *a, const void *b);


/***************************************************************
* Function for swapping the values of two nodes in a 
* list structure
***************************************************************/
static inline void ListNode_swap(ListNode *a, ListNode *b);

/***************************************************************
* Function for merging two lists 
***************************************************************/
static inline List *List_merge(List *left, List *right, 
                               List_compare cmp);

/***************************************************************
* Bubble sort algorithm
***************************************************************/
int List_bubble_sort(List *list, List_compare cmp);

/***************************************************************
* Merge sort algorithm
***************************************************************/
List *List_merge_sort(List *list, List_compare cmp);


#endif /* lcthw_List_algos_h */
