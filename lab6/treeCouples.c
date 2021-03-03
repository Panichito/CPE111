/* treeCouples.c  modified from linkCouples.c
 *
 * This lab is intended to give me the chance to create a simple sorted binary tree, 
 * to use as a search index
 *
 * Created by Panithi Suwanno(Big) 63070503426 for LAB3
 * 23 FEB 2020 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _person
{
	char name[32];			
	char gender[2]; 	
	struct _person *pPartner;	
	struct _person *left;
	struct _person *right;
} PERSON_T;
void freePerson(PERSON_T* current)
{
	if(current->left != NULL) {
		freePerson(current->left);
	}
	if(current->right != NULL) {
		freePerson(current->right);
	}
	free(current);
}
PERSON_T *findPerson(PERSON_T *current, char *name)
{
	PERSON_T *found = NULL;
	if(current != NULL) {
		if(strcmp(name,current->name)==0) 
		{
			found = current;
		}
		else if(strcmp(name,current->name) < 0) 
		{
			found = findPerson(current->left,name);
		}
		else 
		{
			found = findPerson(current->right,name);
		}
	}
	return found;
}
void insertNode(PERSON_T *currentNode, PERSON_T *newNode)  /* trythis6 */
{
    if (strcmp(newNode->name, currentNode->name) < 0)
    {
        if (currentNode->left == NULL)
        {
            currentNode->left = newNode;
            printf("Adding '%s' as left child of '%s'\n",newNode->name, currentNode->name);
        }
        else
            insertNode(currentNode->left, newNode);
    }
    else /* go right */
    {
        if (currentNode->right == NULL)
        {
            currentNode->right = newNode;
            printf("Adding '%s' as right child of '%s'\n",newNode->name, currentNode->name);
        }
        else
            insertNode(currentNode->right, newNode);
    }
}
void printCouple(PERSON_T *current) {
	if(current->left != NULL) {
		printCouple(current->left);
	}
	if(current->right != NULL) {
		printCouple(current->right);
	}
	if(current!=NULL && current->pPartner!=NULL) {
		if(current->pPartner != NULL)
		{
			printf("    %s is coupled with %s\n",current->name,current->pPartner->name);
			current->pPartner->pPartner = NULL;  /* note that current will use again! */
		}
	}
}
void addcouple(PERSON_T *pPersonA, PERSON_T *pPersonB)
{
	if(pPersonA->pPartner !=NULL)
	{
		pPersonA->pPartner->pPartner = NULL;  /* initially assign to NULL */
		printf("  %s is breaking up with %s and is now a couple with %s\n",pPersonA->name,pPersonA->pPartner->name,pPersonB->name);
	}
	if(pPersonB->pPartner !=NULL)
	{
		pPersonB->pPartner->pPartner = NULL;  /* initially assign to NULL */
		printf("  %s is breaking up with %s and is now a couple with %s\n",pPersonB->name,pPersonB->pPartner->name,pPersonA->name);
	}
	/* link new couple */
	pPersonA->pPartner = pPersonB;
	pPersonB->pPartner = pPersonA;
}
void usage() {
	printf("Usage:   ./listCouples [inputfile]\n\n");
	exit(0);
}
int main(int argc,char* argv[])
{
	FILE *filename = NULL;
	char name[64];
	char gender[2];
	char couple1[64];
	char couple2[64];
	char input[128];
	int i = 0;
	PERSON_T *root = NULL;
	PERSON_T *person = NULL;
	PERSON_T *pPersonA = NULL;
	PERSON_T *pPersonB = NULL;
	if(argc < 2)
	{
		usage();
	}
	filename = fopen(argv[1],"r");
	if(filename == NULL) 
	{
		exit(1);
	}
	printf("Welcome to couples program.\n");
	while(fgets(input,sizeof(input),filename) != NULL)
	{
		sscanf(input,"%s %s",name,gender);
		printf("  %s %s\n", name,gender);
		person = (PERSON_T*)calloc(1,sizeof(PERSON_T));
		if(person == NULL) 
		{
			printf("Memory allocation error - exiting\n");
		}
		strcpy(person->name,name);
		strcpy(person->gender,gender);
		if(root == NULL)
		{
			root = person;
		}
		else if(findPerson(root,person->name)==NULL)
		{
			insertNode(root,person);
		}
		i++;
	}
	do
	{
		printf("\nEnter couple:");	
		fgets(input,sizeof(input),stdin); 
		input[strlen(input)-1] = '\0';
		if(strcasecmp(input,"DONE") != 0)
		{
			if(sscanf(input,"%s %s",couple1,couple2)==2)
			{
				pPersonA = findPerson(root,couple1);
				pPersonB = findPerson(root,couple2);
				if(pPersonA == NULL) 
				{
					printf("Name %s not exist in data base",couple1);
				}
				else if(pPersonB == NULL) {
					printf("Name %s not exist in data base",couple2);
				}
				else 
				{
					addcouple(pPersonA,pPersonB);
				}
			}	
			else
			{
				printf("Error invalid couple name");
			}
		}
	}
	while(strcasecmp(input,"DONE") != 0);
	printf("\nCouples:\n");
	printCouple(root);
	freePerson(root);
}
