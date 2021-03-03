/* dictionary.c 
 *
 * A program called dictionary.c that stores multiple words and definitions. 
 * After building the dictionary, allow the user to request the definitions 
 * of words. Each time the user enters a word, look it up in the dictionary 
 * to find its definition or definitions and print them.
 * 
 * Created by Panithi 
 * Lab7: 2 MAR 2020
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "linkedListUtil.h"
#define filename wordlist.txt
typedef struct 
{
    char word[32];
    char definition[128];
} DICT_ENTRY_T;
int getDictIndex(char *word)
{
    char c=tolower(word[0]);
    return (c-'a');
}
void buildDictionary(LIST_HANDLE *dictionary) 
{
    char input[256];
    char word[32];
    char definition[256];
    FILE *pIn=NULL;
    int ind=0;  /* index */
    DICT_ENTRY_T *oneWord;
    pIn = fopen("wordlist.txt","r");
    if(pIn==NULL)
       {
        printf("  Error cannot open 'wordlist.txt' for reading\n");
        exit(0);
    }
    while(fgets(input,sizeof(input),pIn)!=NULL) 
    {
        memset(word,'\0',sizeof(word));
        memset(definition,'\0',sizeof(definition));
        sscanf(input,"%[^:]:%[^\n]",word,definition);
        oneWord=(DICT_ENTRY_T*)calloc(1,sizeof(DICT_ENTRY_T));
        if(oneWord==NULL) 
        {
            printf("  Error memmory allocation\n");
            exit(0);
        }
        strcpy(oneWord->word,word);
        strcpy(oneWord->definition, definition);
        ind = getDictIndex(oneWord->word);
        /* printf(" %d\n", ind); */
        if (ind >= 0 && ind <= 25)
        {
            if (dictionary[ind] == NULL)
            {
                dictionary[ind] = newList();
            }
            listInsertEnd(dictionary[ind], oneWord);
        }
    }
    fclose(pIn);
}
void printDictionary(LIST_HANDLE *dictionary)
{
    LIST_HANDLE list=NULL;
    DICT_ENTRY_T *data=NULL;
    for(int i=0; i<=25; ++i) 
    {
        list=dictionary[i];
        if(list==NULL) 
        {
            printf("  No word with letter '%c'\n",i+'A');
        }
        else
        {
            listReset(list);
            data=listGetNext(list);
            while(data!=NULL) 
            {
                printf("  %s: %s\n",data->word,data->definition);
                data=listGetNext(list);
            }
        }
    }
}
void freeDictionary(LIST_HANDLE *dictionary)  
{
    LIST_HANDLE list=NULL;
    DICT_ENTRY_T *data=NULL;
    for(int i=0; i<=25; ++i)
    {
        list=dictionary[i];
        if(list!=NULL)
        {
            listReset(list);
            data=listGetNext(list);
        }
        while(data!=NULL)
        {
            free(data);
            data=listGetNext(list);
        }
        free(list);
    }
}
int printDefinition(LIST_HANDLE *dictionary, char *input) 
{
    int found=0;
    LIST_HANDLE list=NULL;
    DICT_ENTRY_T *data=NULL;
    for(int i=0; i<=25; ++i)
    {
        list=dictionary[i];
        if(list!=NULL)
        {
            listReset(list);
            data=listGetNext(list);
            while(data!=NULL)
            {
                if(strcasecmp(input,data->word)==0)
                {
                    printf("  %s\n",data->definition);
                    found=1;
                }
                data=listGetNext(list);
            }
        }
    }
    if(!found)
    {
        printf("  Not found in dictionary!\n");
    }
}
int main() 
{
    char input[32];
    LIST_HANDLE dictionary[26];
    memset(dictionary,'\0',sizeof(dictionary));
    buildDictionary(dictionary);
    printf("Do you want to see all words in dictionary (type Y or other) ? ");  /* type Y or other */
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%[^\n]", input);
    if(strcasecmp(input,"Y")==0)
    {
        printDictionary(dictionary);
        printf("\n");
    }
    while(1)
       {
        printf("Enter word (done to exit): ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%[^\n]",input);
        if(input[0]=='\n')
        {
            printf("  Please type again!\n");
            continue;
        }
        if(strcasecmp(input,"done")==0)
        {
            break;
        }
        printf("  %s >>",input);
        printDefinition(dictionary,input);
    }
    printf("\nGood bye!\n");
}
