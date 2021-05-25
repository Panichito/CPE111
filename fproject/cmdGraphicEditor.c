/* cmdGraphicEditor
 *  This is the main program of our project
 *  The program will ask user for a command in command line
 *  then after user enter a valid command it will process it
 *  then call other function based on the command
 *  if it shape related command it will create a struct to save it
 *  and add it into the list
 *
 *   Created by Rickrollaphobia group
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commandFunctions.h"
#include "linkedListUtilMod.h"
#include "abstractQueueMod.h"
#include "drawImage.h"
#include "helpMenu.h"
#include "utility.h"

COMMAND_T *setup[3]; /*array of command , need to be run first in order to draw image*/
LIST_HANDLE *commands = NULL;/*linked list of commands , instruction to draw the image*/
const int shapeCommandRequireArgs[] = {2, 1, 1, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7};

/*number of argument required to draw each shape*/

/* do the command action from the mode that user input */
void instantCommand(int mode);

/* do the color command action from the mode that user input */
void colorCommands();

/*Create the command list
 *
 * Return :
 *      boolean value , true if commands list was created*/
BOOL createCommandList();

/* From input split by space and enqueue each string
* Argument
*      input - input string
*/
void queueCommand(char *input);

/* sub-function , pass newCommand and mode to correct function
 * if command was created it will change flag value
 * if command isn't create it will free the command
 * Arguments :
 *      newCommand - pointer to newCommand struct
 *      mode - mode of operation
 * Return :
 *      flag value , -1 if fail , 0 if command belong to setup array , 1 if command need to be add to list
 */
int createCommand(COMMAND_T *newCommand, MODE mode);

/* validate each argument for creating new image
 * Arguments :
 *      command - pointer to a command struct
 * Return :
 *      boolean value , true if command was created
 */
BOOL createImageCommand(COMMAND_T *command);

/* validate each argument for creating background
* Arguments :
*      command - pointer to a command struct
* Return :
*      boolean value , true if command was created
*/
BOOL createBackgroundCommand(COMMAND_T *command);

/* validate each argument for brush size
* Argument :
*      command - pointer to a command struct
* Return :
*      boolean value , true if command was created
*/
BOOL createBrushCommand(COMMAND_T *command);

/* validate each argument for shape command
* Arguments :
*     command - pointer to a command struct
*     commandName - name for the command
*     pointCount - point number for the shape
* Return :
*      boolean value , true if command was created
*/
BOOL createShapeCommand(COMMAND_T *command, char *commandName, int pointCount);

/* open file with the name of *filename , read it and add the command to the list*/
void loadCommands(char *filename);


/** Private **/

/* main
 *  Accept userinput
 */
int main()
    {

    if (!createCommandList())
        {
        printf("Cannot Allocate memory to start program... Exiting\n");
        exit(0);
        }

    readColor();

    while (TRUE)
        {
        queueCommand(messageIOString("Enter command")); /*user enter command and system process the input into queue*/

        MODE mode = ERR;
        if (queueSize() != 0)
            mode = getCommandMode(dequeue()); /*Check first argument of string for command mode*/
        else
            printf("Invalid command\n");

        //printf("current mode is %d\n", mode);

        if (mode == EXIT)
            { break; }

        if (mode != ERR)
            {
            /*Check if command a instruction (less than draw , get put in list) or an order (execute immediately)*/
            if (mode < DRAW)
                {
                COMMAND_T *newCommand = (COMMAND_T *) calloc(1, sizeof(COMMAND_T)); /*Create new command struct*/

                int flag = createCommand(newCommand, mode);
                if (flag != -1)
                    {
                    printf("\t Insert new commands : %s\n", newCommand->name);
                    if (flag == 1)
                        {
                        listInsertEnd(commands, newCommand);
                        }
                    }
                }
            else
                {
                /*Call command based on mode , will check number of argument using queueSize*/
                instantCommand(mode);
                }

            }
        else
            {
            printf("\tCommand not define\n");
            }

        }


    /*Free everything*/

    freeColor();
    resetAllCommand(setup, commands);
    listDestroy(commands);

    return 0;
    }

void instantCommand(int mode)
    {
    switch (mode)
        {
        case DRAW:
            /* draw the picture in canvas from command list */
            if (queueSize() == 1)
                {
                drawImg(dequeue(), setup, commands);
                }
            else
                {
                printf("\tWrong format\n");
                }
            break;
        case LIST:
            /* print all the command lists */
            printAllCommand(setup, commands);
            break;
        case EDIT:
            /* edit the command in the list */
            if (queueSize() >= 1)
                {
                char *pos = dequeue();
                COMMAND_T *oldData = getEditCommand(commands, pos);
                if (oldData != NULL)
                    {
                    int reqArg;
                    /* check require arguments for command */
                    if (oldData->mode < POLY)
                        {
                        reqArg = shapeCommandRequireArgs[oldData->mode];
                        }
                    else
                        {
                        reqArg = ((oldData->pointCount) * 2) + 1;
                        }

                    if (reqArg == queueSize())
                        {
                        /* allocated memory for new data */
                        COMMAND_T *newData = (COMMAND_T *) calloc(1, sizeof(COMMAND_T));
                        if (newData != NULL)
                            {
                            newData->mode = oldData->mode;
                            /* edit command */
                            if (createShapeCommand(newData, strdup(oldData->name), oldData->pointCount))
                                {
                                listSwapData(commands, oldData, newData);
                                freeCommandItem(oldData);
                                }
                            }
                        }
                    }
                }
            else
                {
                printf("\tWrong format\n");
                }
            break;
        case MOVE:
            /* move command to the selected position */
            if (queueSize() == 2)
                {
                char *pos1 = dequeue();
                char *pos2 = dequeue();
                moveCommand(commands, pos1, pos2);
                }
            else
                {
                printf("\tWrong format\n");
                }
            break;
        case SWAP:
            /* swap command order */
            if (queueSize() == 2)
                {
                char *pos1 = dequeue();
                char *pos2 = dequeue();
                swapCommandOrder(commands, pos1, pos2);
                }
            else
                {
                printf("\tWrong format\n");
                }
            break;
        case REMOVE:
            /* remove/free selected command */
            if (queueSize() == 1)
                {
                char *pos = dequeue();
                freeCommand(commands, pos);
                }
            break;
        case RESET:
            /* reset all */
            resetAllCommand(setup, commands);
            break;
        case SAVE:
            /* save command list into the file */
            if (queueSize() == 1)
                {
                saveCommands(dequeue(), setup, commands);
                }
            else
                {
                printf("\tWrong format\n");
                }
            break;
        case LOAD:
            /* load command list from the file */
            if (queueSize() == 1)
                {
                loadCommands(dequeue());
                }
            else
                {
                printf("\tWrong format\n");
                }
            break;
        case COLOR:
            /* do color command action */
            colorCommands();
            break;
        case HELP:
            /* print help */
            if (queueSize() == 0)
                {
                printallhelp();
                }
            else if (queueSize() >= 1)
                {
                /* print help with selected command */
                MODE helpMode = getCommandMode(dequeue());
                if (helpMode == COLOR && queueSize() == 1)
                    {
                    askforhelp_color(getColorCommand(dequeue()));
                    }
                else
                    {
                    askforhelp(helpMode);
                    }
                };
        }
    }


/* Do the color command action from the mode that user input */
void colorCommands()
    {
    if (queueSize() >= 1)
        {
        int option = getColorCommand(dequeue());
        switch (option)
            {
            case COLORLIST:
                /* print all color list */
                printAllColor();
                break;
            case COLORADD:
                /* add new color to the list */
                if (queueSize() == 5)
                    {
                    char *name = dequeue();
                    char *r = dequeue();
                    char *g = dequeue();
                    char *b = dequeue();
                    char *a = dequeue();
                    addColor(name, r, g, b, a);
                    }
                else
                    {
                    printf("\tWrong format\n");
                    }
                break;
            case COLOREDIT :
                /* edit color in the list */
                if (queueSize() == 5)
                    {
                    char *name = dequeue();
                    char *r = dequeue();
                    char *g = dequeue();
                    char *b = dequeue();
                    char *a = dequeue();
                    editColor(name, r, g, b, a);
                    }
                else
                    {
                    printf("\tWrong format\n");
                    }
                break;
            case COLORDEL :
                /* delete selected color from the list */
                if (queueSize() == 1)
                    {
                    deleteColor(dequeue());
                    }
                else
                    {
                    printf("\tWrong format\n");
                    }
                break;
            case COLORSAVE :
                /* save color into the file */
                if (queueSize() == 1)
                    {
                    saveUserColor(dequeue());
                    }
                else
                    {
                    printf("\tWrong format\n");
                    }
                break;
            case COLORLOAD :
                /* load color list from the file */
                if (queueSize() == 1)
                    {
                    loadUserColor(dequeue());
                    }
                else
                    {
                    printf("\tWrong format\n");
                    }
                break;
            default:
                printf("\tCommand not define\n");
            }
        }
    else
        {
        printf("\tCommand not define\n");
        }
    }

/*Create the command list
*
* Return :
*      boolean value , true if commands list was created*/
BOOL createCommandList()
    {
    BOOL flag = TRUE;/*assume success*/

    commands = newList();
    resetShapeCount();

    if (commands == NULL)
        {
        flag = FALSE;
        }

    return flag;
    }

/* From input split by space and enqueue each string
* Argument
*      input - input string
*/
void queueCommand(char *input)
    {
    char temp[MAXCHAR];/*temporary string that will the the split string*/
    queueClear(TRUE);

    /* i - counter for loop
     * start - start index for the new string
     */
    for (int i = 0, start = 0; i <= strlen(input); i++)
        {
        if (isspace(input[i]))
            {
            memset(temp, 0, sizeof(temp));//clear temp
            strncpy(temp, input + start, i - start);//copy the string between two spaces
            if (strlen(temp) > 0)
                enqueue(strdup(temp));
            start = i + 1;
            }
        }
    free(input); /*free the input*/
    }

/* sub-function , pass newCommand and mode to correct function
 * if command was created it will change flag value
 * if command isn't create it will free the command
 * Arguments :
 *      newCommand - pointer to newCommand struct
 *      mode - mode of operation
 * Return :
 *      flag value , -1 if fail , 0 if command belong to setup array , 1 if command need to be add to list
 */
int createCommand(COMMAND_T *newCommand, MODE mode)
    {
    int flag = -1; /* assume fail */
    if (newCommand != NULL) /* check command is allocated*/
        {
        newCommand->mode = mode;/*Put the mode in command*/
        if (mode < POLY)
            {
            /*Check for argument amount*/
            if (shapeCommandRequireArgs[mode] == queueSize())
                {
                switch (mode)
                    {
                    /* command for setup array */
                    case CREATEIMG:
                        if (createImageCommand(newCommand))
                            {
                            setup[0] = newCommand;
                            flag = 0;
                            }
                        break;
                    case BACKGROUND:
                        if (createBackgroundCommand(newCommand))
                            {
                            setup[1] = newCommand;
                            flag = 0;
                            }
                        break;
                    case BRUSH:
                        if (createBrushCommand(newCommand))
                            {
                            setup[2] = newCommand;
                            flag = 0;
                            }
                        break;
                    /* command for an object, not in setup array */
                    case CIRCLE:
                    case CIRCLEFILL:
                        if (createShapeCommand(newCommand, getCommandModeName(newCommand->mode), 1))
                            {
                            flag = 1;
                            }
                        break;
                    case LINE:
                    case LINEDASH:
                    case RECTANGLE:
                    case RECTANGLEFILL:
                    case TRIANGLE:
                    case TRIANGLEFILL:
                    case DIAMOND:
                    case DIAMONDFILL:
                    case ELLIPSE:
                    case ELLIPSEFILL:
                        if (createShapeCommand(newCommand, getCommandModeName(newCommand->mode), 2))
                            {
                            flag = 1;
                            }
                        break;
                    case ARC:
                    case ARCFILL:
                        if (createShapeCommand(newCommand, getCommandModeName(newCommand->mode), 3))
                            {
                            flag = 1;
                            }
                        break;
                    }
                }
            else
                {
                printf("\tWrong argument amount : input %d , need %d\n", queueSize(), shapeCommandRequireArgs[mode]);
                }
            }
        else if (mode >= POLY && mode <= POLYFILL)
            {
            /*Calculate number of possible points*/
            if (queueSize() % 2 == 1)
                {
                if (createShapeCommand(newCommand, getCommandModeName(newCommand->mode), ((queueSize() - 1) / 2)))
                    {
                    flag = 1;
                    }
                }
            else
                {
                printf("\tWrong argument amount : input %d , need odd argument\n", queueSize());
                }
            }
        }
    else
        {
        printf("\tCan't allocate data for new command\n");
        }
    if (flag == -1)
        {
        freeCommandItem(newCommand);
        }
    return flag;
    }

/* validate each argument for creating new image
 * Arguments :
 *      command - pointer to a command struct
 * Return :
 *      boolean value , true if command was created
 */
BOOL createImageCommand(COMMAND_T *command)
    {
    BOOL validCommand = TRUE; /*Assume true*/
    command->points = (POINT_T *) calloc(sizeof(POINT_T), 1); /*Create array for points*/
    command->name = strdup("Create Image"); /*Create command name*/
    /*Check if all allocate is success*/
    if ((command->name != NULL) && (command->points != NULL))
        {
        char *dequeueStringX = NULL;
        char *dequeueStringY = NULL;

        dequeueStringX = dequeue();
        dequeueStringY = dequeue();

        /*Check if all digit*/
        if (allDigit(dequeueStringX) && allDigit(dequeueStringY))
            {
            command->points[0].x = atoi(dequeueStringX);
            command->points[0].y = atoi(dequeueStringY);
            free(dequeueStringX);
            free(dequeueStringY);
            }
        else
            {
            printf("\tValue contain non-digit\n");
            validCommand = FALSE;
            }
        command->pointCount = 1;
        }
    else
        {
        validCommand = FALSE;
        }
    return validCommand;
    }

/* validate each argument for creating background
* Arguments :
*      command - pointer to a command struct
* Return :
*      boolean value , true if command was created
*/
BOOL createBackgroundCommand(COMMAND_T *command)
    {
    BOOL validCommand = FALSE;
    COLOR_T *color = findColor(dequeue(), 1);
    if (color != NULL)
        {
        command->name = strdup("Background");
        command->color = color;
        validCommand = TRUE;
        }
    else
        {
        printf("\tColor isn't in the program\n");
        }
    return validCommand;
    }

/* validate each argument for brush size
* Argument :
*      command - pointer to a command struct
* Return :
*      boolean value , true if command was created
*/
BOOL createBrushCommand(COMMAND_T *command)
    {
    BOOL validCommand = TRUE;
    command->name = strdup("Brush size");
    char *dequeueString = NULL;
    dequeueString = dequeue();
    if (allDigit(dequeueString))
        {
        command->etc = atoi(dequeueString);
        }
    else
        {
        printf("\tValue contain non-digit\n");
        validCommand = FALSE;
        }
    free(dequeueString);
    return validCommand;
    }

/* validate each argument for shape command
* Arguments :
*     command - pointer to a command struct
*     commandName - name for the command
*     pointCount - point number for the shape
* Return :
*      boolean value , true if command was created
*/
BOOL createShapeCommand(COMMAND_T *command, char *commandName, int pointCount)
    {
    BOOL validCommand = TRUE;
    command->name = commandName;
    command->points = (POINT_T *) calloc(sizeof(POINT_T), pointCount);
    /* Check if name and point allocated , (name always get by strdup)*/
    if ((command->name != NULL) && (command->points != NULL))
        {
        for (int i = 0; i < pointCount; i++)
            {
            char *dequeueStringX = NULL;
            char *dequeueStringY = NULL;

            dequeueStringX = dequeue();
            dequeueStringY = dequeue();
            /* check all digit for x and y point */
            if (allDigit(dequeueStringX) && allDigit(dequeueStringY))
                {
                command->points[i].x = atoi(dequeueStringX);
                command->points[i].y = atoi(dequeueStringY);
                free(dequeueStringX);
                free(dequeueStringY);
                }
            else
                {
                printf("\tValue contain non-digit\n");
                validCommand = FALSE;
                free(dequeueStringX);
                free(dequeueStringY);
                break;
                }
            }
        command->pointCount = pointCount;

        if (command->mode == CIRCLE || command->mode == CIRCLEFILL)
            {
            /* command mode that have extra value */
            char *dequeueString = NULL;
            dequeueString = dequeue();
            if (allDigit(dequeueString))
                {
                command->etc = atoi(dequeueString);
                }
            else
                {
                printf("\tValue contain non-digit\n");
                validCommand = FALSE;
                }
            free(dequeueString);
            }
        else
            {
            command->etc = -1;
            }

        /* check the color in the list */
        command->color = findColor(dequeue(), 1);
        if (command->color == NULL)
            {
            printf("\tCan't find color \n");
            validCommand = FALSE;
            }
        }
    else
        {
        printf("\tCan't allocate data for command's components\n");
        validCommand = FALSE;
        }
    return validCommand;
    }

/* open file with the name of *filename , read it and add the command to the list*/
void loadCommands(char *filename)
    {
    FILE *filein = NULL;
    char lineFromFile[MAXCHAR];
    int flag;
    if (strncasecmp(filename + (strlen(filename) - 4), ".sav", 4) != 0)
        {
        char outputName[64];
        strcpy(outputName, filename);
        strcat(outputName, ".sav");
        free(filename);
        filename = strdup(outputName);
        }
    filein = fopen(filename, "r");
    if (filein != NULL)
        {
        while (fgets(lineFromFile, sizeof(lineFromFile), filein) != NULL)
            {
            /* create a command from the file */
            MODE mode;
            char *modeTemp;
            COMMAND_T *newCommand = (COMMAND_T *) calloc(1, sizeof(COMMAND_T));
            if (lineFromFile[strlen(lineFromFile)] == '\n')
                {
                lineFromFile[strlen(lineFromFile)] = '\0';
                }
            queueCommand(strdup(lineFromFile));

            modeTemp = dequeue();
            mode = atoi(modeTemp);
            free(modeTemp);

            /* add command to the list */
            flag = createCommand(newCommand, mode);
            if (flag != -1)
                {
                printf("\t Insert new commands : %s\n", newCommand->name);
                if (flag)
                    {
                    listInsertEnd(commands, newCommand);
                    }
                }
            }
        fclose(filein);
        }
    else
        { printf("\terror - cannot open file\n"); }

    free(filename);
    }

