#include "tree.h"

TreeNode * TreeNode_create(char val)
{
  TreeNode * tn = malloc(sizeof(TreeNode));
  tn -> left = NULL;
  tn -> right = NULL;
  tn -> value = val;
  return tn;
}

TreeNode * Tree_merge(TreeNode * tn1, TreeNode * tn2)
{
  TreeNode * tn = malloc(sizeof(TreeNode));
  tn -> left = tn1;
  tn -> right = tn2;
  tn -> value = '0'; // do not care
  return tn;
}

void preOrderNode(TreeNode * tn)
{
  if (tn == NULL)
    {
      return;
    }
  printf("%c\n", tn -> value);
  preOrderNode(tn -> left);
  preOrderNode(tn -> right);
}

void Tree_destroy(TreeNode * tn)
{
  if (tn == NULL)
    {
      return;
    }
  Tree_destroy(tn -> left);
  Tree_destroy(tn -> right);
  free (tn);
}

TreeNode * readListTree(char * filename)
{
    ListNode * head = NULL;     // returned node
    ListNode * ln;              // input node
    TreeNode * tn;              // input tree node

    TreeNode * final;

    // used for merge

    TreeNode * left;
    TreeNode * right;

    TreeNode * merge;

    char onechar;

    FILE * fptr = fopen(filename, "r");

    while ((onechar = fgetc(fptr)) != EOF)
    {
      if(onechar == '1')      // control bit for data
      {
        onechar = fgetc(fptr);
        tn = TreeNode_create(onechar);      // creates a tree node
        ln = ListNode_create(tn);           // creates a list node with tnptr
        head = List_insert(head, ln, QUEUE);           // insert into the list
      }
      else if(onechar == '0' && head -> next != NULL)     // control bit for merge and checks for end of tree bit
      {
        right = ln -> tnptr;            // store tree node
        deleteNode(head, ln);     // delete node

        ln = head;
        while(ln -> next != NULL)
        {
          ln = ln -> next;
        }

        left = ln -> tnptr;             // store again

        merge = Tree_merge(left, right);    // merge

        ln -> tnptr = merge;            // creates a list node with tnptr

      }

    }

    final = head -> tnptr;

    free(head);

    fclose(fptr);

    return final;
}

ListNode * ListNode_create(TreeNode * tn)
{
  ListNode * ln = malloc(sizeof(ListNode));
  ln -> next = NULL;
  ln -> tnptr = tn;
  return ln;
}
// head may be NULL
// ln must not be NULL
// ln -> next must be NULL
ListNode * List_insert(ListNode * head, ListNode * ln, int mode)
{
  if (ln == NULL)
    {
      printf("ERROR! ln is NULL\n");
      return NULL;
    }
  if ((ln -> next) != NULL)
    {
      printf("ERROR! ln -> next is not NULL\n");
    }    
  if (head == NULL)
    {
      return ln;
    }
  if (mode == STACK)
    {
      ln -> next = head;
      return ln;
    }
  if (mode == QUEUE)
    {
      head -> next = List_insert(head -> next, ln, mode);
      return head;
    }
  
  return head;
}

bool deleteNode(ListNode * head, ListNode * todelete)
{
  if(head == NULL)
  {
    return false;
  }

  if(todelete == NULL)
  {
    return false;
  }

  if(head == todelete)
  {
    ListNode * p = head;
    head = head -> next;
    free(p);
    return true;
  }

  ListNode * end = head;
  ListNode * prev = NULL;

  while(end -> next)
  {
    prev = end;
    end = end -> next;
  }

  prev -> next = NULL;

  free(end);

  return true;
}

static int Tree_heightHelper(TreeNode * tn, int height)
{
  if (tn == 0)
    {
      return height;
    }
  int lh = Tree_heightHelper(tn -> left, height + 1);
  int rh = Tree_heightHelper(tn -> right, height + 1);
  if (lh < rh)
    { 
      return rh;
    }
  if (lh > rh)
    { 
      return lh;
    }
  return lh;
}

int Tree_height(TreeNode * tn)
{
  return Tree_heightHelper(tn, 0);
}

static void Tree_leafHelper(TreeNode * tn, int * num)
{
  if (tn == 0)
    {
      return;
    }
  // if it is a leaf node, add one
  TreeNode * lc = tn -> left;
  TreeNode * rc = tn -> right;
  if ((lc == NULL) && (rc == NULL))
    {
      (* num) ++;
      return;
    }
  Tree_leafHelper(lc, num);
  Tree_leafHelper(rc, num);
}

int Tree_leaf(TreeNode * tn)
{
  int num = 0;
  Tree_leafHelper(tn, & num);
  return num;
}

void buildCodeBookHelper(TreeNode * tn, int * * codebook, int * row, int col)
{
  if (tn == NULL)
  {
    return;
  }
  // is it a leaf node?
  TreeNode * lc = tn -> left;
  TreeNode * rc = tn -> right;
  if ((lc == NULL) && (rc == NULL))
  {
    // finish one code
    codebook[*row][0] = tn -> value;
    (* row) ++;
    return;
  }
  if (lc != NULL)
  {
    // populate this column of the entire subtree
    int numRow = Tree_leaf(lc);
    int ind;
    for (ind = * row; ind < (* row) + numRow; ind ++)
	  {
	    codebook[ind][col] = 0;
	  }
    buildCodeBookHelper(lc, codebook, row, col + 1);
  }
  if (rc != NULL)
  {
    int numRow = Tree_leaf(rc);
    int ind;
    for (ind = * row; ind < (* row) + numRow; ind ++)
	  {
	    codebook[ind][col] = 1;
	  }
    buildCodeBookHelper(rc, codebook, row, col + 1);
  }    
}

void buildCodeBook(TreeNode * root, int * * codebook)
{
  int row = 0;
  // column start at 1 because [0] stores the character
  buildCodeBookHelper(root, codebook, & row, 1); 
}

void printCodeBook(int * * codebook, int numRow)
{
  int row;
  for (row = 0; row < numRow; row ++)
  {
    // print the character
    printf("%c %d ", codebook[row][0], codebook[row][0]);
    int col = 1;
    while (codebook[row][col] != -1)
    {
      printf("%d", codebook[row][col]);
      col ++;
	  }
    printf("\n");
  }
}

int compress(char * infile, char * outfile, int * * codebook, int * mapping)
{
  int numBit = 0;

  FILE * infptr = fopen(infile, "r");

  if (infptr == NULL)
  {
    return 0;
  }

  FILE * outfptr = fopen(outfile, "wb"); // write binary

  if (outfptr == NULL)
  {
    fclose (outfptr);
    return 0;
  }

  unsigned char byte = 0;

  while (! feof(infptr))
  {
    int onechar = fgetc(infptr);
    if (onechar != EOF)
	  {
      int ind = mapping[onechar];
      int ind2 = 1;
      while (codebook[ind][ind2] != -1)
      {

        byte |= codebook[ind][ind2];

        if(numBit == 7)
        {
          numBit = -1;
          fwrite(&byte, sizeof(unsigned char), 1, outfptr);
          byte = 0x00;
        }


        byte = byte << 1;

        numBit = (numBit + 1) % 8;

        ind2 ++;

      }

	  }
  }

  byte = byte << (7 - numBit);

  fwrite(&byte, sizeof(unsigned char), 1, outfptr);

  fclose(infptr);
  fclose(outfptr);
  return 1;
}