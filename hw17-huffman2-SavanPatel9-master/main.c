// main.c
#include "tree.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv)
{
  // argv[1]: input file from hw16
  // argv[2]: input file from hw17
  // argv[3]: output file

    if (argc != 4)
    {
      return EXIT_FAILURE;
    }

    TreeNode * root = readListTree(argv[1]);  // will return one node with a full tree based on input

    //preOrderNode(root);

    int numRow = Tree_leaf(root);   // number of leaf nodes

    int numCol = Tree_height(root);   // tree height

    numCol++;   // need to account for -1

    // creating 2D array

    int ** codebook = malloc(sizeof(int *) * numRow);

    for(int row = 0; row < numRow; row++)
    {
      codebook[row] = malloc(sizeof(int) * numCol);
      // initialize to -1
      for(int col = 0; col < numCol; col++)
      {
        codebook[row][col] = -1;
      }
    }

    buildCodeBook(root, codebook);

    //printCodeBook(codebook, numRow);      // for testing

    // try mapping and then compress

    int mapping[NUMLETTER];
    int ind;
    for (ind = 0; ind < NUMLETTER; ind ++)
    {
      mapping[ind] = -1; // initialized to invalid index
      int ind2;
      for (ind2 = 0; ind2 < numRow; ind2 ++)
	    {
	      if (codebook[ind2][0] == ind)
	      {
	        mapping[ind] = ind2;
	      }
	    } 
    }

    compress(argv[2], argv[3], codebook, mapping);


    // releasing memory
    for (ind = 0; ind < numRow; ind ++)
    {
      free (codebook[ind]);
    }
    free (codebook);

    Tree_destroy(root);


    return EXIT_SUCCESS;
}