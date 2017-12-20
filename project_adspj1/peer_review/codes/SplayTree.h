/**
	No Copyright. But if you copy this code, you may be verified as cheating in ZJU.
	BE CAREFUL!

	This piece of code defines splay tree and some algorithms to it.
*/

#ifndef SPLAY_H
#define SPLAY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _splaynode SplayNode;
typedef SplayNode* SplayPointer;
//=======================================================
// SplayPointer is a pointer pointing at a node in the splay tree.
// Users don't need to know the details in this block.
// Please use function 'SplayGetValue' to retrieve the value stored in the node.
struct _splaynode{
	int value;
	SplayPointer left;
	SplayPointer right;
	SplayPointer parent;
};

typedef struct _splaytree
{
	SplayPointer root;
} SplayTreeNode;
typedef SplayTreeNode* SplayTree;
// Declare 'SplayTree' varible to use the functions followed.

SplayTree splayBuild(void);
// Build an empty splay tree and return it 
// An example to use this function: 		SplayTree tree = splayBuild();

void splayIns(int value, SplayTree tree);
// Insert a node with its value to be 'value' into the tree
// An example to use this function:			splayIns(0, tree);

SplayPointer splayFind(int value, SplayTree tree);
SplayPointer splayFindMin(SplayTree tree);
SplayPointer splayFindMax(SplayTree tree);
// Find the node with (certain/minimal/maximal)value in the tree and return its pointer.
// Return NULL if not found
// Examples to use these functions:			SplayPointer p = splayFind(0, tree);	if(!p)printf("Not found!\n");
//											SplayPointer min = splayFindMin(tree);
//											SplayPointer max = splayFindMax(tree);

int splayDel(int value, SplayTree tree);
// Delete the node with certain value in the tree. 
// Return 1 if the deletion succeeded, and 0 if not (which means the node doesn't exist).
// An example to use this function:			int suc = splayDel(0, tree);	if(!suc)printf("Deletion failed!\n");

void splayFree(SplayTree tree);
// Free the whole tree
// An example to use this function:			splayFree(tree);

int splayGetValue(SplayPointer p);
// When you get an SplayPointer, use this function to access the value stored in it.
// An example to use this function:			SplayPointer min = splayFindMin(tree);
//											if(!min) printf("The tree is empty!\n");
//											else printf("The minimum value is %d\n", splayGetValue(min));

#endif
