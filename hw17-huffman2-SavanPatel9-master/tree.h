#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define QUEUE  0
#define STACK  1
#define SORTED 2

#define NUMLETTER 128

typedef struct treenode
{
  struct treenode * left;
  struct treenode * right;
  char value; // character
} TreeNode;

typedef struct listnode
{
  struct listnode * next;
  TreeNode * tnptr;
} ListNode;

TreeNode * TreeNode_create(char val);
void preOrderNode(TreeNode * tn);
TreeNode * Tree_merge(TreeNode * tn1, TreeNode * tn2);
void Tree_destroy(TreeNode * tn);
int Tree_height(TreeNode * tn);
int Tree_leaf(TreeNode * tn);

TreeNode * readListTree(char * filename);

ListNode * ListNode_create(TreeNode * tn);
// The mode is QUEUE, STACK, or SORTED
ListNode * List_insert(ListNode * head, ListNode * ln, int mode);
bool deleteNode(ListNode * head, ListNode * ln);

void buildCodeBook(TreeNode * root, int * * codebook);
void printCodeBook(int * * codebook, int numRow);

int compress(char * infile, char * outfile, int * * codebook, int * mapping);

#endif