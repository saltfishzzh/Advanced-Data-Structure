/**
	No Copyright. But if you copy this code, you may be verified as cheating in ZJU.
	BE CAREFUL!

	This piece of code defines AVL tree and some algorithms to it.
*/


#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>


struct _avlnode;
typedef struct _avlnode AvlNode;
typedef AvlNode* AvlPointer;
//=======================================================
// AvlPointer is a pointer pointing at a node in the AVL tree.
// Users don't need to know the details in this block.
// Please use function 'AVLGetValue' to retrieve the value stored in the node.
struct _avlnode
{
	int value;
	AvlPointer left;
	AvlPointer right;
	int height;
};
//=======================================================


typedef struct _avltree
{
	AvlPointer root;
} AvlTreeNode;
typedef AvlTreeNode* AvlTree;
// Declare 'AvlTree' varible to use the functions followed.

AvlTree AVLBuild(void);
// Build an empty AVL tree and return it 
// An example to use this function: 		AvlTree tree = AVLBuild();

void AVLIns(int value, AvlTree tree);
// Insert a node with its value to be 'value' into the tree
// An example to use this function:			AVLIns(0, tree);

AvlPointer AVLFind(int value, AvlTree tree);
AvlPointer AVLFindMin(AvlTree tree);
AvlPointer AVLFindMax(AvlTree tree);
// Find the node with (certain/minimal/maximal)value in the tree and return its pointer.
// Return NULL if not found
// Examples to use these functions:			AvlPointer p = AVLFind(0, tree);	if(!p)printf("Not found!\n");
//											AvlPointer min = AVLFindMin(tree);
//											AvlPointer max = AVLFindMax(tree);

int AVLDel(int value, AvlTree tree);
// Delete the node with certain value in the tree. 
// Return 1 if the deletion succeeded, and 0 if not (which means the node doesn't exist).
// An example to use this function:			int suc = AVLDel(0, tree);	if(!suc)printf("Deletion failed!\n");

void AVLFree(AvlTree tree);
// Free the whole tree
// An example to use this function:			AVLFree(tree);

int AVLGetValue(AvlPointer p);
// When you get an AvlPointer, use this function to access the value stored in it.
// An example to use this function:			AvlPointer min = AVLFindMin(tree);
//											if(!min) printf("The tree is empty!\n");
//											else printf("The minimum value is %d\n", AVLGetValue(min));

#endif
