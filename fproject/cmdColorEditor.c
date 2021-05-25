/* cmdColorEditor
 *   This program is the main program when user called COLOR command.
 *   The program will ask the user for a color command in command line
 *   and validate the input, then this program will use colorFunction to
 *   manipulate the color from the task.
 *
 *   Created by Rickrollaphobia group
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include "colorFunctions.h"
#include "helpMenu.h"

#include "abstractQueueMod.h"
#include "utility.h"

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
            enqueue(strdup(temp));
            start = i + 1;
            }
        }
    free(input); /*free the input*/
    }

/* mainColor
    This function will be called if the user input COLOR command.
    This function can manipulate and edit the color list and can also 
    save the new user colors and store in text file to load them after 
    user close the program and want to use them again */
int main()
    {
    readColor();
    int option = 0;
    while (option != COLOREXIT)
        {
        /* asks for the command */
        queueCommand(messageIOString("Enter command"));
        /* get the command MODE */
        option = getColorCommand(dequeue());
        switch (option)
            {
            case COLORLIST:
                /* COLORLIST - this mode will print all the color properties */
                printAllColor();
                break;
            case COLORADD:
                /* COLORADD - this mode will add the new color into the list
                 *            must have 5 value in the queue 
                 */
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
                /* COLOREDIT - this mode will edit the color properties
                 *             must have 5 value in the queue 
                 */
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
                /* COLORDEL - this mode will delete the color from color name */
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
                /* COLORSAVE - this mode will save the user added color into text file */
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
                /* COLORLOAD - this mode will load the user added color from text file */
                if (queueSize() == 1)
                    {
                    loadUserColor(dequeue());
                    }
                else
                    {
                    printf("\tWrong format\n");
                    }
                break;
            case COLORHELP:
                if (queueSize() == 0)
                    {
                    printallhelp_color(7);
                    }
                else if (queueSize() >= 1)
                    {
                    askforhelp_color(getColorCommand(dequeue()));
                    };
                break;
            case COLOREXIT:
                break;
            default:
                printf("\nInvalid command\n");
            }
        }
    queueClear(TRUE);
    freeColor();
    return 0;
    }