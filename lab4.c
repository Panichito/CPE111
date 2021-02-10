/*  logicEval.c
 *  This lab is intended to give me the opportunity to use a stack data structure.
 * 
 *  Created by Panithi Suwanno(Big) 63070503426 
 *  FOR Lab4 9 FEB 2021 
 *  UPDATE 10 FEB 2021 >> fixed bucks and create code from scratch which is better than blindly copy Aj.Sally's code 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "integerStack.h"
char input[128];
void removeSpace() {
	int count = 0;
	for(int i = 0; input[i]; ++i) {
		if(input[i] != ' ') {
			input[count++] = input[i];
		}
	}
	input[count] = '\0';
}
// Infact if parentheses not in the correct format prorgam will show Stack Underflow!
// But I also try to idenity which type of error and where it come from (for better user experience!) :)
int validateInput(char input[]) {
	// check operator duplicated?
	for(int i = 0; i < strlen(input); ++i) {
		if(input[i] == '|' && input[i+1] == '|') {
			printf("\tInvalid expression syntax: || repeated\n");
			return 0;
		}
		else if(input[i] == '&' && input[i+1] == '&') {
			printf("\tInvalid expression syntax: && repeated\n");
			return 0;
		}
	}
	// check parentheses pairs
	int open = 0, end = 0;
	for(int i = 0; i < strlen(input); ++i) {
		if(input[i] == '(') {
			open++;
		}
		else if(input[i] == ')') {
			end++;
		}
	}
	if(open != end || open == 0 || end == 0) {
		printf("\tInvalid expression syntax: parentheses not match\n");
		return 0;
	}
	return 1;
}
int main(int argc, char *argv[]) {  // argc and argv make my code looks more handsome (I won't delete it)
    int bok = 1, result = 0;
    while(1) {
		memset(input,'\0',sizeof(input));
        printf("Enter logical expression to evaluate: ");
        fgets(input,sizeof(input),stdin);
		sscanf(input,"%[^\n]",input);
		if(strlen(input) < 3 || input[0] == ' ') {  // Ex. (A) is the shortest case
			printf("\tInvalid expression syntax\n");
			continue;
		}
		else if(strcasecmp(input,"DONE") == 0) {
			break;
		}
		removeSpace();
		//printf("input= %s\nstrlen= %ld\n",input,strlen(input));
		int bOk = 1;
		// Initially check all valid character
		for(int i = 0; i < strlen(input); ++i) {
			if(input[i] != '(' && input[i] != ')' && input[i] != '&' && input[i] != '|') {
				if(!isalpha(input[i]) || !isupper(input[i])) {
					bOk = 0;
					printf("\tInvalid character in expression: %c\n",input[i]);
					break;
				}
			}
		}
		if(bOk) {
			bOk = validateInput(input);
			if(bOk) {
				stackClearInt();
				int truthvalue = 0, result = 0;
				for(int i = 0; i < strlen(input); ++i) {
					if(input[i] == '(') {
						continue;
					}
					else if(input[i] == ')') {
						int v1 = popInt();
						int op = popInt();
						int v2 = popInt();
						//printf("%d %d %d\n",v1,op,v2);
						if(v1 == UNDERFLOW || op != UNDERFLOW && v2 == UNDERFLOW) {
							bOk = 0;
							printf("\tInvalid expression: stack underflow\n");  // may be your parentheses not correct :(
							break;
						}
						else if(op == 1) {
							result = (v1 || v2);
						}
						else if(op == -1) {
							result = (v1 && v2);
						}
						pushInt(result);
						printf("result= %d\n",result);
					}
					else {
						truthvalue = ((int)input[i]-65)%2;
						pushInt(truthvalue);
						//printf("tv= %d\n",truthvalue);
					}
				}
			}
			// print the result 
			if(bOk) {
				int empty = stackSizeInt();  // need to have only one element left before pop()
				//printf("empty= %d\n",empty);
				if(empty != 1) {
					printf("\tInvalid expression syntax\n");
					continue;
				}
				printf("\t%s truth value is ",input);
				result = popInt();
				if(result) {
					printf("TRUE\n");
				}
				else {
					printf("FALSE\n");
				}
			}
		}
	}
    printf("Bye!\n");
    return 0;
}
