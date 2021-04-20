/* emergency.c
 *
 * Lab 11: This lab is intended to give you practice writing a program that uses a max­heap to do a heap sort.
 *
 * Created by Panithi Suwanno (Big) 63070503426
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "abstractHeap.h"

typedef struct
{
	char name[32];       /* first name of the patient */
	char problem[32];    /* reason for coming to the emergency room */
	int severity;        /* indicates how serious the problem is ­ higher values mean more serious */
} PATIENT_T;

void usage() 
{
	printf("Usage:   ./emergency [inputfile] [outputfile]\n\n");
	exit(0);
}

/* Compare two patients. If patient1 severity is lower than patient2 severity, return ­-1.
 * If the severity values are the same, return 0. 
 * If patient1 severity is higher than patient2 severity, return 1.
 */
int comparePatients(void* patient1, void* patient2)
{
	PATIENT_T* p1 = (PATIENT_T*) patient1;
	PATIENT_T* p2 = (PATIENT_T*) patient2;
	if(p1->severity < p2->severity)
		return -1;
	else if(p1->severity > p2->severity)
		return 1;
	else 
		return 0;
}

int main(int argc, char *argv[]) 
{
	int bMaxHeap = 1;
	int capacity = 999;
	char inputfile[32];
	char outputfile[32];
	FILE *pIn = NULL;
	FILE *pOut = NULL;
	/* storage */
	PATIENT_T *person;
	char input[128];
	char name[32];
	char problem[32];
	int severity;

	if(argc < 3)
	{
		usage();
	}
	strcpy(inputfile, argv[1]);
	strcpy(outputfile, argv[2]);
	pIn = fopen(inputfile, "r");
	if (pIn == NULL) 
	{
		printf(">>> Error! Cannot opening INPUT file '%s'\n", inputfile);
		exit(1);
	}    

	/* Initialize heap */
	if (!initHeap(comparePatients, bMaxHeap, capacity))
	{
		printf(">>> Error! Cannot initialize heap\n");
		exit(2);
	}
	else
		printf("Successfully initialized the heap\n");

	/* Read the lines from the input file */
	while(fgets(input, sizeof(input), pIn) != NULL)
	{
		memset(name, '\0', sizeof(name));
		memset(problem, '\0', sizeof(problem));

		person = (PATIENT_T *) calloc(1, sizeof(PATIENT_T));
		if(person == NULL)
		{
			printf(">>> Error! Memory allocation\n");
			exit(3);
		}

		sscanf(input, "%s %s %d", name, problem, &severity);
		strcpy(person->name, name);
		strcpy(person->problem, problem);
		person->severity = severity;
		heapInsert(person);
	}
	fclose(pIn);

	pOut = fopen(outputfile, "w");
	if(pOut == NULL) 
	{
		printf(">>> Error! Cannot opening OUTPUT file '%s'\n", outputfile);
		exit(4);
	}
	
	while(heapPeek() != NULL)
	{
		person = heapExtract();
		fprintf(pOut, "%s %s %d\n", person->name, person->problem, person->severity);
		free(person);
	}
	fclose(pOut);

	printf("Finished the program!\n");
}
