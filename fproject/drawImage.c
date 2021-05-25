/* drawImage
 * process the list of commands provided by user
 * drawing each component then turn it into an image
 * and finally write it to a png file
 *
 *   Created by Rickrollaphobia group
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <gd.h>
#include "drawImage.h"

int totalColor; /*Total color allocated*/

/* getColor
 *  check if the color is already allocated in the program
 *  if isn't , allocate it then +1 to total color this
 *  will give allocate value to the color
 *  else return the allocate color of that color
 *
 * Arguments:
 *  im : pointer to image
 *  color : pointer to color struct
 *
 * Return : the allocate value of that color
 */
int getColor(gdImagePtr im, COLOR_T *color);

/*drawObject
 * from command item define and draw the shape to image
 *
 * Argument :
 * im : pointer to image
 * command : pointer to command item
 *
 */
void drawObject(gdImagePtr im, COMMAND_T *command);

/* drawImageTriangle
 *  draw triangle to image by making the command into a polygon command
 *
 *  Arguments:
 *  im : pointer to image
 *  command : pointer to command
 *  bFill : boolean if the shape is a fill or not
 *
 */
void drawImageTriangle(gdImagePtr im, COMMAND_T *command, int bFill);

/* drawImageDiamond
 *  draw diamond to image by making the command into a polygon command
 *
 *  Arguments:
 *  im : pointer to image
 *  command : pointer to command
 *  bFill : boolean if the shape is a fill or not
 *
 */
void drawImageDiamond(gdImagePtr im, COMMAND_T *command, int bFill);



/**PUBLIC**/

/* drawImg
 * processing each command in list and draw it to memory
 * then finally draw it to image file
 *
 * Arguments:
 *  filename : output file name
 *  setuo[] : array of few commands that essential to create image
 *  commands : list of commands
 *
 * Return:
 *  boolean value that indicate if the image is created or not
 */
BOOL drawImg(char *filename, COMMAND_T *setup[], LIST_HANDLE commands)
    {
    BOOL flag = TRUE;
    /* Declare pointer to the image's memory */
    gdImagePtr im = NULL;
    /* Declare output files */
    FILE *fileout = NULL;

    totalColor = 0; /* set total color to 0 */

    if (setup[0] != NULL)
        {
        im = gdImageCreate(setup[0]->points[0].x, setup[0]->points[0].y);
        /* allocate image */

        if (im != NULL)
            {

            if (setup[1] != NULL)
                {
                getColor(im, setup[1]->color);
                }
            else
                {
                printf("\tBackground color isn't set : using WHITE as background\n");
                gdImageColorAllocateAlpha(im, 255, 255, 255, 1);
                totalColor++;
                }

            if (setup[2] != NULL)
                {
                gdImageSetThickness(im, setup[2]->etc);
                }

            listReset(commands);
            COMMAND_T *drawCommand = (COMMAND_T *) listGetNext(commands);
            while (drawCommand != NULL)
                {
                drawObject(im, drawCommand);
                drawCommand = (COMMAND_T *) listGetNext(commands);
                }

            /*check extension for filename*/
            if (strncasecmp(filename + (strlen(filename) - 4), ".png", 4) != 0)
                {
                char outputName[64];
                strcpy(outputName, filename);
                strcat(outputName, ".png");
                free(filename);
                filename = strdup(outputName);
                }
            fileout = fopen(filename, "wb");

            printf("\tImage created : saved as \"%s\"\n", filename);

            /* Output the image to the disk file in PNG format. */
            gdImagePng(im, fileout);

            free(filename);
            /* Close the files. */
            fclose(fileout);

            /*free allocated color*/
            for (int i = totalColor; i >= 0; i--)
                {
                gdImageColorDeallocate(im, i);
                }
            resetAllocateColor();

            /* Destroy the image in memory. */
            gdImageDestroy(im);
            }
        }
    else
        {
        flag = FALSE;
        printf("\tMust create img first (HELP for more details)\n");
        }
    }

/**PRIVATE**/

/* getColor
 *  check if the color is already allocated in the program
 *  if isn't , allocate it then +1 to total color this
 *  will give allocate value to the color
 *  else return the allocate color of that color
 *
 * Arguments:
 *  im : pointer to image
 *  color : pointer to color struct
 *
 * Return : the allocate value of that color
 */
int getColor(gdImagePtr im, COLOR_T *color)
    {
    if (color->allocate == -1)
        {
        color->allocate = gdImageColorAllocateAlpha(im, color->value[0], color->value[1], color->value[2],
                                                    color->value[3]);
        totalColor++;
        }
    return color->allocate;
    }

/*drawObject
 * from command item define and draw the shape to image
 *
 * Argument :
 * im : pointer to image
 * command : pointer to command item
 *
 */
void drawObject(gdImagePtr im, COMMAND_T *command)
    {
    printf("\t\tDrawing : %s\n", command->name);
    switch (command->mode)
        {
        case CIRCLE:
            gdImageEllipse(im, command->points[0].x, command->points[0].y, command->etc, command->etc,
                           getColor(im, command->color));
            break;
        case CIRCLEFILL:
            gdImageFilledEllipse(im, command->points[0].x, command->points[0].y, command->etc, command->etc,
                                 getColor(im, command->color));
            break;
        case LINE:
            gdImageLine(im, command->points[0].x, command->points[0].y, command->points[1].x, command->points[1].y,
                        getColor(im, command->color));
            break;
        case LINEDASH:
            gdImageDashedLine(im, command->points[0].x, command->points[0].y, command->points[1].x,
                              command->points[1].y, getColor(im, command->color));
            break;
        case RECTANGLE:
            gdImageRectangle(im, command->points[0].x, command->points[0].y, command->points[1].x, command->points[1].y,
                             getColor(im, command->color));
            break;
        case RECTANGLEFILL:
            gdImageFilledRectangle(im, command->points[0].x, command->points[0].y, command->points[1].x,
                                   command->points[1].y, getColor(im, command->color));
            break;

        case TRIANGLE:
            drawImageTriangle(im, command, 0);
            break;
        case TRIANGLEFILL:
            drawImageTriangle(im, command, 1);
            break;
        case DIAMOND:
            drawImageDiamond(im, command, 0);
            break;
        case DIAMONDFILL:
            drawImageDiamond(im, command, 1);
            break;
        case ELLIPSE:
            gdImageEllipse(im, command->points[0].x, command->points[0].y, command->points[1].x, command->points[1].y,
                           getColor(im, command->color));
            break;
        case ELLIPSEFILL:
            gdImageFilledEllipse(im, command->points[0].x, command->points[0].y, command->points[1].x,
                                 command->points[1].y, getColor(im, command->color));
            break;
        case ARC:
            gdImageArc(im, command->points[0].x, command->points[0].y, command->points[1].x, command->points[1].y,
                       command->points[2].x, command->points[2].y, getColor(im, command->color));
            break;
        case ARCFILL:
            gdImageFilledArc(im, command->points[0].x, command->points[0].y, command->points[1].x, command->points[1].y,
                             command->points[2].x, command->points[2].y, getColor(im, command->color), 0);
            break;
        case POLY:
            gdImagePolygon(im, (gdPointPtr) command->points, command->pointCount, getColor(im, command->color));
            break;
        case POLYOPEN:
            gdImageOpenPolygon(im, (gdPointPtr) command->points, command->pointCount, getColor(im, command->color));
            break;
        case POLYFILL:
            gdImageFilledPolygon(im, (gdPointPtr) command->points, command->pointCount, getColor(im, command->color));
            break;
        }
    }

/* drawImageTriangle
*  draw triangle to image by making the command into a polygon command
*
*  Arguments:
*  im : pointer to image
*  command : pointer to command
*  bFill : boolean if the shape is a fill or not
*
*/
void drawImageTriangle(gdImagePtr im, COMMAND_T *command, int bFill)
    {
    gdPoint trianglePoint[3]; /*points for drawing triangle*/

    /*process command into points to draw shape*/
    trianglePoint[0].x = command->points[0].x + command->points[1].x;
    trianglePoint[0].y = command->points[0].y;

    trianglePoint[1].x = command->points[0].x - command->points[1].x;
    trianglePoint[1].y = command->points[0].y;

    trianglePoint[2].x = command->points[0].x;
    trianglePoint[2].y = command->points[0].y - command->points[1].y;

    if (bFill)
        { gdImageFilledPolygon(im, trianglePoint, 3, getColor(im, command->color)); }
    else
        { gdImagePolygon(im, trianglePoint, 3, getColor(im, command->color)); }
    }

/* drawImageDiamond
*  draw diamond to image by making the command into a polygon command
*
*  Arguments:
*  im : pointer to image
*  command : pointer to command
*  bFill : boolean if the shape is a fill or not
*
*/
void drawImageDiamond(gdImagePtr im, COMMAND_T *command, int bFill)
    {
    gdPoint diamondPoint[4]; /*points for drawing diamond*/

    /*process command into points to draw shape*/
    diamondPoint[0].x = command->points[0].x + command->points[1].x;
    diamondPoint[0].y = command->points[0].y;

    diamondPoint[1].x = command->points[0].x - command->points[1].x;
    diamondPoint[1].y = command->points[0].y;

    diamondPoint[2].x = command->points[0].x;
    diamondPoint[2].y = command->points[0].y - command->points[1].y;

    diamondPoint[3].x = command->points[0].x;
    diamondPoint[3].y = command->points[0].y + command->points[1].y;

    if (bFill)
        { gdImageFilledPolygon(im, (gdPointPtr) diamondPoint, 4, getColor(im, command->color)); }
    else
        { gdImagePolygon(im, (gdPointPtr) diamondPoint, 4, getColor(im, command->color)); }
    }

