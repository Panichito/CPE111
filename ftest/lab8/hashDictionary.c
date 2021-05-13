/*
 * hashDictionary.c
 * Created by Panithi Suwanno (Big) 63070503426
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "abstractHashTable.h"
#include "timeFunctions.h"
#define BUCKET_COUNT 503

typedef struct 
{
	char word[32];
	char definition[128];
} DICT_ENTRY_T;

void usage()
{
	printf("Usage: ./hashDictionary [inputfile]\n");
	exit(0);
}

unsigned int bitwiseOpHash(char* key)
{
	unsigned int result = 0;
	unsigned int tmp = 0;
	int size = hashTableSize();
	for(int i = 0; i < strlen(key); i++)
	{
		/* shift up four bits then add in next char */ 
		result = (result << 4) + key[i];
		if(tmp = (result & 0xf0000000))  /* if high bit is set */
		{
			/* xor result with down shifted tmp */
			result = result ^ (tmp >> 24);
			/* then xor with tmp itself */
			result = result ^ tmp;
		}
	}
	result = result % size;   /* make it fit in the table size */ 
	return result;
}

void buildDictionary(FILE* pIn)
{
	int pDummy;
	char input[512], word[64], definition[512];
	DICT_ENTRY_T* one = NULL;
	while(fgets(input, sizeof(input), pIn) != NULL)
	{
		sscanf(input, "%[^|]|%[^\n]", word, definition);
		one = (DICT_ENTRY_T*) calloc(1, sizeof(DICT_ENTRY_T));
		if(one == NULL)
		{
			printf("Error memory allocation\n");
			exit(2);
		}
		strcpy(one->word, word);
		strcpy(one->definition, definition);
		if(!hashTableInsert(word, one, &pDummy))
		{
			printf("  Cannot allocated memory for hash table!\n");
			exit(2);
		}
	}
}

void printDefinitions(char* word)
{
	DICT_ENTRY_T* find = NULL;
	recordTime(1);
	find = hashTableLookup(word);
	long microseconds = recordTime(0);
	if(find != NULL)
		printf("%-20s ==> %-128s\n", find->word, find->definition);
	else 
		printf("Word '%s' is not found in the dictionary\n", word);
	printf("Lookup required %ld microseconds\n\n", microseconds);
}

int main(int argc, char* argv[]) 
{
	if(!hashTableInit(BUCKET_COUNT, &bitwiseOpHash))
	{
		printf("Initialization failed!\n");
		exit(1);
	}
	printf("Initialization succeed!\n");
	FILE* pIn = NULL;
	if(argc < 2)
		usage();
	pIn = fopen(argv[1], "r");
	if(pIn == NULL)
	{
		printf("Error - cannot open file\n");
		exit(1);
	}
	buildDictionary(pIn);
	fclose(pIn);
	while(1)
	{
		char input[64], word[64];
		printf("Find definition for what word (<CR> to exit)? ");
		fgets(input, sizeof(input), stdin);
		sscanf(input, "%s", word);
		if(strlen(word) == 0)
			continue;
		printDefinitions(word);
	}
	hashTableFree();
}
