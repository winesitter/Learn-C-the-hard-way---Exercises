#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

#include "bintree.h"


int get_globlist(glob_t *globlist, char *query, TreeNode *dirTree, int init)
{
  int status;

  /*************************************************************
  * Read all files and directories
  *************************************************************/
  if (init == 1)
    status = glob(query, GLOB_TILDE | GLOB_MARK | GLOB_ONLYDIR, NULL, globlist);
  else 
    status = glob(query, GLOB_TILDE | GLOB_MARK | GLOB_APPEND | GLOB_ONLYDIR, NULL, globlist);


  /*************************************************************
  * Error handling
  *************************************************************/
  if (status == GLOB_NOSPACE) 
  {
    printf("ERROR: Query %s needs too much memory.\n", query);
    return status;
  }
  else if (status == GLOB_NOMATCH) 
  {
    return status;
  }
  else if (status == GLOB_ABORTED) 
  {
    printf("ERROR: Can not read files for query %s\n", query);
    return status;
  }

  /*************************************************************
  * Recursive handling of directories
  *************************************************************/
  int i=0;
  while (globlist->gl_pathv[i]) 
  {
    char *path = globlist->gl_pathv[i];
    int len    = strlen(path);

    if ( strcmp(&path[len - 1], "/") == 0 )
    {
      char *newQuery = malloc(len + strlen(query) + 1);  // + 1 for null terminator
      strcpy(newQuery, path);
      strcat(newQuery, query);

      push_bintree_child(dirTree, path);

      get_globlist(globlist, newQuery, dirTree->child, 0);

      free(newQuery);
    }
    else
    {
      push_bintree_neighbor(dirTree, path);
    }

    i++;
  }

  return status;
}



int main(int argc, char *argv[])
{
  TreeNode *tree = create_bintree_node(0,0);
  push_bintree_neighbor(tree, "test_neighbor");
  push_bintree_child(tree, "test_child");
  push_bintree_neighbor(tree->child, "test_child_neighbor");
  push_bintree_child(tree->child->next, "test_child_neighbor_neighbor");
  free_bintree(tree, 1);


  glob_t globlist;
  TreeNode *dirTree = create_bintree_node(0,0);

  get_globlist(&globlist, "*", dirTree, 1);

  //printf_bintree_values(dirTree, 1);

  int i=0;
  while (globlist.gl_pathv[i]) 
  {
    printf("%s\n", globlist.gl_pathv[i]);
    i++;
  }

  free_bintree(dirTree, 1);
  globfree(&globlist);

  return 0;
}
