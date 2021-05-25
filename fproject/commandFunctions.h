/* commandFunction.h
 * 
 * Header file for commandFunction.c
 *
 * This file contains commands that the program can do. And also 
 * includes the command for manipulated within the linked list data structure.
 *
 * Created by Rickrollaphobia group
 */
#ifndef COMMAND_H
#define COMMAND_H

#include "colorFunctions.h"
#include "linkedListUtilMod.h"
#include "utility.h"

/* command mode represents various status that received from users */
typedef int MODE;
#define EXIT -99
#define ERR -1
#define CREATEIMG 0
#define BACKGROUND 1
#define BRUSH 2
#define CIRCLE 3
#define CIRCLEFILL 4
#define LINE 5
#define LINEDASH 6
#define RECTANGLE 7
#define RECTANGLEFILL 8
#define TRIANGLE 9
#define TRIANGLEFILL 10
#define DIAMOND 11
#define DIAMONDFILL 12
#define ELLIPSE 13
#define ELLIPSEFILL 14
#define ARC 15
#define ARCFILL 16
#define POLY 17
#define POLYOPEN 18
#define POLYFILL 19
#define DRAW 20
#define LIST 21
#define EDIT 22
#define MOVE 23
#define SWAP 24
#define REMOVE 25
#define RESET 26
#define SAVE 27
#define LOAD 28
#define COLOR 29
#define HELP 30


/* Structure that represents the point in the x-axis and y-axis format */
typedef struct point
    {
    int x;   /* x-axis */
    int y;	 /* y-axis */
    }POINT_T;

/* Structure that represent the one of the command in list */
typedef struct command
    {
    MODE mode;  		  /* predefine mode (typedef int) of commands */
    char *name; 		  /* assigned name of commands */
    POINT_T *points;      /* points value  */
    int pointCount; 	  /* count of points */
    int etc; 			  /* extra value */
    COLOR_T *color;  /* color used in drawing */
    } COMMAND_T;


/* getCommandMode function
 *
 * This function checks the user input to see if it 
 * matches the specified command set or not. After that, 
 * the command will be converted into a code called mode which 
 * will be used in the future.
 *
 * Argument 
 *   input - string input that received from users
 * 
 * Return number between 0 - 29 if input is correct
 * Return -99 exit the program
 * Return -1 command not found
 */
MODE getCommandMode(char *input);


/* resetShapeCount function 
 * 
 * When the user calls this function, the program will set 
 * every value of the shapeCount[] array equal to zero.
 *
 * Returns NULL.
 */
void resetShapeCount();


/* getCommandModeName function
 * Argument
 * 	   mode - integer obtained from the getCommandMode function
 *
 * Return string (abbreviations of shapes)
 */
char *getCommandModeName(MODE mode);


/* printCommandContent function
 *
 * Arguments
 * 		index - The order of the data to be displayed
 * 		command - A struct that stores information for 
 * 				  each instruction in the linked list.
 *
 * Return NULL.
 */
void printCommandContent(int index, COMMAND_T *command);


/* printAllCommand function
 * This function will display all commands in the linked list in chronological order.
 *
 * Arguments
 * 		setup - Array of command , need to be run first in order to draw image.
 * 		commands - Linked list of commands , instruction to draw the image.
 * Return NULL.
 */
void printAllCommand(COMMAND_T *setup[], LIST_HANDLE commands);


/* getEditCommand function
 * Find the command in the linked list that user want to edit.
 * Arguements
 * 		commands - Linked list of commands , instruction to draw the image.
 * 		position - The position of the information can be obtained from the queue.
 *
 * Return struct of the command that going to edit
 * Return NULL not found that command in linked list
 */
COMMAND_T *getEditCommand(LIST_HANDLE commands, char *position);

/* moveCommand function
* Arguments
* 		commands - Linked list of commands , instruction to draw the image.
* 		position1 - The position of the first data can be obtained from the queue.
* 		position1 - The position of the second data can be obtained from the queue.
*
* Return NULL. (no return)
*/
BOOL moveCommand(LIST_HANDLE commands, char *position1, char *position2);

/* swapCommandOrder function
 * Arguments 
 * 		commands - Linked list of commands , instruction to draw the image.
 * 		position1 - The position of the first data can be obtained from the queue.
 * 		position1 - The position of the second data can be obtained from the queue.
 * 
 * Return NULL. (no return)
 */
BOOL swapCommandOrder(LIST_HANDLE commands, char *position1, char *position2);


/* freeCommand function
 * remove unwanted commands from linked list
 *
 * Arguments 
 * 		commands - Linked list of commands , instruction to draw the image.
 * 		position - The position of the information can be obtained from the queue.
 *
 * Return NUll. (no return)
 */
BOOL freeCommand(LIST_HANDLE commands, char *position);


/* freeCommandItem function
 * This function is to free an unused struct.
 *
 * Argument
 * 	   command - struct of COMMAND_T 
 *
 * Return NULL.
 */
void freeCommandItem(COMMAND_T *command);


/* resetAllCommand function
 * This function will reset all values in a linked list to NULL and free them.
 *
 * Arguments
 * 		setup - Array of command , need to be run first in order to draw image.
 * 		commands - Linked list of commands , instruction to draw the image.
 *
 * Return NULL.
 */
void resetAllCommand(COMMAND_T *setup[], LIST_HANDLE commands);


/* saveCommands function
 * This function will save the information of the linked list commands by opening 
 * the output file and writing the commands data to archive it.
 *
 * Arguments 
 * 		filename - Name of the file user want to write the command to.
 * 		setup - Array of command , need to be run first in order to draw image.
 * 		commands - Linked list of commands , instruction to draw the image.
 * Return NULL.
 */
void saveCommands(char *filename, COMMAND_T **setup, LIST_HANDLE commands);

#endif
