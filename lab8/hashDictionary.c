/* hashDictionary.c
 *
 * A program stores multiples words and definitions. After building the dictionary, allow the user to request the definitions of words.
 * Each time user enters a word, look it up the hash table to find definition and print it. (Do some experiments to see size of hash table affects the retrieval time)
 *
 * Created by Panithi Suwanno (Big) 63070503426
 * Lab8: 23 MAR 2021
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "timeFunctions.h"
#include "abstractHashTable.h"
#define ll long long
#define BUCKET_COUNT 503
#define filename "wordlist.txt"

typedef struct
{
	char word[32];
	char definition[128];
} DICT_ENTRY_T;

unsigned int bitwiseOpHash(char* key)
{
	unsigned int result = 0;
	unsigned int tmp = 0;
	int size = hashTableSize();
	int i = 0;
	for(i = 0; i < strlen(key); i++)
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

void buildDictionary()
{
	int pDummy;  /* just a dummy */
	char input[256];
	char word[32];
	char definition[256];
	FILE *pIn = NULL;
	DICT_ENTRY_T *oneword;
	pIn = fopen(filename, "r");
	if(pIn == NULL)
	{
		printf("  Error cannot open 'wordlist.txt' for reading\n");
		exit(0);
	}
	while(fgets(input, sizeof(input), pIn) != NULL)
	{
		memset(word, '\0', sizeof(word));
		memset(definition, '\0', sizeof(definition));
		sscanf(input, "%[^|]|%[^\n]", word, definition);
		oneword = (DICT_ENTRY_T *)calloc(1, sizeof(DICT_ENTRY_T));
		if (oneword == NULL)
		{
			printf("  Error memmory allocation - exiting\n");
			exit(0);
		}
		strcpy(oneword->word, word);
		strcpy(oneword->definition, definition);
		if(!hashTableInsert(word, oneword, &pDummy)) 
		{
			printf("  Cannot allocated memory - exiting\n");
			exit(0);
		}
	}
	fclose(pIn);
}

void printDefinition(char *input)
{
	DICT_ENTRY_T *find = NULL;
	recordTime(1);             
	/* code to call function to lookup the word */             
	find = hashTableLookup(input);
	ll microseconds = recordTime(0);             
	if(find != NULL) 
		printf(" %s\n", find->definition);
	/* print definition... or message about not finding word */ 
	else 
		printf(" Not found in dictionary\n");
	printf("Lookup required %lld microseconds\n\n", microseconds); 
}

int main()
{
	char input[32];
	if(!hashTableInit(BUCKET_COUNT, &bitwiseOpHash))
		printf("Initialization falied!\n");
	printf("Initialization succeed!\n");
	buildDictionary();
	while (1)
	{
		printf("Enter word (-1 to exit): ");
		fgets(input, sizeof(input), stdin);
		sscanf(input, "%[^\n]", input);
		if (input[0] == '\n')
		{
			printf("  Please type again!\n");
			continue;
		}
		if (strcasecmp(input, "-1") == 0)  /* exit the program */
		{
			hashTableFree();
			break;
		}
		printf("  %s >>", input);
		printDefinition(input);
	}
	printf("\n\tGood Bye!\n\n");
}
