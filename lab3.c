/* linkCouples.c  adjust from couples.c
 *
 * Created by Panithi Suwanno(Big) 63070503426 for LAB3
 * 2 FEB 2020 
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct _person {
	char name[32];
	char gender[2];
	struct _person *pPartner;
	struct _person *pNext;
} PERSON_T;

void printAllPeople(PERSON_T *pListHead) {
	PERSON_T *current = pListHead;
	int order = 1;
	while(current != NULL) {
		printf("%d) %10s \t%s\n",order,current->name,current->gender);
		current = current->pNext;
		order++;
	}
}

void usage() {
	printf("Usage:   ./listCouples [inputfile]\n\n");
	exit(0);
}

int findPeople(PERSON_T *pListHead, char *nameDelete) {
	PERSON_T *current = pListHead;
	while(current != NULL) {
		if(strcasecmp(current->name,nameDelete) == 0) {
			return 1;
		}
		current = current->pNext;
	}
	if(current == NULL) {
		return 0;
	}
}

void deletePeople(PERSON_T **pHead, char *nameDelete) {
	PERSON_T *prevPerson = NULL;
	PERSON_T *delPerson = NULL;
	PERSON_T *thisPerson = *pHead;
	while(thisPerson != NULL) {
		prevPerson = delPerson;
		delPerson = thisPerson;
		thisPerson = thisPerson->pNext;
		if(strcasecmp(nameDelete,delPerson->name) == 0) {
			if(prevPerson == NULL) {        // delete the first node
				*pHead = delPerson->pNext;    // move head point to next position instead
			}
			else {
				prevPerson->pNext = delPerson->pNext;
				//prevPerson->pNext = thisPerson;    // an optional way to do
			}
			free(delPerson);
			break;
		}
	}
}

int main(int argc, char *argv[]) {
	FILE *pIn = NULL;
	char input[128];
	char filename[64];
	PERSON_T *pPerson = NULL;
	PERSON_T *pHead = NULL;
	PERSON_T *pTail = NULL;
	char nameRead[32];
	char genderRead[2];
	if(argc < 2) {
		usage();
	}
	strcpy(filename,argv[1]);
	pIn = fopen(filename,"r");
	if (pIn == NULL) {
		printf("Error opening input file '%s'\n",filename);
		exit(1);
	}    
	int count = 0;
	while(fgets(input,sizeof(input),pIn) != NULL) {
		memset(nameRead,'\0',sizeof(nameRead));
		memset(genderRead,'\0',sizeof(genderRead));
		sscanf(input,"%s %s",nameRead,genderRead);
		pPerson = (PERSON_T*) calloc(1,sizeof(PERSON_T));
		if(pPerson == NULL) {
			printf("Memory allocation error - exiting\n");
			exit(2);
		}
		strncpy(pPerson->name,nameRead,sizeof(pPerson->name)-1);
		strncpy(pPerson->gender,genderRead,sizeof(pPerson->gender)-1);
		if(pHead == NULL) {  // first item
			pHead = pTail = pPerson;
		}
		else {
			pTail->pNext = pPerson;
			pTail = pPerson;
		}
		count++;
	}
	printf("Read %d people from '%s'\n",count,filename);
	fclose(pIn);
	printAllPeople(pHead);
	char nameDelete[32];
	// Ask user to delete people or not
	while(1) {
		printf("Do you want to delete people? ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%s",input);
		if(strcasecmp(input,"N") == 0) {
			printf("Good Bye!\n");
			break;
		}
		else if(strcasecmp(input,"Y") == 0) {
			while(1) {
				printf("Enter name to delete: ");
				fgets(nameDelete,sizeof(nameDelete),stdin);
				sscanf(nameDelete,"%s",nameDelete);
				if(!findPeople(pHead,nameDelete)) {
					printf("-- %s not found in the list. Continue? ",nameDelete);
					fgets(input,sizeof(input),stdin);
					sscanf(input,"%s",input);
					if(strcasecmp(input,"N") == 0) {
						printf("Good Bye!\n");
						break;
					}
					else if(strcasecmp(input,"Y") == 0) {
						continue;
					}
					else {
						printf("  Invalid choice, Please try again!\n");
						continue;
					}
				}
				else {
					deletePeople(&pHead,nameDelete);
					printAllPeople(pHead);
					printf("-- %s has been deleted. Continue? ",nameDelete);
					fgets(input,sizeof(input),stdin);
					sscanf(input,"%s",input);
					if(strcasecmp(input,"N") == 0) {
						printf("Good Bye!\n");
						break;
					}
					else if(strcasecmp(input,"Y") == 0) {
						continue;
					}
					else {
						printf("  Invalid choice, Please try again!\n");
						continue;
					}
				}
			}
			break;
		}
		else {
			printf("  Invalid choice, Please try again!\n");
		}
	}
}
