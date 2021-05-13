/*
 * simpleBinaryTree.c
 *
 * Functions for a very simple binary
 * tree. This tree does not keep its data sorted. It simply
 * fills up the tree from left to right as new calls to
 * 'insertItem' are made.
 *
 * Created by Sally Goldin, 4 December 2012 for CPE113
 * Modified 22 January 2013 to do level order insertion
 * Modified 1 Feb 2014 to remove unused 'count' item in node and to
 *  fix memory leak in free (never freed the tree itself)
 * Modified 15 Feb 2018 to fix bug if you call freeTree when there
 * is no tree yet, or no root node.
 *
 * Panithi Suwanno (Big) 63070503426
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simpleBinaryTree.h"
#include "abstractQueue.h"


/** private **/
/* Return the number of children a node has 
 * Arguments 
 *   pNode      - node we are inquiring about
 * Return 0, 1 or 2
 */
int childCount(NODE_T* pNode)
{
	int count = 0;
	if (pNode->left != NULL)
		count++;
	if (pNode->right != NULL)
		count++;
	return count;
}

/*
 *  Function to print data from a node. Passed to
 *  various traversal functions.
 *  Argument
 *     pNode   -  Node to process
 */
void printNodeData(NODE_T* pNode)
{
	printf("Node %p ==> %s\n", pNode, pNode->data);
}

int found = 0;
void parentFinder(NODE_T* current, char* key, char* parent)
{
	if(current == NULL)
		return;
	if(strcmp(current->data, key) == 0)
	{
		if(strcmp(key, parent) == 0)   /* root node case */
		{
			printf("This is root node!\n");
			found = 1;
		}
		else
		{
			printf("%s\n");
			found = 1;
		}
	}
	else 
	{
		parentFinder(current->left, key, current->data);
		parentFinder(current->right, key, current->data);
	}
}

int depth(NODE_T* current)
{
	if(current == NULL)
		return 0;
	else
	{
		int left = depth(current->left);
		int right = depth(current->right);
		
		printf("%s\n", current->data);
		printf("%d %d\n", left, right);
		if(left > right)
			return left+1;
		else
			return right+1;
	}
}

void leaf(NODE_T* current)
{
	if(current->left == NULL && current->right == NULL)
	{
		printNodeData(current);
	}
	if(current->left != NULL)
	{
		leaf(current->left);
	}
	if(current->right != NULL)
	{
		leaf(current->right);
	}
}

void BFS(NODE_T* current)
{
	queueClear();
	enqueue(current);
	while((current = dequeue()) != NULL)
	{
		printNodeData(current);
		enqueue(current->left);
		enqueue(current->right);
	}
}


/* Function to insert a new node in its
 * correct location in the tree (next free spot, starting from the left) 
 * Arguments
 *    pRoot       - pointer to a node
 *    pNewNode    - new node - data already assigned
 */
void insertNode(NODE_T* pRoot, NODE_T* pNewNode)
{
	NODE_T * pNextNode = NULL;
	queueClear();
	enqueue(pRoot);
	while ((pNextNode = dequeue()) != NULL)
	{
		if (pNextNode->left == NULL)
		{
			pNextNode->left = pNewNode;
			printf("Added new node(%s) as left child of (%s)\n",
					pNewNode->data,pNextNode->data);
			break;
		}
		else if (pNextNode->right == NULL)
		{
			pNextNode->right = pNewNode;
			printf("Added new node(%s) as right child of (%s)\n",
					pNewNode->data,pNextNode->data);
			break;
		}
		else 
		{
			enqueue(pNextNode->left);
			enqueue(pNextNode->right);
		}
	}
}


void freeNode(NODE_T* pNode)
{
	free(pNode->data);  /* we allocated this, so we delete it */
	free(pNode);
}

/* Traverse a tree (in order traversal) and execute the
 * function 'nodeFunction' on each element
 * Argument
 *    pCurrent     -   current node
 *    nodeFunction -   function to execute on each node
 */
void traverseInOrder(NODE_T* pCurrent,void (*nodeFunction)(NODE_T* pNode ))
{
	if (pCurrent->left != NULL)
	{
		traverseInOrder(pCurrent->left,nodeFunction); 
	}
	(*nodeFunction)(pCurrent);
	if (pCurrent->right != NULL)
	{
		traverseInOrder(pCurrent->right,nodeFunction); 
	}
}

/* Traverse a tree (post order traversal) and execute the
 * function 'nodeFunction' on each element
 * Argument
 *    pCurrent     -   current node
 *    nodeFunction -   function to execute on each node
 */
void traversePostOrder(NODE_T* pCurrent,void (*nodeFunction)(NODE_T* pNode ))
{
	if (pCurrent->left != NULL)
	{
		traversePostOrder(pCurrent->left,nodeFunction); 
	}
	if (pCurrent->right != NULL)
	{
		traversePostOrder(pCurrent->right,nodeFunction); 
	}
	(*nodeFunction)(pCurrent);
}


/* Traverse a tree (pre order traversal) and execute the
 * function 'nodeFunction' on each element
 * Argument
 *    pCurrent     -   current node
 *    nodeFunction -   function to execute on each node
 */
void traversePreOrder(NODE_T* pCurrent,void (*nodeFunction)(NODE_T* pNode ))
{
	(*nodeFunction)(pCurrent);
	if (pCurrent->left != NULL)
	{
		traversePreOrder(pCurrent->left,nodeFunction); 
	}
	if (pCurrent->right != NULL)
	{
		traversePreOrder(pCurrent->right,nodeFunction); 
	}
}

/** PUBLIC FUNCTIONS */

/* Create a new tree and return a pointer to that tree
 * This is a "handle". Other modules should never look at
 * or modify the contents of the structure. The calling 
 * module should call 'freeTree' when it no longer needs
 * the tree.
 * Returns pointer to allocated tree, or null if memory allocation fails 
 */
TREE_T * createTree()
{
	TREE_T * pTree = calloc(1,sizeof(TREE_T));
	queueClear();
	return pTree;
}


/* Insert a new node into the next available location in the tree.
 * Arguments
 *    pTree       - pointer
 *    pDataItem    - new data to be inserted in the tree 
 * Returns 1 for success, 0 if memory allocation error occurred.
 */
int insertItem(TREE_T* pTree, char* pDataItem)
{
	int status = 1;
	char* pNewDataItem = NULL;
	NODE_T * pNewNode = NULL;
	/* create a copy of the data */
	pNewDataItem = strdup(pDataItem);
	/* create the new node */
	pNewNode = (NODE_T*) calloc(1,sizeof(NODE_T));
	if ((pNewNode == NULL) || (pNewDataItem == NULL))
	{
		status = 0;
	}
	else
	{
		pNewNode->data = pNewDataItem;
		if (pTree->root == NULL)
		{
			pTree->root = pNewNode;
			printf("Node (%s) is the root\n", pNewNode->data);
		}
		else
		{    
			insertNode(pTree->root,pNewNode);
		}
		pTree->itemcount++; 
	} 
	return status;
}

/* Traverse the tree and free all the nodes
 * Then free the TREE_T object itself.
 * This needs to be a post order traversal
 */
void freeTree(TREE_T * pTree)
{
	queueClear();
	if (pTree != NULL)
	{
		if (pTree->root != NULL)
			traversePostOrder(pTree->root,&freeNode);
		free(pTree);
	}
} 


/* Traverse and print using the specified order
 * structure
 * Argument
 *   pTree   - public structure
 *   order   - code for traversal order (see constants in .h file)
 */
void printTree(TREE_T * pTree, int order)
{
	char key[32];
	if (pTree == NULL)
		printf("Tree not created yet!\n");
	else if (pTree->root == NULL)
		printf("Tree is empty!\n");
	else
	{
		switch (order)
		{
			case PREORDER:
				traversePreOrder(pTree->root,&printNodeData);
				break;
			case INORDER:
				traverseInOrder(pTree->root,&printNodeData);
				break;
			case POSTORDER:
				traversePostOrder(pTree->root,&printNodeData);
				break;
			case LEVELORDER:
				BFS(pTree->root);
				break;
			case LEAF:
				leaf(pTree->root);
				break;
			case DEPTH:
				printf("Max depth is %d\n", depth(pTree->root));
				break;
			case PARENT:
				found = 0;
				printf("Enter child: ");
				fgets(key, sizeof(key), stdin);
				sscanf(key, "%s", key);
				printf("Result of %s's parent: ", key);
				parentFinder(pTree->root, key, key);
				if(found == 0) 
					printf("NOT FOUND THIS NODE\n");
				break;
			default:
				printf("Invalid order constant in printTree!\n");
		}
	} 

}

#ifdef DEBUG
/* this main is a test driver to see if the functions in this
 * module work correctly. It will not be compiled unless
 * -DDEBUG is specified on the compiler command line, e.g.
 * 
 *  gcc -DDEBUG -o binaryTree binaryTree.c
 *
 */
int main(int argc, char* argv[])
{

	/*  char* samples[] = {"What a day","Fred","I love C","Alphabet",
		"Zoology","Sunshine","Babysitter","Roast Duck",
		"Japanese","Nothing to say","Mai Pen Rai",
		"Who are you?","Yes","No","Maybe","123",
		"Ant City","Captain Kirk","Japanese"};
		*/

	char* samples[] = {"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16"};


	int sampleCount = sizeof(samples)/sizeof(char*);
	int i = 0;
	TREE_T * pMyTree = createTree();
	if (pMyTree == NULL)
	{
		printf("Memory allocation error creating new tree\n");
		exit(1);
	}
	printf("Successfully created the tree!\n");

	for (i = 0; i < sampleCount; i++)
	{
		if (!insertItem(pMyTree,samples[i]))
		{
			printf("Memory allocation error inserting new item\n");
			break;
		}
	}

	printf("Let's print them in pre order!\n\n");
	printTree(pMyTree,PREORDER);
	printf("\nNow print them in inorder!\n\n");
	printTree(pMyTree,INORDER);
	printf("\nNow post order!\n\n");
	printTree(pMyTree,POSTORDER);

	printf("\n\nOkay, free the tree\n");
	freeTree(pMyTree);

}
#endif
