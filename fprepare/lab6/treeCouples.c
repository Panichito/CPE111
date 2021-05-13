/* linkCouples.c
 * Created by Panithi Suwanno (Big) 64070503426
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _person
{
	char name[32];
	char gender[2];
	struct _person *pPartner;
	struct _person *left;
	struct _person *right;
} PERSON_T;

void usage() 
{
	printf("Usage: ./treeCouples [inputfile] \n\n");
	exit(0);
}

PERSON_T* findPerson(char *name, PERSON_T* root)
{
	PERSON_T* found = NULL;
	if(root != NULL) 
	{
		if(strcmp(name, root->name) == 0) 
			found = root;
		else if(strcmp(name, root->name) < 0)
			found = findPerson(name, root->left);
		else
			found = findPerson(name, root->right);
	}
	return found;
}

void make(PERSON_T* p1, PERSON_T* p2)
{
	if(p1->pPartner != NULL) 
	{
		printf("\t%s is breaking up with %s and is now a couple with %s\n", p1->name, p1->pPartner->name, p2->name);
		p1->pPartner->pPartner = NULL;
	}
	if(p2->pPartner != NULL)
	{
		printf("\t%s is breaking up with %s and is now a couple with %s\n", p2->name, p2->pPartner->name, p1->name);
		p2->pPartner->pPartner = NULL;
	}
	p1->pPartner = p2;
	p2->pPartner = p1;
}

void printAll(PERSON_T* root)
{
	if(root->left != NULL)
		printAll(root->left);
	printf("\t%s %s\n", root->name, root->gender);
	if(root->right != NULL)
		printAll(root->right);
}

void printCouples(PERSON_T* root)
{
	if(root->left != NULL)
		printCouples(root->left);
	if(root->pPartner != NULL && strcmp(root->gender, "M") == 0)
	{
		printf("\t%s is coupled with %s\n", root->name, root->pPartner->name);
	}
	if(root->right != NULL)
		printCouples(root->right);
}

void insertNode(PERSON_T* root, PERSON_T* person)
{
	/* compare with root node */
	if(strcmp(person->name, root->name) < 0)  /* left */
	{
		if(root->left == NULL)
		{
			root->left = person;
			printf("Adding '%s' as a left child of '%s'\n", person->name, root->name);
		}
		else
			insertNode(root->left, person);
	}
	else /* right */
	{
		if(root->right == NULL)
		{
			root->right = person;
			printf("Adding '%s' as a left child of '%s'\n", person->name, root->name);
		}
		else 
			insertNode(root->right, person);
	}
}

int main(int argc, char* argv[])
{
	FILE *pIn = NULL;
	int isLoop = 1;
	int countLine = 0;
	char name[64];
	char gender[2];
	char input[128];
	char c1[32] = "\0";   /* abbreviation couple1 */
	char c2[32] = "\0";   /* abbreciation couple2 */
	PERSON_T* p1 = NULL;  /* abbreviation partner1 */
	PERSON_T* p2 = NULL;  /* abbreciation partner2 */
	PERSON_T* person = NULL;
	PERSON_T* root = NULL;

	if(argc < 2) 
		usage();
	pIn = fopen(argv[1], "r");
	if(pIn == NULL) 
	{
		printf("Cannot open input file for reading\n");
		exit(1);
	}
	/* read file */
	while(fgets(input, sizeof(input), pIn) != NULL) 
	{
		sscanf(input, "%s %s", name, gender);
		person = (PERSON_T*) calloc(1, sizeof(PERSON_T));
		if(person == NULL) 
		{
			printf("Error allocating when creating a person\n");
			exit(5);
		}
		strcpy(person->name, name);
		strcpy(person->gender, gender);
		person->gender[0] = toupper(person->gender[0]);
		if(root == NULL)
			root = person;
		else if(findPerson(person->name, root) == NULL)
			insertNode(root, person);
		countLine++;
	}
	fclose(pIn);

	/* run case */
	printf("\nWelcome to couples program\nRead %d people:\n", countLine);
	printAll(root);

	while(1)
	{
		memset(c1, 0, sizeof(c1));
		memset(c2, 0, sizeof(c2));
		printf("Enter couple: ");
		fgets(input, sizeof(input), stdin);
		sscanf(input, "%s %s", c1, c2);
		if(strcasecmp(c1, "DONE") == 0) 
			break;
		if(strcmp(c1, "\0") == 0 || strcmp(c2, "\0") == 0)
		{
			printf("\tError: you must enter two names\n");
			continue;
		}
		p1 = findPerson(c1, root);
		p2 = findPerson(c2, root);
		printf("%s %s\n", c1, c2);
		printf("%s %s\n", p1->name, p2->name);
		if(p1 == NULL) 
		{
			printf("\t%s not exist\n", c1);
			continue;
		}
		if(p2 == NULL) 
		{
			printf("\t%s not exist\n", c2);
			continue;
		}
		if(strcmp(p1->gender, p2->gender) == 0)
		{
			printf("\tSame gender not allowed\n");
			continue;
		}
		make(p1, p2);
	}
	printf("Couples:\n");
	printCouples(root);
}
