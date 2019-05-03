#include "bintree.h"

#include <stdlib.h>
#include <stdio.h>


/***************************************************************
* Create a new bintree node
***************************************************************/
TreeNode *create_bintree_node(int layer, int count)
{
  TreeNode *node = calloc(1, sizeof(TreeNode));
  node->layer = layer;
  node->count = count;

  node->next   = NULL;
  node->prev   = NULL;
  node->parent = NULL;
  node->child  = NULL;

  return node;
}

/***************************************************************
* Push a new neighbor node to the tree 
***************************************************************/
void push_bintree_neighbor(TreeNode *node, void *value)
{
  TreeNode *neighbor = create_bintree_node(node->layer, 
                                           node->count + 1);
  neighbor->value = value;

  if (node->next == NULL)
  {
    node->next = neighbor;
    neighbor->prev = node;
    neighbor->parent = node->parent;
  }
  else 
  {
    neighbor->next = node->next;
    node->next = neighbor;
    neighbor->prev = node;
    neighbor->parent = node->parent;
  }
}

/***************************************************************
* Push a new child node to the tree 
***************************************************************/
void push_bintree_child(TreeNode *node, void *value)
{
  TreeNode *child = create_bintree_node(node->layer + 1, 0);
  child->value = value;

  if (node->child == NULL)
  {
    node->child = child;
    child->parent = node;
  }
  else
  {
    TreeNode *lastChild = NULL;
    lastChild = find_bintree_last(node->child);
    push_bintree_neighbor(lastChild, value);
  }
}

/***************************************************************
* Clear bintree
***************************************************************/
void free_bintree(TreeNode *node, int start)
{
  TreeNode *head;
  if (start == 1)
    head = find_bintree_head(node);
  else
    head = node;
  
  if (head->next != NULL)
    free_bintree(head->next, 0);
  if (head->child != NULL)
    free_bintree(head->child, 0);

  //free(head->value);
  free(head);
}

/***************************************************************
* Find the head of the bintree, by providing any node of the
* bintree.
* The head is the first node in the first layer
* By definition, all child nodes point with their parent pointer
* to the first node node in the previous layer.
***************************************************************/
TreeNode *find_bintree_head(TreeNode *node)
{
  TreeNode *buf = node;
  while (buf->parent != NULL)
    buf = buf->parent;

  return buf;
}

/***************************************************************
* Find the bottom of the bintree, by providing a starting
* node of the bintree.
* The bottom is the first node in the last layer of a given
* starting point. Each node has a different bottom.
***************************************************************/
TreeNode *find_bintree_bottom(TreeNode *node)
{
  TreeNode *layerbuf = node;
  while (layerbuf->child != NULL)
    layerbuf = layerbuf->child;

  TreeNode *countbuf = layerbuf;
  while (countbuf->prev != NULL)
    countbuf = countbuf->prev;

  return countbuf;
}

/***************************************************************
* Find the first node of the current layer for a given node in 
* the bintree
***************************************************************/
TreeNode *find_bintree_first(TreeNode *node)
{
  TreeNode *buf = node;
  while (buf->prev != NULL)
    buf = buf->prev;

  return buf;
}

/***************************************************************
* Find the last node of the current layer for a given node in 
* the bintree
***************************************************************/
TreeNode *find_bintree_last(TreeNode *node)
{
  TreeNode *buf = node;
  while (buf->next != NULL)
    buf = buf->next;

  return buf;
}

/***************************************************************
* printf of stored values of the entire tree
***************************************************************/
void printf_bintree_values(TreeNode *node, int start)
{
  TreeNode *head;
  if (start == 1)
    head = find_bintree_head(node);
  else
    head = node;
  
  if (head->next != NULL)
    printf_bintree_values(head->next, 0);
  if (head->child != NULL)
    printf_bintree_values(head->child, 0);

  if (node->value != NULL)
    printf("%s\n", node->value);
}

