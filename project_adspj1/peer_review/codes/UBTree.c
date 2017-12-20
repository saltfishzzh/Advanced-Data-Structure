#include "UBTree.h"

// Build an empty unbalanced tree and return it 
UBTree UBBuild(void)
{
	UBTree t = (UBTree)malloc(sizeof(UBTreeNode));
	t->root = NULL;
	return t;
}

// Insert a node with value into the tree
void UBIns(int value, UBTree tree)
{
	if(!tree)return;	//if the tree is invalid, do nothing

	if(!tree->root)		//if the tree is empty, create a node with value to be its root
	{
		tree->root = (UBPointer)malloc(sizeof(UBNode));
		tree->root->value = value;
		tree->root->left = tree->root->right = NULL;
	}
	else
	{					//search the proper position to insert
		UBPointer p = tree->root;
		while(p->value != value)	//if p->value == value, there is no need to insert
		{
			if(value < p->value)	//search the position in left subtree
			{
				if(!p->left)		//insert it to the left position of p and break
				{
					p->left = (UBPointer)malloc(sizeof(UBNode));
					p->left->value = value;
					p->left->left = p->left->right = NULL;
					break;
				}
				p = p->left;
			}
			else					//search the position in left subtree
			{
				if(!p->right)		//insert it to the left position of p and break
				{
					p->right = (UBPointer)malloc(sizeof(UBNode));
					p->right->value = value;
					p->right->left = p->right->right = NULL;
					break;
				}
				p = p->right;
			}
		}
	}
}

// Find the node with certain value in the tree and return its pointer.
UBPointer UBFind(int value, UBTree tree)
{
	UBPointer p = tree->root;
	while(p && p->value != value)
	{
		if(value < p->value)p = p->left;
		else p = p->right;
	}
	return p;
}

// Find the node with minimum value in the tree and return its pointer.
UBPointer UBFindMin(UBTree tree)
{
	UBPointer p = tree->root;
	while(p && p->left)p = p->left;
	return p;
}

// Find the node with maximum value in the tree and return its pointer.
UBPointer UBFindMax(UBTree tree)
{
	UBPointer p = tree->root;
	while(p && p->right)p = p->right;
	return p;
}

//Find the node with certain value in the tree whose root is p,
//it returns the root of the tree after deletion
UBPointer UBNodeDel(int value, UBPointer p)
{
	if(value < p->value) p->left = UBNodeDel(value, p->left);			//delete from left subtree
	else if(value > p->value) p->right = UBNodeDel(value, p->right);	//delete from right subtree
	else
	{ 																	//delete p
		if(!p->left && !p->right)				//if p is a leaf, simply free it
		{
			free(p);
			p = NULL;
		}
		else if(p->left && p->right)			//if p has both children
		{										//swap p with its left child, delete from the left subtree
			p->value = p->left->value;
			p->left->value = value;
			p->left = UBNodeDel(value, p->left);
		}
		else if(!p->left)						//if p doesn't has left child, return the right child of p
		{										//and free p
			UBPointer child = p->right;
			free(p);
			p = child;
		}
		else									//if p doesn't has right child, return the left child of p
		{										//and free p
			UBPointer child = p->left;
			free(p);
			p = child;
		}
	}
	return p;
}

// Delete the node with certain value in the tree, if deletion fails (the node is not found), then return 0
// otherwise return 1
int UBDel(int value, UBTree tree)
{
	UBPointer p = UBFind(value, tree);		//find the node to be deleted
	if(!p) return 0;						// if not found, return 0
	else tree->root = UBNodeDel(value, tree->root);	//else use UBNodeDel function
	return 1;
}

//Free the tree (or subtree) whose root is p
void UBFreeNode(UBPointer p);
//Free the whole tree
void UBFree(UBTree tree)
{
	if(tree)UBFreeNode(tree->root);
	free(tree);
}
void UBFreeNode(UBPointer p)
{
	if(p && p->left)UBFreeNode(p->left);
	if(p && p->right)UBFreeNode(p->right);
	free(p);
}

//Get the value stored in a UBPointer
int UBGetValue(UBPointer p)
{
	return p->value;
}