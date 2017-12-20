/**
	No Copyright. But if you copy this code, you may be verified as cheating in ZJU.
	BE CAREFUL!

	This piece of code defines simple binary search tree (unbalanced tree) and some algorithms to it.
*/

#ifndef UBT_H
#define UBT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _ubnode UBNode;
typedef UBNode* UBPointer;
//=======================================================
// UBPointer is a pointer pointing at a node in the unbalanced tree.
// Users don't need to know the details in this block.
// Please use function 'UBGetValue' to retrieve the value stored in the node.
struct _ubnode
{
	int value;
	UBPointer left, right;
}; 
//=======================================================

typedef struct _ubtreenode
{
	UBPointer root;
} UBTreeNode;
typedef UBTreeNode* UBTree;
// Declare 'UBTree' varible to use the functions followed.

UBTree UBBuild(void);
// Build an empty unbalanced tree and return it 
// An example to use this function: 		UBTree tree = UBBuild();

void UBIns(int value, UBTree tree);
// Insert a node with its value to be 'value' into the tree
// An example to use this function:			UBIns(0, tree);

UBPointer UBFind(int value, UBTree tree);
UBPointer UBFindMin(UBTree tree);
UBPointer UBFindMax(UBTree tree);
// Find the node with (certain/minimal/maximal)value in the tree and return its pointer.
// Return NULL if not found
// Examples to use these functions:			UBPointer p = UBFind(0, tree);	if(!p)printf("Not found!\n");
//											UBPointer min = UBFindMin(tree);
//											UBPointer max = UBFindMax(tree);

int UBDel(int value, UBTree tree);
// Delete the node with certain value in the tree. 
// Return 1 if the deletion succeeded, and 0 if not (which means the node doesn't exist).
// An example to use this function:			int suc = UBDel(0, tree);	if(!suc)printf("Deletion failed!\n");

void UBFree(UBTree tree);
// Free the whole tree
// An example to use this function:			UBFree(tree);

int UBGetValue(UBPointer p);
// When you get an UBPointer, use this function to access the value stored in it.
// An example to use this function:			UBPointer min = UBFindMin(tree);
//											if(!min) printf("The tree is empty!\n");
//											else printf("The minimum value is %d\n", UBGetValue(min));

#endif