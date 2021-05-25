/* commandFunction.c
 *
 * This file contains commands that the program can do. And also 
 * includes the command for manipulated within the linked list data structure.
 *
 * Created by Rickrollaphobia group 
 */
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "commandFunctions.h"

/** Public **/
int shapeCount[] = {0, 0, 0, 0, 0, 0, 0, 0};

/* resetShapeCount function 
 * 
 * When the user calls this function, the program will set 
 * every value of the shapeCount[] array equal to zero.
 *
 * Returns NULL.
 */
void resetShapeCount()
    {
    for (int i = 0; i < sizeof(shapeCount) / sizeof(shapeCount[0]); i++)
        {
        shapeCount[i] = 0;
        }
    }

/* getCommandModeName function
 * Argument
 * 	   mode - integer obtained from the getCommandMode function
 *
 * Return string (abbreviations of shapes)
 */
char *getCommandModeName(MODE mode)
    {
    char nameBuffer[64];
    char indexBuffer[16];
    int shapeIndex;
    memset(nameBuffer, 0, sizeof(nameBuffer));
    switch (mode)
        {
        case LINE:
        case LINEDASH:
            strcat(nameBuffer, "L");
            shapeIndex = 0;
            break;
        case RECTANGLE:
        case RECTANGLEFILL:
            strcat(nameBuffer, "R");
            shapeIndex = 1;
            break;
        case CIRCLE:
        case CIRCLEFILL:
            strcat(nameBuffer, "C");
            shapeIndex = 2;
            break;
        case TRIANGLE:
        case TRIANGLEFILL:
            strcat(nameBuffer, "T");
            shapeIndex = 3;
            break;
        case DIAMOND:
        case DIAMONDFILL:
            strcat(nameBuffer, "D");
            shapeIndex = 4;
            break;
        case ELLIPSE:
        case ELLIPSEFILL:
            strcat(nameBuffer, "E");
            shapeIndex = 5;
            break;
        case ARC:
        case ARCFILL:
            strcat(nameBuffer, "A");
            shapeIndex = 6;
            break;
        case POLY:
        case POLYOPEN:
        case POLYFILL:
            strcat(nameBuffer, "P");
            shapeIndex = 7;
            break;
        }
    sprintf(indexBuffer, "%d", shapeCount[shapeIndex]);
    strcat(nameBuffer, indexBuffer);
    shapeCount[shapeIndex]++;
    return strdup(nameBuffer);
    }

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
MODE getCommandMode(char *input)
    {
    MODE mode = ERR;
    if (strcasecmp(input, "CreateImg") == 0)
        mode = CREATEIMG;
    else if (strcasecmp(input, "Background") == 0)
        mode = BACKGROUND;
    else if (strcasecmp(input, "Brush") == 0)
        mode = BRUSH;
    else if (strcasecmp(input, "Line") == 0)
        mode = LINE;
    else if (strcasecmp(input, "LineDash") == 0)
        mode = LINEDASH;
    else if (strcasecmp(input, "Rectangle") == 0)
        mode = RECTANGLE;
    else if (strcasecmp(input, "RectangleFill") == 0)
        mode = RECTANGLEFILL;
    else if (strcasecmp(input, "Circle") == 0)
        mode = CIRCLE;
    else if (strcasecmp(input, "CircleFill") == 0)
        mode = CIRCLEFILL;
    else if (strcasecmp(input, "Triangle") == 0)
        mode = TRIANGLE;
    else if (strcasecmp(input, "TriangleFill") == 0)
        mode = TRIANGLEFILL;
    else if (strcasecmp(input, "Diamond") == 0)
        mode = DIAMOND;
    else if (strcasecmp(input, "DiamondFill") == 0)
        mode = DIAMONDFILL;
    else if (strcasecmp(input, "Arc") == 0)
        mode = ARC;
    else if (strcasecmp(input, "ArcFill") == 0)
        mode = ARCFILL;
    else if (strcasecmp(input, "Ellipse") == 0)
        mode = ELLIPSE;
    else if (strcasecmp(input, "EllipseFill") == 0)
        mode = ELLIPSEFILL;
    else if (strcasecmp(input, "Polygon") == 0)
        mode = POLY;
    else if (strcasecmp(input, "PolygonOpen") == 0)
        mode = POLYOPEN;
    else if (strcasecmp(input, "PolygonFill") == 0)
        mode = POLYFILL;
    else if (strcasecmp(input, "Draw") == 0)
        mode = DRAW;
    else if (strcasecmp(input, "List") == 0)
        mode = LIST;
    else if (strcasecmp(input, "Edit") == 0)
        mode = EDIT;
    else if (strcasecmp(input, "Move") == 0)
        mode = MOVE;
    else if (strcasecmp(input, "Swap") == 0)
        mode = SWAP;
    else if (strcasecmp(input, "Remove") == 0)
        mode = REMOVE;
    else if (strcasecmp(input, "Reset") == 0)
        mode = RESET;
    else if (strcasecmp(input, "Save") == 0)
        mode = SAVE;
    else if (strcasecmp(input, "Load") == 0)
        mode = LOAD;
    else if (strcasecmp(input, "Color") == 0)
        mode = COLOR;
    else if (strcasecmp(input, "Help") == 0)
        mode = HELP;
    else if (strcasecmp(input, "Exit") == 0)
        mode = EXIT;
    free(input);
    return mode;
    }

/* printCommandContent function
 *
 * Arguments
 * 		index - The order of the data to be displayed
 * 		command - A struct that stores information for 
 * 				  each instruction in the linked list.
 *
 * Return NULL.
 */
void printCommandContent(int index, COMMAND_T *command)
    {
    printf("\t%2d) name : %-3s mode : %d color : %s\n\t\t", index, command->name, command->mode, command->color->name);
    for (int i = 0; i < command->pointCount; i++)
        {
        printf("point%2d : X:%3d Y:%3d", i + 1, command->points[i].x, command->points[i].y);
        if (i + 1 < command->pointCount)
            printf(" , ");
        }
    if (command->etc != -1)
        {
        printf(",%3d", command->etc);
        }
    printf("\n");
    }

/* printAllCommand function
 * This function will display all commands in the linked list in chronological order.
 *
 * Arguments
 * 		setup - Array of command , need to be run first in order to draw image.
 * 		commands - Linked list of commands , instruction to draw the image.
 *
 * Return NULL.
 */
void printAllCommand(COMMAND_T *setup[], LIST_HANDLE commands)
    {
    int index = 1;
    COMMAND_T *data = NULL;
    listReset(commands);
    data = listGetNext(commands);
    if (setup[0] != NULL)
        {
        printf("\tImage size :\n\t\tX:%3d Y:%3d\n", setup[0]->points[0].x, setup[0]->points[0].y);
        }
    else
        {
        printf("\tImage hasn't been create yet\n");
        }

    if (setup[1] != NULL)
        {
        printf("\tBackground color : %s\n", setup[1]->color->name);
        }
    else
        {
        printf("\tBackground color hasn't been selected yet\n");
        }

    printf("\tBrush size : ");
    if (setup[2] != NULL)
        {
        printf("%3dpx\n", setup[2]->etc);
        }
    else
        {
        printf("%3dpx\n", 1);
        }

    if (listSize(commands) == 0)
        {
        printf("\tLists is empty\n");
        }
    else
        printf("\tLists Size is %d\n", listSize(commands));
    while (data != NULL)
        {
        printCommandContent(index, data);
        data = listGetNext(commands);
        ++index;
        }
    }

/* getEditCommand function
 * Find the command in the linked list that user want to edit.
 * Arguements
 * 		commands - Linked list of commands , instruction to draw the image.
 * 		position - The position of the information can be obtained from the queue.
 *
 * Return struct of the command that going to edit
 * Return NULL not found that command in linked list
 */
COMMAND_T *getEditCommand(LIST_HANDLE commands, char *position)
    {
    COMMAND_T *data = NULL;
    int listCount = listSize(commands);
    listReset(commands);
    if (listCount == 0)
        {
        printf("\tInvalid - list is empty\n");
        }
    else if (allDigit(position))
        {
        int index = atoi(position);
        if (index <= listCount)
            {
            for (int i = 0; i < index; ++i)
                {
                data = listGetNext(commands);
                }
            printCommandContent(index, data);
            }
        else
            { printf("\tInvalid input number out of range\n"); }
        }
    free(position);
    return data;
    }

/* moveCommand function
* Arguments
* 		commands - Linked list of commands , instruction to draw the image.
* 		position1 - The position of the first data can be obtained from the queue.
* 		position1 - The position of the second data can be obtained from the queue.
*
* Return NULL. (no return)
*/
BOOL moveCommand(LIST_HANDLE commands, char *position1, char *position2)
    {
    int listCount = listSize(commands);
    if (listCount <= 1)
        {
        printf("\tInvalid list too small (has %d commands) , cannot be move\n", listCount);
        }
    else if (allDigit(position1) && allDigit(position2))
        {
        int num1 = atoi(position1);
        int num2 = atoi(position2);

        if (num1 < 0 || num2 > listCount)
            {
            printf("\tInvalid input number out of range\n");
            }
        else if (num1 == num2)
            {
            printf("\tInvalid input the same number postion\n");
            }
        else
            {
            listItemMove(commands, num1 - 1, num2 - 1);
            printf("\tMove commands from #%2d to #%2d\n", num1, num2);
            }
        }
    else
        { printf("\tArguments must be number\n"); }
    free(position1);
    free(position2);
    }

/* swapCommandOrder function
 * Arguments 
 * 		commands - Linked list of commands , instruction to draw the image.
 * 		position1 - The position of the first data can be obtained from the queue.
 * 		position1 - The position of the second data can be obtained from the queue.
 * 
 * Return NULL. (no return)
 */
BOOL swapCommandOrder(LIST_HANDLE commands, char *position1, char *position2)
    {
    int listCount = listSize(commands);
    if (listCount <= 1)
        {
        printf("\tInvalid list too small (has %d commands) , cannot be swap\n", listCount);
        }
    else if (allDigit(position1) && allDigit(position2))
        {
        int num1 = atoi(position1);
        int num2 = atoi(position2);

        if (num1 < 0 || num2 > listCount)
            {
            printf("\tInvalid input number out of range\n");
            }
        else
            {
            listItemSwap(commands, num1 - 1, num2 - 1);
            printf("\tSwapped commands #%2d and #%2d\n", num1, num2);
            }
        }
    else
        { printf("\tArguments must be number\n"); }
    free(position1);
    free(position2);
    }

/* freeCommand function
 * remove unwanted commands from linked list
 *
 * Arguments 
 * 		commands - Linked list of commands , instruction to draw the image.
 * 		position - The position of the information can be obtained from the queue.
 *
 * Return NUll. (no return)
 */
BOOL freeCommand(LIST_HANDLE commands, char *position)
    {
    if (listSize(commands) == 0)
        {
        printf("\tInvalid - list is empty\n");
        }
    else if (allDigit(position))
        {
        int num = atoi(position);
        printf("\tTrying to removed position %d\n", num);
        if (num > 0 && num <= listSize(commands))
            {
            freeCommandItem((COMMAND_T *) listRemove(commands, num - 1));
            printf("\tSuccessfully removed position %d\n", num);
            }
        else
            {
            printf("\tInvalid input number out of range\n");
            }
        }
    else
        { printf("\tArgument must be number\n"); }
    free(position);
    }

/* freeCommandItem function
 * This function is to free an unused struct.
 *
 * Argument
 * 	   command - struct of COMMAND_T 
 *
 * Return NULL.
 */
void freeCommandItem(COMMAND_T *command)
    {
    if (command->name != NULL)
        {
        free(command->name);
        }
    if (command->points != NULL)
        {
        free(command->points);
        }
    free(command);
    }

/* resetAllCommand function
 * This function will reset all values in a linked list to NULL and free them.
 *
 * Arguments
 * 		setup - Array of command , need to be run first in order to draw image.
 * 		commands - Linked list of commands , instruction to draw the image.
 *
 * Return NULL.
 */
void resetAllCommand(COMMAND_T *setup[], LIST_HANDLE commands)
    {
    listReset(commands);
    for (int i = 0; i < 3; ++i)
        {
        if (setup[i] != NULL)
            {
            freeCommandItem(setup[i]);
            setup[i] = NULL;
            }
        }
    for (int j = listSize(commands); j > 0; j--)
        {
        freeCommandItem((COMMAND_T *) listRemove(commands, j - 1));
        }
    resetShapeCount();
    }

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
void saveCommands(char *filename, COMMAND_T **setup, LIST_HANDLE commands)
    {
    FILE *fileout = NULL;
    COMMAND_T *data = NULL;
    if (strncasecmp(filename + (strlen(filename) - 4), ".sav", 4) != 0)
        {
        char outputName[64];
        strcpy(outputName, filename);
        strcat(outputName, ".sav");
        free(filename);
        filename = strdup(outputName);
        }
    fileout = fopen(filename, "w");
    listReset(commands);
    for (int i = 0; i < 3; ++i)
        {
        if (setup[i] != NULL)
            {
            fprintf(fileout, "%d", setup[i]->mode);
            for (int j = 0; j < setup[i]->pointCount; ++j)
                {
                fprintf(fileout, " %d %d", setup[i]->points[j].x, setup[i]->points[j].y);
                }
            if (setup[i]->mode == BRUSH)
                {
                fprintf(fileout, " %d", setup[i]->etc);
                }
            if (setup[i]->mode == BACKGROUND)
                {
                fprintf(fileout, " %s", setup[i]->color->name);
                }
            fprintf(fileout, "\n");
            }
        }
    data = listGetNext(commands);
    while (data != NULL)
        {
        fprintf(fileout, "%d", data->mode);
        for (int i = 0; i < data->pointCount; ++i)
            {
            fprintf(fileout, " %d %d", data->points[i].x, data->points[i].y);
            }
        if (data->mode == CIRCLE || data->mode == CIRCLEFILL)
            {
            fprintf(fileout, " %d", data->etc);
            }

        fprintf(fileout, " %s", data->color->name);
        fprintf(fileout, "\n");

        data = listGetNext(commands);
        }
    fclose(fileout);
    }
