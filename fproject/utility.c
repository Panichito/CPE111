/***********************************************************************************************************************
* utility.c
*
* utility function ex. check string is all char / digit
* or Ask question , receive answer and return input value
*
* Created by Pada Cherdchoothai (Da) ID 63070503439
*
***********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#include "utility.h"

/* check if string is all digit
 *
 * Argument :
 * char stringToCheck[] : user input
 *
 * Return :
 * Boolean value : true if string is all digit
 */
BOOL allDigit(char stringToCheck[])
    {
    for (int i = 0; i < strlen(stringToCheck); ++i)
        {
        if (!isdigit(stringToCheck[i]))
            {
            return FALSE;
            }
        }
    return TRUE;
    }

/* check if string is all alphabet
*
* Argument :
* char stringToCheck[] : user input
*
* Return :
* Boolean value : true if string is all alphabet
*/
BOOL allAlpha(char stringToCheck[])
    {
    for (int i = 0; i < strlen(stringToCheck); ++i)
        {
        if (!isalpha(stringToCheck[i]))
            {
            return FALSE;
            }
        }
    return TRUE;
    }

/* Print prompt message and get user input for 2 possible value true/false
*
* Argument :
* char message[] : print message
* char true[] : string if want output to be true
* char false[] : string if want output to be false
*
* Return :
* Boolean value : true if string is all alphabet
*/
BOOL boolPrompt(char message[], char true[], char false[])
    {
    char buffer[MAXCHAR]; /* user input buffer */
    char input[MAXCHAR]; /* user input */
    while (1)
        {
        printf("%s ([ %s / %s ]) : ", message, true, false);
        fgets(buffer, MAXCHAR, stdin);
        sscanf(buffer, "%s", input);
        printf("\n");
        if (strcasecmp(input, true) == 0) /* compare user input */
            { return TRUE; }
        else if (strcasecmp(input, false) == 0)
            { return FALSE; }
        }
    }

/* Print prompt message and ask for input return as int value
 *
 * Argument :
 * char message[] : print message
 *
 * Return :
 * the received int value
 */
int messageIONum(char message[])
    {
    char inputBuffer[MAXCHAR]; /* user input buffer */
    int out = -1;
    if (message != NULL) /*if message not empty print the message*/
        { printf("%s : ", message); }
    fgets(inputBuffer, MAXCHAR, stdin);
    sscanf(inputBuffer, "%d", &out);
    return out;
    }

/* Print prompt message and ask for input return as char string
*
* Argument :
* char message[] : print message
*
* Return :
* the received string
*/
char *messageIOString(char message[])
    {
    char input[MAXCHAR]; /* user input buffer */
    memset(input, 0, sizeof(input));
    if (message != NULL)/*if message not empty print the message*/
        { printf("%s : ", message); }
    fgets(input, sizeof(input), stdin);
    if (input[strlen(input)] == '\n')
        {
        input[strlen(input)] = '\0';
        }

    return strdup(input);
    }