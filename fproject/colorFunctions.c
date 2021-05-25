/* colorFunctions.c
 *  This file manipulate the color system of the program including
 *  adding, editing, deleting, load and save color.
 *
 *   Created by Rickrollaphobia group
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include "linkedListUtilMod.h"
#include "colorFunctions.h"

LIST_HANDLE *allColor;

/* getColorCommand function
 *   This function will compare the input command
 *   into mode ID. Have argument:
 *       input - input command from user
 *
 *   This function will return the mode ID
 */
int getColorCommand(char *input)
    {
    int commandID = COLORERR;

    /* compare the input with the mode name */
    if (strcasecmp(input, "list") == 0)
        commandID = 1;
    else if (strcasecmp(input, "add") == 0)
        commandID = 2;
    else if (strcasecmp(input, "edit") == 0)
        commandID = 3;
    else if (strcasecmp(input, "delete") == 0)
        commandID = 4;
    else if (strcasecmp(input, "save") == 0)
        commandID = 5;
    else if (strcasecmp(input, "load") == 0)
        commandID = 6;
    else if (strcasecmp(input, "help") == 0)
        commandID = 7;
    else if (strcasecmp(input, "exit") == 0)
        commandID = 99;

    free(input);
    return commandID;
    }


/* readColor()
 *   This function should be called first when program started and
 *   will read all color from file 'defaultColor.dat' then add to list.
 *   This function doesn't have return value.
 */
void readColor()
    {
    FILE *pDefaultColor = NULL;
    char inputBuffer[32];

    /* create new list to store all color */
    allColor = newList();
    pDefaultColor = fopen("defaultColor.dat", "r");
    if (pDefaultColor == NULL) /* can't open default color file */
        {
        printf("Error - Can't open defaultColor.dat file...\n");
        exit(0);
        }
    while (fgets(inputBuffer, sizeof(inputBuffer), pDefaultColor) != NULL)
        {
        COLOR_T *colorSet = (COLOR_T *) calloc(1, sizeof(COLOR_T));
        if (colorSet != NULL)
            {
            /* store each color from default color file into the linked list */
            sscanf(inputBuffer, "%s %d %d %d %d", colorSet->name, &colorSet->value[0], &colorSet->value[1],
                   &colorSet->value[2], &colorSet->value[3]);
            colorSet->allocate = -1;
            listInsertEnd(allColor, colorSet);
            }
        else
            {
            printf("Error - Can't allocate memory...\n");
            exit(1);
            }
        }
    fclose(pDefaultColor);
    }


/* checkDefaultColor function
 *   Debug function - check is all default color is loaded 
 *   This function will check the input that is the same name with
 *   default color or not by getting a argument
 *       findName - the name of color that you want to check
 *      
 *   This function will return 1 if it's the same name and will
 *   return 0 if not
 */
int checkDefaultColor(char *findName)
    {
    char defaultColor[11][64] = {"white", "black", "gray", "red", "green", "blue",
                                 "orange", "pink", "purple", "yellow", "brown"
    };
    int i;
    for (i = 0; i < 11; i++)
        {
        /* compare the input name with all default color name */
        if (strcasecmp(findName, defaultColor[i]) == 0)
            return 1;
        }
    return 0;
    }


/* findColor
 *   This function will traverse the color list to find the color
 *   and return color structure if it find. Return NULL if not.
 *       colorName - Name of searched color
 *       bFree - boolean to free the string argument or not 
 */
COLOR_T *findColor(char *colorName, int bFree)
    {
    COLOR_T *currentColor = NULL;
    COLOR_T *colorFound = NULL;

    listReset(allColor);
    /* get the head of all color list */
    currentColor = listGetNext(allColor);
    while (currentColor != NULL)
        {
        /* compare the name of searched color with current color list */
        if (strcasecmp(colorName, currentColor->name) == 0)
            {
            colorFound = currentColor;
            }
        /* if not the same, go to next color list */
        currentColor = listGetNext(allColor);
        }
    if (bFree == 1)
        free(colorName);
    return colorFound;
    }


/* checkAllDigit
 *   This function will check the string argument that all character
 *   is digit or not. This function have a argument
 *       stringToCheck - the string to check each character
 *
 *   This function will return 1 if all character are all digit
 *   and will return 0 if not 
 */
int checkAllDigit(char *stringToCheck)
    {
    int i;
    for (i = 0; i < strlen(stringToCheck); i++)
        {
        /* check that character is digit or not */
        if (isdigit(stringToCheck[i]) == 0)
            return 0;
        }
    return 1;
    }


/* addColor
 *   This function will add the new color to the end of all color list and
 *   set allocate value to -1
 *   This function receives 5 arguments:
 *       colorName - name of the new color
 *       redValue - red color value 0-255
 *       greenValue - green color value 0-255
 *       blueValue - blue color value 0-255
 *       alphaValue - opacity of color
 *
 *   This function will return 1 if successfully add the new color and
 *   return 0 if not
 */
int addColor(char *colorName, char *redValue, char *greenValue, char *blueValue, char *alphaValue)
    {
    int rgbaValue[4] = {-1, -1, -1, -1};
    COLOR_T *newColor = NULL;

    /* validate the name of new color */
    if (findColor(colorName, 0) != NULL) /* check the color that exist or not */
        printf("   Error - This color name already exist...\n");
    else
        {
        /* validate the rgba value */
        if ((checkAllDigit(redValue) == 0) || (checkAllDigit(greenValue) == 0) ||
            (checkAllDigit(blueValue) == 0) || (checkAllDigit(alphaValue) == 0))
            printf("   Error - RGB value must be an INTEGER between 0-255.\n");
        else
            {
            rgbaValue[0] = atoi(redValue);
            rgbaValue[1] = atoi(greenValue);
            rgbaValue[2] = atoi(blueValue);
            rgbaValue[3] = atoi(alphaValue);
            if (((rgbaValue[0] > 255) || (rgbaValue[0] < 0)) ||
                ((rgbaValue[1] > 255) || (rgbaValue[1] < 0)) ||
                ((rgbaValue[2] > 255) || (rgbaValue[2] < 0)))
                printf("   Error - RGB value must be an INTEGER between 0-255.\n");
            else
                {
                /* add the new color to the end of the list */
                newColor = (COLOR_T *) calloc(1, sizeof(COLOR_T));
                strcpy(newColor->name, colorName);
                newColor->value[0] = rgbaValue[0];
                newColor->value[1] = rgbaValue[1];
                newColor->value[2] = rgbaValue[2];
                newColor->value[3] = rgbaValue[3];
                newColor->allocate = -1;
                printf("   [ADD] %s %d %d %d %d\n", newColor->name, newColor->value[0], newColor->value[1],
                       newColor->value[2], newColor->value[3]);
                listInsertEnd(allColor, newColor);
                free(colorName);
                free(redValue);
                free(greenValue);
                free(blueValue);
                free(alphaValue);
                return 1;
                }
            }
        }
    free(colorName);
    free(redValue);
    free(greenValue);
    free(blueValue);
    free(alphaValue);
    return 0;
    }


/* editColor
 *   This function will edit the color property from all color list
 *   This function receives 5 arguments:
 *       colorName - name of the edit color
 *       redValue - red color value 0-255
 *       greenValue - green color value 0-255
 *       blueValue - blue color value 0-255
 *       alphaValue - opacity of color
 *
 *   This function will return 1 if successfully edit color and
 *   return 0 if not
 */
int editColor(char *colorName, char *redValue, char *greenValue, char *blueValue, char *alphaValue)
    {
    int rgbaValue[4] = {-1, -1, -1, -1};
    COLOR_T *editColor = NULL;

    /* find the edit color that exist or not */
    editColor = findColor(colorName, 0);
    if (editColor == NULL) /* not exist */
        printf("   Error - This color is not exist...\n");
    else if (checkDefaultColor(colorName) == 1)
        printf("   Error - This is default color\n");
    else
        {
        /* validate the rgba value */
        if ((checkAllDigit(redValue) == 0) || (checkAllDigit(greenValue) == 0) ||
            (checkAllDigit(blueValue) == 0) || (checkAllDigit(alphaValue) == 0))
            printf("   Error - RGB value must be an INTEGER between 0-255.\n");
        else
            {
            rgbaValue[0] = atoi(redValue);
            rgbaValue[1] = atoi(greenValue);
            rgbaValue[2] = atoi(blueValue);
            rgbaValue[3] = atoi(alphaValue);
            if (((rgbaValue[0] > 255) || (rgbaValue[0] < 0)) ||
                ((rgbaValue[1] > 255) || (rgbaValue[1] < 0)) ||
                ((rgbaValue[2] > 255) || (rgbaValue[2] < 0)))
                printf("   Error - RGB value must be an INTEGER between 0-255.\n");
            else
                {
                /* change/edit the color property */
                editColor->value[0] = rgbaValue[0];
                editColor->value[1] = rgbaValue[1];
                editColor->value[2] = rgbaValue[2];
                editColor->value[3] = rgbaValue[3];
                printf("   [EDIT] %s color successfully\n", colorName);
                free(colorName);
                free(redValue);
                free(greenValue);
                free(blueValue);
                free(alphaValue);
                return 1;
                }
            }
        }
    free(colorName);
    free(redValue);
    free(greenValue);
    free(blueValue);
    free(alphaValue);
    return 0;
    }


/* deleteColor
 *   This function will delete the selected color list from the input argument
 *   name of color. Argument:
 *       colorName - name of delete color
 *
 *   This function will return 1 if successfully delete and
 *   will return 0 if not
 */
int deleteColor(char *colorName)
    {
    COLOR_T *colorSet = NULL;
    int count;

    count = 0;
    listReset(allColor);
    colorSet = listGetNext(allColor);
    while (colorSet != NULL)
        {
        /* find the position of delete color in the list */
        if (strcasecmp(colorName, colorSet->name) == 0)
            {
            /* validate the color that is default color or not */
            if (checkDefaultColor(colorName) == 1)
                {
                printf("   Error - This is default color\n");
                free(colorName);
                return 0;
                }
            /* delete the color from the list */
            listRemove(allColor, count);
            free(colorSet);
            printf("   [DELETE] %s color successfully\n", colorName);
            free(colorName);
            return 1;
            }
        colorSet = listGetNext(allColor);
        count++;
        }
    printf("   Error - Can't find the color...\n");
    free(colorName);
    return 0;
    }


/* saveUserColor
 *   This function will save the user added color into text file that
 *   name by input argument. Users can be able to load this set of color
 *   after exit the program. Argument:
 *       fileName - new user color file name
 */
void saveUserColor(char *fileName)
    {
    FILE *pUserColor = NULL;
    COLOR_T *colorSet = NULL;

    /* add file type if user doesn't enter */
    if (strncasecmp(fileName + (strlen(fileName) - 4), ".dat", 4) != 0)
        {
        char outputName[64];
        strcpy(outputName, fileName);
        strcat(outputName, ".dat");
        free(fileName);
        fileName = strdup(outputName);
        }
    pUserColor = fopen(fileName, "w");
    if (pUserColor != NULL)
        {
        listReset(allColor);
        colorSet = listGetNext(allColor);
        while (colorSet != NULL)
            {
            /* skip default color in the list */
            if (checkDefaultColor(colorSet->name) == 1)
                {
                colorSet = listGetNext(allColor);
                continue;
                }
            /* write down the added color in text file */
            fprintf(pUserColor, "%s %d %d %d %d\n", colorSet->name, colorSet->value[0], colorSet->value[1],
                    colorSet->value[2], colorSet->value[3]);
            colorSet = listGetNext(allColor);
            }
        }
    /* successfully write and close the file */
    if (fclose(pUserColor) != 0)
        {
        printf("\tError - Writing file failed. Is your disk full?\n");
        exit(1);
        }
    printf("   [SAVE] save color into %s successfully\n", fileName);
    free(fileName);
    }


/* loadUserColor
 *   This function will load the color from text file that user store
 *   by using saveColor and will skip the repeat color by using the initial
 *   color in the list before the load. Argument:
 *       fileName - color file name
 */
void loadUserColor(char *fileName)
    {
    char inputBuffer[64];
    FILE *pUserColor = NULL;

    /* add the file type if user doesn't enter */
    if (strncasecmp(fileName + (strlen(fileName) - 4), ".dat", 4) != 0)
        {
        char outputName[64];
        strcpy(outputName, fileName);
        strcat(outputName, ".dat");
        free(fileName);
        fileName = strdup(outputName);
        }
    /* open the user color file */
    pUserColor = fopen(fileName, "r");
    if (pUserColor != NULL)
        {
        while (fgets(inputBuffer, sizeof(inputBuffer), pUserColor) != NULL)
            {
            COLOR_T *colorSet = (COLOR_T *) calloc(1, sizeof(COLOR_T));
            if (colorSet != NULL)
                {
                /* getting each color from the file and store in the list */
                sscanf(inputBuffer, "%s %d %d %d %d", colorSet->name, &colorSet->value[0], &colorSet->value[1],
                       &colorSet->value[2], &colorSet->value[3]);
                colorSet->allocate = -1;
                if (findColor(colorSet->name, 0) != NULL)
                    {
                    /* got the repeat color and skip it */
                    printf("\tGot the same %s color. Skipping...\n", colorSet->name);
                    free(colorSet);
                    continue;
                    }
                else
                    {
                    printf("Imported :\n\t[COLOR] %s\n\t r:%d g:%d b:%d a:%d\n", colorSet->name, colorSet->value[0],
                           colorSet->value[1],
                           colorSet->value[2], colorSet->value[3]);
                    }
                listInsertEnd(allColor, colorSet);
                }
            else
                {
                printf("\tError - Can't allocate memory...\n");
                exit(1);
                }
            }
        printf("   [LOAD] load color from %s successfully\n", fileName);
        fclose(pUserColor);
        }
    else
        printf("Error - Can't open %s file...\n", fileName);
    free(fileName);
    }


/* printAllColor
 *   This function will print all the color property from the list.
 *   Use to check and debug, etc.
 */
void printAllColor()
    {
    COLOR_T *colorSet = NULL;

    listReset(allColor);
    colorSet = listGetNext(allColor);
    printf("Lists of all color:\n");
    while (colorSet != NULL)
        {
        /* print the properties and go to next color in the list */
        printf("   [COLOR] %s\n\t r:%d g:%d b:%d a:%d\n", colorSet->name, colorSet->value[0], colorSet->value[1],
               colorSet->value[2], colorSet->value[3]);
        colorSet = listGetNext(allColor);
        }
    }

/* resetAllocateColor()
This function will change all allocate value to -1 */
void resetAllocateColor()
    {
    COLOR_T *colorSet = NULL;

    listReset(allColor);
    colorSet = listGetNext(allColor);
    while (colorSet != NULL)
        {
        colorSet->allocate = -1;
        colorSet = listGetNext(allColor);
        }
    }

/* freeColor()
    This function will free all the list, should be called at the end of program */
void freeColor()
    {
    COLOR_T *colorSet = NULL;

    listReset(allColor);
    colorSet = listGetNext(allColor);
    while (colorSet != NULL)
        {
        /* free the current list and go to next list */
        free(colorSet);
        colorSet = listGetNext(allColor);
        }
    listDestroy(allColor);
    }
