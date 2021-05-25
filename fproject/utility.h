/***********************************************************************************************************************
* utility.h
*
* This header define type BOOL and TRUE / FALSE
* and declare function in utility.c , these function are utility tools
*
* Created by Pada Cherdchoothai (Da) ID 63070503439
*
***********************************************************************************************************************/
#ifndef UTILITY_H
#define UTILITY_H

typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define MAXCHAR 256

/* check if string is all digit
 *
 * Argument :
 * char stringToCheck[] : user input
 *
 * Return :
 * Boolean value : true if string is all digit
 */
BOOL allDigit(char stringToCheck[]);

/* check if string is all alphabet
*
* Argument :
* char stringToCheck[] : user input
*
* Return :
* Boolean value : true if string is all alphabet
*/
BOOL allAlpha(char stringToCheck[]);

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
BOOL boolPrompt(char message[], char true[], char false[]);

/* Print prompt message and ask for input return as char string
*
* Argument :
* char message[] : print message
*
* Return :
* the received string
*/
char* messageIOString(char message[]);

/* Print prompt message and ask for input return as int value
 *
 * Argument :
 * char message[] : print message
 *
 * Return :
 * the received int value
 */
int messageIONum(char message[]);

#endif