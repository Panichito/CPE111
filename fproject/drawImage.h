/* drawImage
 * process the list of commands provided by user
 * drawing each component then turn it into an image
 * and finally write it to a png file
 *
 *   Created by Rickrollaphobia group
 */
#ifndef DRAWIMAGE_H
#define DRAWIMAGE_H

#include "commandFunctions.h"
#include "linkedListUtilMod.h"

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
BOOL drawImg(char* filename,COMMAND_T* setup[],LIST_HANDLE commands);

#endif