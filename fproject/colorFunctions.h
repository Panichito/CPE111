/* colorFunctions.h
 * 
 * Header file for colorFunctions.c
 *
 * This file contains the function about color list that the program can do. 
 * And includes the command for manipulated within the color linked list data structure.
 *
 * Created by Rickrollaphobia group
 */

/* OverAll
 * - read all color from file then add to list
 * - user can add & edit new color
 * - user can save “user added color”
 * - findColor(char* colorName)
       - traverse color list , find colorName
       - if found return pointer to data
*/

#ifndef COLOR_HEADER
#define COLOR_HEADER

#define COLORERR -99
#define COLORLIST 1
#define COLORADD 2
#define COLOREDIT 3
#define COLORDEL 4
#define COLORSAVE 5
#define COLORLOAD 6
#define COLORHELP 7
#define COLOREXIT 99

typedef struct _color
    {
    char name[64];//name of color
    int value[4];// rgba value
    int allocate;// allocate value of color (given from drawimage.c)
    } COLOR_T;

/* getColorCommand function
 *   This function will compare the input command
 *   into mode ID. Have argument:
 *       input - input command from user
 *
 *   This function will return the mode ID
 */
int getColorCommand(char *input);


/* readColor()
    This function should be called first when program started and
    will read all color from file 'defaultColor.dat' and 'userColor.dat'
    then add to list */
void readColor();


/* findColor
    This function will traverse the color list to find the color
    and return color structure if it find. Return NULL if not.
        colorName - Name of searched color
        bFree - boolean for free the string argument or not */
COLOR_T* findColor(char* colorName, int bFree);


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
int addColor(char *colorName, char *redValue, char *greenValue, char *blueValue, char *alphaValue);


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
int editColor(char *colorName, char *redValue, char *greenValue, char *blueValue, char *alphaValue);


/* deleteColor
 *   This function will delete the selected color list from the input argument
 *   name of color. Argument:
 *       colorName - name of delete color
 *
 *   This function will return 1 if successfully delete and
 *   will return 0 if not
 */
int deleteColor(char *colorName);


/* saveUserColor
 *   This function will save the user added color into text file that
 *   name by input argument. Users can be able to load this set of color
 *   after exit the program. Argument:
 *       fileName - new user color file name
 */
void saveUserColor(char *fileName);


/* loadUserColor
 *   This function will load the color from text file that user store
 *   by using saveColor and will skip the repeat color by using the initial
 *   color in the list before the load. Argument:
 *       fileName - color file name
 */
void loadUserColor(char *fileName);


/* resetAllocateColor()
This function will change all allocate value to -1 */
void resetAllocateColor();


/* freeColor()
    This function will free all the list, should be called at the end of program */
void freeColor();


/* printAllColor()
    This function will print all the color property from the list. */
void printAllColor();


#endif /* !COLOR_HEADER */
