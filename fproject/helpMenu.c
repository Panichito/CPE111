//
// Created by ASUS on 3/13/2021.
//
#include <stdio.h>
#include <strings.h>


#include "commandFunctions.h"
#include "utility.h"
#include "helpMenu.h"
#include "colorFunctions.h"

HELP_T help[35] = {{"CreateImg",                       "[x] [y]",                                           "create the canvas (top-left is (0,0), bottom-right is (x-1,y-1)) *require to do before drawing"},
                   {"Background",                      "[color]",                                           "change background's color"},
                   {"Brush",                           "[size]",                                            "change brush size (pixel)"},
                   {"Circle/CircleFill",               "[cx] [cy] [r] [color]",                             "create circle center at (cx,cy) with radius (r)"},
                   {"Line/LineDash",                   "[x1] [y1] [x2] [y2] [color]",                       "create line from (x1,y1) to (x2,y2)"},
                   {"Rectangle/RectangleFill",         "[x1] [y1] [x2] [y2] [color]",                       "create rectangle top-left (x1,y1) , bottom-right (x2,y2)"},
                   {"Triangle/TriangleFill",           "[cx] [cy] [w] [h] [color]",                         "create triangle base center at (cx,cy) with width of (w) height of (h)"},
                   {"Diamond/DiamondFill",             "[cx] [cy] [w] [h] [color]",                         "create diamond center at (cx,cy) with width of (w) height/depth of (h)"},
                   {"Ellipse/EllipseFill",             "[cx] [cy] [rx] [ry] [color]",                       "create circle center at (cx,cy) with radius each axis (rx) and (ry)"},
                   {"Arc/ArcFilled",                   "[cx] [cy] [w] [rx] [ry] [e] [color]",               "create arc center at (cx,cy) with radius each axis (rx) and (ry) arc-length (s) sector (e)"},
                   {"Polygon/PolygonOpen/PolygonFill", "[x1] [y1] [x2] [y2] .. [xn] [yn] [color]",          "create polygon connecting with given coordinate in-order\n\tVariation of command , Fill - fill color inside the shape , Open - won't connect last dot to first dot"},
                   {"Draw",                            "[outputName]",                                      "create .png image with given instruction"},
                   {"List",                            "no argument",                                       "show all the commands added by user with index"},
                   {"Edit",                            "[index in list] [argument required for the shape]", "edit content of a command *can't change the shape"},
                   {"Move",                            "[index1] [index2]",                                 "move item from position [index1] to position [index2]"},
                   {"Swap",                            "[index1] [index2]",                                 "swap 2 item in list"},
                   {"Remove",                          "[index]",                                           "remove a command"},
                   {"Reset",                           "no argument",                                       "clear everything and restart the program"},
                   {"Save",                            "[filename (with or without .sav)]",                 "save instruction to file"},
                   {"Load",                            "[filename (with or without .sav)]",                 "load instruction from file *added to existing commands"},
                   {"Color",                           "[List/Add/Edit/Delete/Save/Load] [Args]",           "use color commands"},
                   {"Help",                            "[command name]",                                    "show detail of the command"},
                   {"Exit",                            "no argument",                                       "exit program"}};

HELP_T help_color[7] = {{"List",   "no argument",                       "show all color"},
                        {"Add",    "[name] [r] [g] [b] [a]",            "add new color to list with name and rgba value"},
                        {"Edit",   "[name] [r] [g] [b] [a]",            "edit value of existing color"},
                        {"Delete", "[name]",                            "delete color from list"},
                        {"Save",   "[filename (with or without .dat)]", "save user added color to file"},
                        {"Load",   "[filename (with or without .dat)]", "load custom color from file to list"},
                        {"Exit",   "no argument",                       "exit program"}};

/* printallhelp function
 * Printing all command including names, arguments, drescription
 * printing list of 5 commands at a time. 
 * Arguements
 *      no argument.
 *
 * recieving Y as ture to proceed printing commands
 * recieving N as false to exit function
 */
void printallhelp()
    {
    int i = 0;
    int k = 0;

    while (1)
        {
        for (i = k; i < k + 5; ++i)
            {
            printf("%2d. %-20s \tArgument: %-25s \tExplanation: %s \n\n", i + 1, help[i].commandName,
                   help[i].commandArgs,
                   help[i].commandDef);
            if (i == 21)
                {
                printf("end of command list\n");
                return;
                }
            }
        k = k + 5;

        if (boolPrompt("want to see 5 more?(y/n)", "Y", "N"))
            {
            continue;
            }
        else
            {
            break;
            }
        }

    }

/* printallhelp_color function
 * Printing all color command including names, arguments, drescription
 * 
 * Arguements
 *      count : number of command print.
 */
void printallhelp_color(int count)
    {
    int i = 0;

    for (i = 0; i < count; ++i)
        {
        printf("%2d. %-20s \tArgument: %-25s \tExplanation: %s \n\n", i + 1, help_color[i].commandName,
               help_color[i].commandArgs,
               help_color[i].commandDef);
        }

    }

/* printonehelp function
 * Printing only selected command
 * 
 * Arguements
 *      helpIndex - selected command position in the array.
 *      colorindex - indicate which is general command or color command
 *                   0 - general command
 *                   1 - color command
 */
void printonehelp(int helpIndex, int colorindex)
    {
    if (colorindex == 0)
        {
        printf("\n\t%s \tArgument: %s \tExplanation: %s \n\n", help[helpIndex].commandName, help[helpIndex].commandArgs,
               help[helpIndex].commandDef);
        }
    else if (colorindex == 1)
        {
        printf("\n\t%s \tArgument: %s \tExplanation: %s \n\n", help_color[helpIndex].commandName,
               help_color[helpIndex].commandArgs, help_color[helpIndex].commandDef);
        }
//        else
//        {
//            printf("it is appear to be some bugs\n");
//        }
    }

/* askforhelp function
 * recieve mode from main as integer then send to print
 * 
 * Arguements
 *      commandIndex - MODE from commandFunctions
 */
void askforhelp(int commandIndex)
    {
    switch (commandIndex)
        {
        case CREATEIMG:
            printonehelp(0, 0);
            break;
        case BACKGROUND:
            printonehelp(1, 0);
            break;
        case BRUSH:
            printonehelp(2, 0);
            break;
        case CIRCLE:
        case CIRCLEFILL:
            printonehelp(3, 0);
            break;
        case LINE:
        case LINEDASH:
            printonehelp(4, 0);
            break;
        case RECTANGLE:
        case RECTANGLEFILL:
            printonehelp(5, 0);
            break;
        case TRIANGLE:
        case TRIANGLEFILL:
            printonehelp(6, 0);
            break;
        case DIAMOND:
        case DIAMONDFILL:
            printonehelp(7, 0);
            break;
        case ELLIPSE:
        case ELLIPSEFILL:
            printonehelp(8, 0);
            break;
        case ARC:
        case ARCFILL:
            printonehelp(9, 0);
            break;
        case POLY:
        case POLYOPEN:
        case POLYFILL:
            printonehelp(10, 0);
            break;
        case DRAW:
            printonehelp(11, 0);
            break;
        case LIST:
            printonehelp(12, 0);
            break;
        case EDIT:
            printonehelp(13, 0);
            break;
        case MOVE:
            printonehelp(14, 0);
            break;
        case SWAP:
            printonehelp(15, 0);
            break;
        case REMOVE:
            printonehelp(16, 0);
            break;
        case RESET:
            printonehelp(17, 0);
            break;
        case SAVE:
            printonehelp(18, 0);
            break;
        case LOAD:
            printonehelp(19, 0);
            break;
        case COLOR:
            printonehelp(20, 0);
            printallhelp_color(6);
            break;
        case HELP:
            printonehelp(21, 0);
            break;
        default:
            printf("\tInvalid command\n");
            break;
        }
    }

/* askforhelp_color function
 * recieve MODE as integer then send to print
 * 
 * Arguements
 *      commandIndex_color - MODE from colorFunctions
 */
void askforhelp_color(int commandIndex_color)
    {
    switch (commandIndex_color)
        {
        case COLORLIST:
            printonehelp(0, 1);
            break;
        case COLORADD:
            printonehelp(1, 1);
            break;
        case COLOREDIT:
            printonehelp(2, 1);
            break;
        case COLORDEL:
            printonehelp(3, 1);
            break;
        case COLORSAVE:
            printonehelp(4, 1);
            break;
        case COLORLOAD:
            printonehelp(5, 1);
            break;
        case COLOREXIT:
            printonehelp(6, 1);
            break;
        default:
            printf("\tInvalid command\n");
            break;
        }
    }
