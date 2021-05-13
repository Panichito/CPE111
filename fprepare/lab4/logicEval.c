/* 
 * logicEval.c
 * Created by Panithi Suwanno (Big) 63070503426
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "integerStack.h"
#define TRUE 1
#define FALSE 0
#define AND 38
#define OR 124

int checkChr(char* input) 
{
	for(int i = 0; i < strlen(input); ++i)
	{
		if((!isalpha(input[i]) || !isupper(input[i])) && input[i] != '(' && input[i] != ')' && input[i] != '&' && input[i] != '|')
		{
			printf("\tIllegal character\n");
			return 1;
		}
		if((input[i] == '|' && input[i+1] == '|') && (input[i] == '&' && input[i+1] == '&')) 
		{
			printf("\tRepeated syntax\n");
		}
	}
	return 0;
}

int truthvalue(char character)
{
	return (character-65 )%2;
}

int compute(char* input)
{
	int retVal = -1;
	int result;
	int v1, v2, op;
	stackClearInt();
	for(int i = 0; i < strlen(input); ++i)
	{
		if(input[i] == '(')
			continue;
		else if(input[i] == ')')
		{
			v2 = popInt();
			op = popInt();
			v1 = popInt();
			if(v1 == UNDERFLOW || v2 == UNDERFLOW || op == UNDERFLOW)
			{
				printf("\tInvalid expression syntax\n");
				return -1;
			}
			if(op == -1)
			{
				result = v1 && v2;
			}
			else if(op == 1) 
			{
				result = v1 || v2;
			}
			else 
			{
				printf("\tInvalid expression syntax\n");
				return -1;
			}
			pushInt(result);
		}
		else 
		{
			pushInt(truthvalue(input[i]));
		}
	}
	result = popInt();
	if(result == UNDERFLOW || stackSizeInt() != 0)
	{
		printf("\tInvalid expression syntax\n");
		return -1;
	}
	return result;
}

int main()
{
	char input[256];
	printf("Welcome to LogicEval!\n\nA,C,E, etc are false; B,D,F, etc are true\nUser '&' for AND and '|' for OR, '(' and ')' for nesting\n\n");
	while(1)
	{
		int count = 0 ;
		int result = 0;
		memset(input, 0, sizeof(input));
		printf("Enter logical expression to evaluate: ");
		fgets(input, sizeof(input), stdin);
		sscanf(input, "%[^\n]", input);
		if(strcasecmp(input, "DONE") == 0) 
			break;
		if(input[0] == '\n') 
		{
			printf("\tPlease input something\n");
			continue;
		}
		/* remove space */
		for(int i = 0; input[i]; ++i)
		{
			if(input[i] != ' ')
				input[count++] = input[i];
		}
		input[count] = '\0';
		if(checkChr(input)) 
		{
			continue;
		}
		if(strlen(input) == 1)
		{
			printf("\t%s truth value is ", input);
			if(truthvalue(input[0]) == 1)
				printf("TRUE\n");
			else
				printf("FALSE\n");
		}
		else 
		{
			result = compute(input);
			if(result == -1)
				continue;
			printf("\t%s truth value is ", input);
			if(result == 1)
				printf("TRUE\n");
			else if(result == 0)
				printf("FALSE\n");
		}
	}
	printf("Bye!\n");
}
