#include "SplayTree.h"

// splay p in the subtree whose root is 'root'
SplayPointer Splay(SplayPointer p, SplayPointer root);

// Build an empty splay tree and return it 
SplayTree splayBuild(void)
{
	SplayTree t = (SplayTree)malloc(sizeof(SplayTreeNode));
	if(t)t->root = NULL;
	return t;
}

// Insert a node with value into the subtree whose root is p. 
// It returns the root of this subtree after insertion.
SplayPointer splayInsNode(int value, SplayPointer p);
// Insert a node with its value to be 'value' into the tree
void splayIns(int value, SplayTree tree)
{
	if(!tree)return;	//if the tree is invalid, do nothing

	if(!tree->root)		//if the tree is empty, create a node with value to be its root
	{
		tree->root = (SplayPointer)malloc(sizeof(SplayNode));
		tree->root->value = value;
		tree->root->left = tree->root->right = tree->root->parent = NULL;
	}
	else				//otherwise, use splayInsNode function, and then splay p in the whole tree
	{
		SplayPointer p = splayInsNode(value, tree->root);	
		tree->root = Splay(p, tree->root);
	}
}

SplayPointer splayInsNode(int value, SplayPointer p)
{
	while(p && p->value != value)	//if p->value == value, there is no need to insert
	{
		if(p->value < value)		//search the position in right subtree
		{
			if(!p->right)			//insert it to the left position of p and break
			{
				p->right = (SplayPointer)malloc(sizeof(SplayNode));
				p->right->value = value;
				p->right->parent = p;
				p->right->left = p->right->right = NULL;
				break;
			}
			p = p->right;
		}
		else						//search the position in left subtree
		{
			if(!p->left)			//insert it to the left position of p and break
			{
				p->left = (SplayPointer)malloc(sizeof(SplayNode));
				p->left->value = value;
				p->left->parent = p;
				p->left->left = p->left->right = NULL;
			}
			p = p->left;
		}
	}
	return p;
}

// Find the node with certain value in the tree and return its pointer.
SplayPointer splayFind(int value, SplayTree tree)
{
	SplayPointer p = tree->root;
	// find the node with value
	while(p && p->value != value)
	{
		if(p->value < value)p = p->right;
		else p = p->left;
	}
	// if found and it isn't the root, splay the node, otherwise simply return the pointer
	if(p && p != tree->root)tree->root = Splay(p, tree->root);
	return p;
}

SplayPointer splay_find_min(SplayPointer root)
{
	SplayPointer p = root;
	while(p && p->left) p = p->left;	
	return p;
}
// Find the node with minimum value in the tree and return its pointer.
SplayPointer splayFindMin(SplayTree tree)
{
	//find the minimum node and splay it
	SplayPointer p = splay_find_min(tree->root);
	if(p)tree->root = Splay(p, tree->root);
	return p;
}

SplayPointer splay_find_max(SplayPointer root)
{
	SplayPointer p = root;
	while(p && p->right) p = p->right;
	return p;
}
// Find the node with maximum value in the tree and return its pointer.
SplayPointer splayFindMax(SplayTree tree)
{
	//find the maximum node and splay it
	SplayPointer p = splay_find_max(tree->root);
	if(p)tree->root = Splay(p, tree->root);
	return p;
}

// Delete the node with certain value in the tree. 
// Return 1 if the deletion succeeded, and 0 if not (which means the node doesn't exist).
int splayDel(int value, SplayTree tree)
{
	// Find the node. If found, it will be placed at the root of the tree.
	SplayPointer p = splayFind(value, tree);
	if(!p)return 0;	//If not found, return 0.

	// If p is deleted, the whole tree will be divided into two parts at most
	SplayPointer new_root = NULL;
	// If p has both children,
	if(p->left && p->right)
	{
		// find the maximum node in the left subtree and splay it to the root of the left subtree
		new_root = splay_find_max(p->left);
		tree->root = Splay(new_root, p->left);
		new_root->parent = NULL;
		// as the new_root is the maximum node in the subtree, it has no right children
		// we can simply make the right child of p be the right child of new_root
		new_root->right = p->right;
		if(p->right)p->right->parent = new_root;
	}
	// If p has no left child, simply make the right subtree to be the new tree
	else if(!p->left)
	{
		tree->root = p->right;
		if(p->right)p->right->parent = NULL;
	}
	// If p has no right child, simply make the left subtree to be the new tree
	else
	{
		tree->root = p->left;
		if(p->left)p->left->parent = NULL;
	}

	free(p);
	return 1;
}

//Free the tree (or subtree) whose root is 'node'
void splay_Free_Node(SplayPointer node)
{
	if(node && node->left)splay_Free_Node(node->left);
	if(node && node->right)splay_Free_Node(node->right);
	free(node);
}
//Free the whole tree
void splayFree(SplayTree tree)
{
	if(tree)splay_Free_Node(tree->root);
	free(tree);
}

//Get the value stored in a splayPointer
int splayGetValue(SplayPointer p)
{
	return p->value;
}

//=============================
// The four actions using in splay function
void ZigZig(SplayPointer p);
void ZigZag(SplayPointer p);
void ZagZig(SplayPointer p);
void ZagZag(SplayPointer p);
//=============================
SplayPointer Splay(SplayPointer p, SplayPointer root)
{
	if(p == root)return p;		//If p is the root, we needn't to splay
	int finishSplay = 0;		//to mark whether the splay is finished
	while(!finishSplay)
	{
		if(p->parent == root)	//If p is a child of root,
		{
			finishSplay = 1;	//the splay will be finished in the next step

			if(p->value < root->value)	//if p is the left child
			{
				root->left = p->right;	if(p->right)p->right->parent = root;
				p->right = root;
			}
			else						//if p is the right child
			{
				root->right = p->left;	if(p->left)p->left->parent = root;
				p->left = root;
			}
			root->parent = p;
			p->parent = NULL;
		}
		else
		{
			if(p->parent->parent == root)finishSplay = 1;

			if(p->value < p->parent->value && p->value < p->parent->parent->value) ZigZig(p);		//     /
																									//    /
																									//   p

			else if(p->value > p->parent->value && p->value < p->parent->parent->value) ZigZag(p);	//   /
																									//   \
																									//    p

			else if(p->value < p->parent->value && p->value > p->parent->parent->value) ZagZig(p);	//   \
																									//   /
																									//  p

			else if(p->value > p->parent->value && p->value > p->parent->parent->value) ZagZag(p);	//   \
																									//    \
																									//     p
		}
	}
	return p;
}

void ZigZig(SplayPointer p)
{
	SplayPointer A = p, B = p->parent, C = B->parent;

	B->left = A->right;		if(A->right)A->right->parent = B;
	C->left = B->right;		if(B->right)B->right->parent = C;
	A->right = B;
	B->right = C;
	A->parent = C->parent;
	B->parent = A;
	C->parent = B;

	if(A->parent)
	{
		if(A->parent->value > A->value) A->parent->left = A;
		else A->parent->right = A;
	}
}

void ZigZag(SplayPointer p)
{
	SplayPointer A = p, B = p->parent, C = B->parent;

	B->right = A->left;		if(A->left)A->left->parent = B;
	C->left = A->right;		if(A->right)A->right->parent = C;
	A->left = B;
	A->right = C;
	A->parent = C->parent;
	B->parent = A;
	C->parent = A;

	if(A->parent)
	{
		if(A->parent->value > A->value) A->parent->left = A;
		else A->parent->right = A;
	}
}

void ZagZig(SplayPointer p)
{
	SplayPointer A = p, B = p->parent, C = B->parent;

	B->left = A->right;		if(A->right)A->right->parent = B;
	C->right = A->left;		if(A->left)A->left->parent = C;
	A->right = B;
	A->left = C;
	A->parent = C->parent;
	B->parent = A;
	C->parent = A;

	if(A->parent)
	{
		if(A->parent->value > A->value) A->parent->left = A;
		else A->parent->right = A;
	}
}

void ZagZag(SplayPointer p)
{
	SplayPointer A = p, B = p->parent, C = B->parent;

	B->right = A->left;		if(A->left)A->left->parent = B;
	C->right = B->left;		if(B->left)B->left->parent = C;
	A->left = B;
	B->left = C;
	A->parent = C->parent;
	B->parent = A;
	C->parent = B;

	if(A->parent)
	{
		if(A->parent->value > A->value) A->parent->left = A;
		else A->parent->right = A;
	}
}
