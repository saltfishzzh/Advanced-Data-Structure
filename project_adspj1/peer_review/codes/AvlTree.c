#include "AvlTree.h"

AvlPointer llrot(AvlPointer A);
AvlPointer lrrot(AvlPointer A);
AvlPointer rlrot(AvlPointer A);
AvlPointer rrrot(AvlPointer A);

// Build an empty AVL tree
AvlTree AVLBuild(void)
{
	AvlTree tree = (AvlTree)malloc(sizeof(AvlTreeNode));
	tree->root = NULL;
	return tree;
}

void AVL_Free_Node(AvlPointer node);	//Free the tree (or subtree) whose root is 'node'
//Free the whole tree
void AVLFree(AvlTree tree)
{
	if(tree)AVL_Free_Node(tree->root);	//If tree is valid, simply use AVL_Free_Node function
	free(tree);
}
void AVL_Free_Node(AvlPointer node)
{
	if(node && node->left)AVL_Free_Node(node->left);
	if(node && node->right)AVL_Free_Node(node->right);
	free(node);
}

//Find the node with certain value in the tree
AvlPointer AVLFind(int value, AvlTree tree)
{
	AvlPointer p = tree->root;
	while(p && p->value != value){
		if(p->value < value)p = p->right;
		else p = p->left;
	}
	return p;
}

//Find the node with minimum value in the subtree whose root is p
AvlPointer AVLFindMinNode(AvlPointer p)
{
	while(p && p->left)p = p->left;
	return p;
}

//Find the node with minimum value in the tree
AvlPointer AVLFindMin(AvlTree tree)
{
	return AVLFindMinNode(tree->root);
}

//Find the node with maximum value in the subtree whose root is p
AvlPointer AVLFindMaxNode(AvlPointer p)
{
	while(p && p->right)p = p->right;
	return p;
}

//Find the node with maximum value in the tree
AvlPointer AVLFindMax(AvlTree tree)
{
	return AVLFindMaxNode(tree->root);
}

//Find the node with certain value in the tree whose root is p,
//it returns the root of the tree after deletion
AvlPointer AVLNodeDel(int value, AvlPointer p)
{
	int lh = 0, rh = 0;			
	//lh means the height of the left subtree of p, while rh means the height of the right one
	
	if(p->value == value)		//if p is to be deleted
	{
		if(!p->left && !p->right)	// if p is a leaf node, then simply free it and assign p NULL
		{
			free(p);
			p = NULL;
		}
		else		// otherwise
		{
			if(p->left)	//if p has left child, find 'maximum node' in the left subtree and replace p with it
			{
				AvlPointer lcmax = AVLFindMaxNode(p->left);
				// by replacing the value of p with its value and delete it in the left subtree of p
				p->value = lcmax->value;
				p->left = AVLNodeDel(lcmax->value, p->left);
			}
			else	// or the case is much simpler. we only need to replace p with the right child of p
			{
				AvlPointer rchild = p->right;
				free(p);
				p = rchild;
			}
		}
	}
	else
	{
		if(value < p->value)
		{
			p->left = AVLNodeDel(value, p->left);
		}
		else
		{
			p->right = AVLNodeDel(value, p->right);
		}			
	}

	// Now the deletion is completed in the recursion above, we need to check 
	// the height of two subtrees and do necessary rotations.
	if(p)
	{
		// assign the height of p
		if(p->left)lh = p->left->height + 1;	else lh = 0;
		if(p->right)rh = p->right->height + 1;	else rh = 0;
		p->height = lh > rh ? lh : rh;

		// the following code describes how to rotate in different cases
		if(lh - rh > 1)
		{
			int llh = p->left->left ? p->left->left->height + 1 : 0;
			int lrh = p->left->right ? p->left->right->height + 1 : 0;
			if(llh > lrh)p = llrot(p);
			else p = lrrot(p);
		}
		else if(lh - rh < -1)
		{
			int rlh = p->right->left ? p->right->left->height + 1 : 0;
			int rrh = p->right->right ? p->right->right->height + 1 : 0;
			if(rlh > rrh)p = rlrot(p);
			else p = rrrot(p);
		}
	}
	return p;
}

// Delete the node with certain value in the tree, if deletion fails (the node is not found), then return 0
// otherwise return 1
int AVLDel(int value, AvlTree tree)
{
	AvlPointer p;
	int lh = 0, rh = 0;

	p = AVLFind(value, tree);			//find the node to be deleted
	if(!p)return 0;						// if not found, return 0
	else tree->root = AVLNodeDel(value, tree->root);	//else use AVLNodeDel function
	return 1;
}

//Get the value stored in an AvlPointer
int AVLGetValue(AvlPointer p)
{
	return p->value;
}


// Insert a node with value into the subtree whose root is p. It returns the root of this subtree after insertion.
AvlPointer AVLInsEle(int value, AvlPointer p);
// Insert a node with value into the tree
void AVLIns(int value, AvlTree tree)
{	
	if(!tree)return;	//if the tree is invalid, do nothing

	if(!tree->root)		//if the tree is empty, create a node with value to be its root
	{
		AvlPointer p = (AvlPointer)malloc(sizeof(AvlNode));
		p->value = value; p->left = p->right = NULL;
		tree->root = p;
		p->height = 0;
	}
	else				//otherwise, use AVLInsEle function
		tree->root = AVLInsEle(value, tree->root);
}

AvlPointer AVLInsEle(int value, AvlPointer p)
{
	int lh = 0, rh = 0;
	// lh means the height of the left subtree of p + 1, while rh means the height of the right one + 1
	// the default value 0 means the height of NULL(-1) + 1

	if( !p ){						// if p is NULL, create a new node
		p = (AvlPointer)malloc(sizeof(AvlNode));
		p->value = value;
		p->left = p->right = NULL;
		p->height = 0;
	}else if(value > p->value){		// in this case, insert value to the right subtree of p
		p->right = AVLInsEle(value, p->right);
	}else if(value < p->value){		// in this case, insert value to the left subtree of p
		p->left = AVLInsEle(value, p->left);
	}else{
		return p;
	}

	// assign the height of p
	if(p->left)lh = p->left->height + 1;
	if(p->right)rh = p->right->height + 1;
	p->height = lh > rh ? lh : rh;

	// the following code describes how to rotate in different cases
	if(lh - rh < -1){
		if(value > p->right->value)
			p = rrrot(p);
		else
			p = rlrot(p);
	}else if(lh - rh > 1){
		if(value < p->left->value)
			p = llrot(p);
		else
			p = lrrot(p);
	}

	return p;
}

// single left rotation
AvlPointer llrot(AvlPointer A){
	AvlPointer B = A->left;

	A->left = B->right;
	B->right = A;
	A->height -= 2;

	return B;
}

// single right rotation
AvlPointer rrrot(AvlPointer A){
	AvlPointer B = A->right;

	A->right = B->left;
	B->left = A;
	A->height -= 2;

	return B;
}

// double left right rotation
AvlPointer lrrot(AvlPointer A){
	AvlPointer B = A->left;
	AvlPointer C = B->right;

	A->left = C->right;
	C->right = A;
	B->right = C->left;
	C->left = B;
	A->height -= 2;
	B->height --;
	C->height ++;
	return C;
}

// double right left rotation
AvlPointer rlrot(AvlPointer A){
	AvlPointer B = A->right;
	AvlPointer C = B->left;

	A->right = C->left;
	C->left = A;
	B->left = C->right;
	C->right = B;
	A->height -= 2;
	B->height --;
	C->height ++;
	return C;
}
