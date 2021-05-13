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
	struct _person *next;
} PERSON_T;

void usage() 
{
	printf("Usage: ./couple [inputfile] \n\n");
	exit(0);
}

PERSON_T* find(char *name, PERSON_T* head)
{
	PERSON_T* current = head;
	while(current != NULL)
	{
		if(strcasecmp(name, current->name) == 0)
			return current;
		current = current->next;
	}
	return NULL;
}

void make(PERSON_T* p1, PERSON_T* p2)
{
	if(p1->pPartner != NULL) 
	{
		printf("\t%s is breaing up with %s and is now a couple with %s\n", p1->name, p1->pPartner->name, p2->name);
		p1->pPartner->pPartner = NULL;
	}
	if(p2->pPartner != NULL)
	{
		printf("\t%s is breaing up with %s and is now a couple with %s\n", p2->name, p2->pPartner->name, p1->name);
		p2->pPartner->pPartner = NULL;
	}
	p1->pPartner = p2;
	p2->pPartner = p1;
}

void printAll(PERSON_T* head)
{
	PERSON_T* current = head;
	while(current != NULL)
	{
		printf("\t%s %s\n", current->name, current->gender);
		current = current->next;
	}
}

void delete(char* name, PERSON_T** head)
{
	PERSON_T* cur = *head;
	PERSON_T* prev = NULL;;
	PERSON_T* del = NULL;;
	while(cur != NULL)
	{
		prev = del;
		del = cur;
		cur = cur->next;
		if(strcasecmp(name, del->name) == 0) 
		{
			if(prev == NULL)  /* delete head */
			{
				*head = cur;
			}
			else 
			{
				prev->next = cur;
			}
			free(del);
			break;
		}
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
	char c1[32] = "\0";  /* abbreviation couple1 */
	char c2[32] = "\0";  /* abbreciation couple2 */
	PERSON_T* p1 = NULL;  /* abbreviation partner1 */
	PERSON_T* p2 = NULL;  /* abbreciation partner2 */
	PERSON_T* head = NULL;
	PERSON_T* tail = NULL;
	PERSON_T* person = NULL;

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
		if(head == NULL)
			head = tail = person;
		else 
		{
			tail->next = person;
			tail = person;
		}
		countLine++;
	}
	fclose(pIn);

	/* run case */
	printf("Welcome to couples program\nRead %d people:\n", countLine);
	printAll(head);

	printf("Do you want to delete people ? (type Y) ");
	fgets(input, sizeof(input), stdin);
	sscanf(input, "%s", input);
	if(strcasecmp(input, "Y") == 0)
	{
		while(isLoop)
		{
			printf("Enter name to delete: ");
			fgets(input, sizeof(input), stdin);
			sscanf(input, "%s", input);
			if(find(input, head))
			{
				delete(input, &head);
				printf("-- %s has been deleted. ", input);
			}
			else 
				printf("-- %s not found in the list. ", input);

			while(1) 
			{
				printf("Continue? (Y/n) ");
				fgets(input, sizeof(input), stdin);
				sscanf(input, "%s", input);
				if(strcasecmp(input, "Y") == 0) 
					break;
				else if(strcasecmp(input, "N") == 0) 
				{
					isLoop = 0;
					break;
				}
				else 
					continue;
			}
		}
	}
	printAll(head);

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
		p1 = find(c1, head);
		p2 = find(c2, head);
		if(!p1) 
		{
			printf("\t%s not exist\n", c1);
			continue;
		}
		if(!p2) 
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
	PERSON_T* show = head;  /* for printing all couples */
	while(show != NULL)
	{
		if(show->pPartner != NULL && strcmp(show->gender, "M") == 0)
			printf("\t%s is coupled with %s\n",show->name, show->pPartner->name);
		show = show->next;
	}
}
