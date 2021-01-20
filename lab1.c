/* couples.c
 * This program will read a file with the names and genders of people,
 *  and create a dynamic array to hold structures representing these people.
 * Let user ask for pairs of people who are in a couple, then shows the results.
 *
 * Created by Panithi Suwanno(Big) 63070503426 for LAB1
 * 19 JAN 2021 - 16.55 PM
 * UPDATE: 20 JAN 2020 - 12.33 AM
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 1000  // for max couples

typedef struct _person {
	char name[32];               /* person's name */
	char gender[2];              /* person's gender */
	struct _person *pPartner;    /* pointer to another PERSON_T who is this person's partner.*/
} PERSON_T;


int main(int argc, char *argv[]) {
	FILE *pIn = NULL;
	char input[128];
	char filename[64];
	PERSON_T **people = NULL;
	PERSON_T *pPerson = NULL;
	if(argc < 2) {
		printf("  Please specify name for input file\n");
		exit(1);
	}
	sscanf(argv[1],"%s",filename);
	// open for count the total people in the file
	// assume that we don't know how many exact number
	pIn = fopen(filename,"r");
	if(pIn == NULL) {
		printf("  Error cannot open '%s' for reading\n",filename);
		exit(2);
	}
	int count = 0;  // Line counter
	fgets(input,sizeof(input),pIn);
	sscanf(input,"%d",&count);
	if(count == 0) {
		printf("  Invalid input file '%s' indicates 0 people\n",filename);
		exit(3);
	}
	people = (PERSON_T**) calloc(count,sizeof(PERSON_T*));
	if(people == NULL) {
		printf("  Unable to allocate memory for %d people\n",count);
		exit(4);
	}
	for(int i = 0; i < count; i++) {
		if(fgets(input,sizeof(input),pIn) == NULL) {
			printf("   Unexpected end of file at line %d\n",i+1);
			break;
		}
		pPerson = (PERSON_T*) calloc(1,sizeof(PERSON_T));
		if(pPerson == NULL) {
			printf("  Error allocating a person\n");
			exit(5);
		}
		people[i] = pPerson;
		sscanf(input,"%s %s",people[i]->name,people[i]->gender);
	}
	fclose(pIn);
	// User Interface
	printf("Welcome to couples program.\nRead %d people:\n",count);
	for(int i = 0; i < count; i++) {  // secmentation false (core dumped)
		printf("  %s %s\n",people[i]->name,people[i]->gender);
	}
	int couple[MAX];  // array to store the relasionship amoung group of people by index method
	memset(couple,0,sizeof(couple));
	while(1) {
		int valid = 0, index1, index2;
		char name1[64], name2[64];
		printf("Enter couple: ");
		fgets(input,sizeof(input),stdin);
		memset(name1,'\0',sizeof(name1));
		memset(name2,'\0',sizeof(name2));
		sscanf(input,"%s %s",name1,name2);
		if(strcasecmp(name1,"DONE") == 0) {
			break;
		}
		if(strlen(name2) == 0) { 
			valid = 0;
			printf("    Error: you must enter two names\n");
			continue;
		}
		if(strcasecmp(name1,name2) == 0) {
			printf("    Error: duplicate name not allowed\n");
			continue;
		}
		for(int i = 0; i < count; i++) {
			if(strcasecmp(name1,people[i]->name) == 0) {
				index1 = i;
				valid = 1;
				break;
			}
			else if(i == count-1) {
				printf("    Error: person '%s' does not exist\n",name1);
				valid = 0;
			}
		}
		if(valid) {
			for(int i = 0; i < count; i++) {
				if(strcasecmp(name2,people[i]->name) == 0) {
					index2 = i;
					valid = 1;
					break;
				}
				else if(i == count-1) {
					printf("    Error: person '%s' does not exist\n",name2);
					valid = 0;
				}
			}
		}
		if(valid) {
			if(strcasecmp(people[index1]->gender,people[index2]->gender) == 0) {
				printf("    Error: cannot create a couple with same gender\n");
			}
			else {
				if(couple[index1] == 0 && couple[index2] == 0) {
					couple[index1] = index2;
					couple[index2] = index1;
				}
				else if(couple[index1] != 0 && couple[index2] == 0) {
					printf("    %s is breaking up with %s and is now a couple with %s\n",people[index1]->name,people[couple[index1]]->name,people[index2]->name);
					couple[couple[index1]] == 0;  // become single now!
					couple[index1] = index2;
					couple[index2] = index1;
				}
				else if(couple[index2] != 0 && couple[index2] == 0) {
					printf("    %s is breaking up with %s and is now a couple with %s\n",people[index2]->name,people[couple[index2]]->name,people[index1]->name);
					couple[couple[index2]] == 0;  // become single now!
					couple[index1] = index2;
					couple[index2] = index1;
				}
				else if(couple[index1] != 0 && couple[index2] != 0) {  // means name1 & name2 has their own spouse
					printf("    %s is breaking up with %s and is now a couple with %s\n",people[index1]->name,people[couple[index1]]->name,people[index2]->name);
					couple[couple[index1]] = 0;  // become single now!
					couple[couple[index2]] = 0;
					couple[index1] = index2;
					couple[index2] = index1;
				}
			}
		}
	}
	printf("\nCouples:\n");
	for(int i = 0; i < count; i++) {
		if(couple[i] != 0 && strcmp(people[couple[i]]->gender,"M") == 0) {
			printf("    %s is coupled with %s\n",people[couple[i]]->name,people[i]->name);
		}
	}
	free(people);
}
