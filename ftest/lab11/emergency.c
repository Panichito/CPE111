/*
 * emergency.c 
 * Created by Panithi Suwanno (Big) 63070503426
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "abstractHeap.h"

typedef struct
{
	char name[32];
	char problem[32];
	int severity;
} PATIENT_T;

int comparePatients(void* patient1, void* patient2)
{
	PATIENT_T* p1 = patient1;
	PATIENT_T* p2 = patient2;
	if(p1->severity > p2->severity)
		return 1;
	else if(p1->severity < p2->severity)
		return -1;
	else 
		return 0;
}

void usage()
{
	printf("Usage: ./emergency [inputfile] [outputfile]\n");
	exit(0);
}

int main(int argc, char* argv[])
{
	FILE* pIn = NULL;
	FILE* pOut = NULL;
	PATIENT_T* person = NULL;
	char input[128];
	char name[32], problem[32];
	int severity;
	int bMaxHeap = 1;  /* Max heap */
	int capacity = 50;  /* fifty is enough */
	if(argc < 3) 
		usage();
	pIn = fopen(argv[1], "r");
	pOut = fopen(argv[2], "w");
	if(pIn == NULL || pOut == NULL)
	{
		printf("Unable to open file!\n");
		exit(1);
	}
	if(!initHeap(comparePatients, bMaxHeap, capacity))
	{
		printf("Heap initialize falied!\n");
		exit(2);
	}
	printf("Heap initialize succeed!\n");
	while(fgets(input, sizeof(input), pIn) != NULL)
	{
		sscanf(input, "%s %s %d", name, problem, &severity);
		person = (PATIENT_T*) calloc(1, sizeof(PATIENT_T));
		if(person == NULL)
		{
			printf("Error memory allocation for patient!\n");
			exit(3);
		}
		strcpy(person->name, name);
		strcpy(person->problem, problem);
		person->severity = severity;
		heapInsert(person);
	}
	fclose(pIn);
	
	person = heapExtract();
	while(person != NULL)
	{
		fprintf(pOut, "%s %s %d\n", person->name, person->problem, person->severity);
		free(person);
		person = heapExtract();
	}
	fclose(pOut);

	return 0;
}
