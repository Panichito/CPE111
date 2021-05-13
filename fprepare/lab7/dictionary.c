/*
 * dictionary.c
 * Created by Panithi Suwanno (Big) 63070503426
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "linkedListUtil.h"

typedef struct 
{
	char word[32];
	char definition[128];
} DICT_ENTRY_T;

void usage()
{
	printf("Usage: ./dictionary [inputfile]\n");
	exit(0);
}

int getDictIndex(char* word)
{
	char c = tolower(word[0]);
	return c - 'a';
}

void buildDictionary(LIST_HANDLE dictionary[26], FILE* pIn)
{
	int index = 0;
	char input[512], word[64], definition[512];
	DICT_ENTRY_T* one = NULL;
	while(fgets(input, sizeof(input), pIn) != NULL)
	{
		sscanf(input, "%[^:]:%[^\n]", word, definition);
		one = (DICT_ENTRY_T*) calloc(1, sizeof(DICT_ENTRY_T));
		if(one == NULL)
		{
			printf("Error memory allocation\n");
			exit(2);
		}
		strcpy(one->word, word);
		strcpy(one->definition, definition);
		index = getDictIndex(one->word);
		if(dictionary[index] == NULL)  /* no linked list yet */
		{
			dictionary[index] = newList();
		}
		listInsertEnd(dictionary[index], one);
	}
}

void printAll(LIST_HANDLE dictionary[26])
{
	DICT_ENTRY_T* data = NULL;
	for(int i = 0; i < 26; ++i)
	{
		LIST_HANDLE list = dictionary[i];
		if(list != NULL)
		{
			listReset(list);
			data = listGetNext(list);
			while(data != NULL)
			{
				printf("%-20s ==> %-128s\n", data->word, data->definition);
				data = listGetNext(list);
			}
		}
	}
}

void printDefinitions(LIST_HANDLE dictionary[26], char* word)
{
	for(int i = 0; i < strlen(word); ++i)  /* preventing getDictIndex error! */
	{
		if(!isalpha(word[i]))
		{
			printf("Word '%s' is not found in the dictionary\n", word);
			return;
		}
	}
	int index = getDictIndex(word);
	LIST_HANDLE list = dictionary[index];
	DICT_ENTRY_T* data = NULL;
	if(list == NULL)
	{
		printf("Word '%s' is not found in the dictionary\n", word);
		return;
	}
	else 
	{
		listReset(list);
		data = listGetNext(list);
		while(data != NULL)
		{
			if(strcasecmp(data->word, word) == 0)
			{
				printf("%-20s ==> %-128s\n", data->word, data->definition);
				return;
			}
			data = listGetNext(list);
		}
	}
	printf("Word '%s' is not found in the dictionary\n", word);
}

void freeDictionary(LIST_HANDLE dictionary[26])
{
	DICT_ENTRY_T* data = NULL;
	LIST_HANDLE list = NULL;
	for(int i = 0; i < 26; ++i)
	{
		list = dictionary[i];
		if(list != NULL)
		{
			listReset(list);
			data = listGetNext(list);
			while(data != NULL)
			{
				free(data);
				data = listGetNext(list);
			}
			listDestroy(list);
		}
	}
}

int main(int argc, char* argv[]) 
{
	LIST_HANDLE dictionary[26];
	memset(dictionary, 0, sizeof(dictionary));
	FILE* pIn = NULL;
	if(argc < 2)
		usage();
	pIn = fopen(argv[1], "r");
	if(pIn == NULL)
	{
		printf("Error - cannot open file\n");
		exit(1);
	}
	buildDictionary(dictionary, pIn);
	fclose(pIn);
	printAll(dictionary);
	while(1)
	{
		char input[64], word[64];
		printf("Find definition for what word (<CR> to exit)? ");
		fgets(input, sizeof(input), stdin);
		sscanf(input, "%s", word);
		if(strlen(word) == 0)
			continue;
		printDefinitions(dictionary, word);
	}
	freeDictionary(dictionary);
}
