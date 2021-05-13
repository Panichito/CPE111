/* 
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
} PERSON_T;

void usage() 
{
	printf("Usage: ./couple [inputfile] \n\n");
	exit(0);
}

PERSON_T *find(char* name, PERSON_T** people, int count)
{
	PERSON_T *pFound = NULL;
	for(int i = 0; i < count; ++i) 
	{
		if(strcasecmp(name, people[i]->name) == 0)
		{
			pFound = people[i];
			break;
		}
	}
	return pFound;
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

int main(int argc, char* argv[])
{
	FILE *pIn = NULL;
	char input[128];
	int countLine = 0;
	PERSON_T **people = NULL;  /* array of people who might be related */
	PERSON_T *person = NULL;
	char name[64];
	char gender[2];
	int i = 0;
	char c1[32] = "\0";  /* abbreviation couple1 */
	char c2[32] = "\0";  /* abbreciation couple2 */
	PERSON_T* p1 = NULL; /* abbreviation person1 */
	PERSON_T* p2 = NULL; /* abbreviation person2 */

	if(argc < 2) 
		usage();
	pIn = fopen(argv[1], "r");
	if(pIn == NULL) 
	{
		printf("Cannot open input file for reading\n");
		exit(1);
	}
	/* read file */
	if(fgets(input, sizeof(input), pIn) == NULL)
	{
		printf("File seems to be empty\n");
		exit(2);
	}
	sscanf(input, "%d", &countLine);
	printf("%d\n", countLine);
	people = (PERSON_T**) calloc(countLine, sizeof(PERSON_T*));
	if(people == NULL) 
	{
		printf("Error allocating array\n");
		exit(3);
	}

	for(i = 0; i < countLine; ++i)
	{
		if(fgets(input, sizeof(input), pIn) != NULL) 
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
			people[i] = person;
		}
	}
	fclose(pIn);
	printf("Welcome tp couples program\nRead %d people:\n", i);
	for(int j = 0; j < i; ++j) {
		printf("\t%s %s\n", people[j]->name, people[j]->gender);
	}
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
		p1 = find(c1, people, countLine);
		p2 = find(c2, people, countLine);
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
	for(int j = 0; j < countLine; ++j) 
	{
		if(people[j]->pPartner != NULL && strcmp(people[j]->gender, "M") == 0)
		{
			printf("\t%s is coupled with %s\n",people[j]->name, people[j]->pPartner->name);
		}
	}
}
