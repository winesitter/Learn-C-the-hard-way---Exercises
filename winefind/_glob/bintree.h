#ifndef INCLUDE_BINTREE_H
#define INCLUDE_BINTREE_H

#include <stdlib.h>

struct TreeNode;

/********************************************
 * Binary Tree Node Structure
 *******************************************/
typedef struct TreeNode
{
  int layer;
  int count;

  struct TreeNode *next;
  struct TreeNode *prev;

  struct TreeNode *parent;
  struct TreeNode *child;

  void *value;
} TreeNode;

/***************************************************************
* Create a new bintree node
***************************************************************/
TreeNode *create_bintree_node(int layer, int count);

/***************************************************************
* Push a new neighbor node to the tree 
***************************************************************/
void push_bintree_neighbor(TreeNode *node, void *value);

/***************************************************************
* Push a new child node to the tree 
***************************************************************/
void push_bintree_child(TreeNode *node, void *value);

/***************************************************************
* Clear bintree
***************************************************************/
void free_bintree(TreeNode *node, int start);

/***************************************************************
* Find the head of the bintree, by providing any node of the
* bintree.
* The head is the first node in the first layer
* By definition, all child nodes point with their parent pointer
* to the first node node in the previous layer.
***************************************************************/
TreeNode *find_bintree_head(TreeNode *node);

/***************************************************************
* Find the bottom of the bintree, by providing a starting
* node of the bintree.
* The bottom is the first node in the last layer of a given
* starting point. Each node has a different bottom.
***************************************************************/
TreeNode *find_bintree_bottom(TreeNode *node);

/***************************************************************
* Find the first node of the current layer for a given node in 
* the bintree
***************************************************************/
TreeNode *find_bintree_first(TreeNode *node);

/*************************************************************** * Find the last node of the current layer for a given node in 
* the bintree
***************************************************************/
TreeNode *find_bintree_last(TreeNode *node);

/***************************************************************
* printf of stored values of the entire tree
***************************************************************/
void printf_bintree_values(TreeNode *node, int start);


#endif /* INCLUDE_BINTREE_H */
