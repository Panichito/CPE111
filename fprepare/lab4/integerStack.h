/**
 *  integerStack.h
 *
 *  Header file defining the operations that one can
 *  do on a stack whose elements are integers.
 *
 *  This can be implemented in a variety of ways.
 *
 *  Created by Sally Goldin, 26 January 2016 for CPE113
 *
 */

#ifndef INTEGERSTACK_H
#define INTEGERSTACK_H

#define UNDERFLOW -9999

/**
 * Push a data item onto the stack 
 * Arguments:
 *   intdata      -   integer value to be pushed  
 * Returns 1 if successful, 0 if we have an overflow.
 */
int pushInt(int intdata);


/**
 * Removes and returns the top item on the stack.
 * Returns special value -9999 if the queue is empty 
 * (that is, underflow).
 */
int popInt();



/**
 *  Find out how many items are currently in the stack.
 * Return number of items in the queue (could be zero)
 */
int stackSizeInt();


/**
 *  Clear so we can reuse 
 */
void stackClearInt();


/** DEBUGGING FUNCTION PRINTS SOME INFO ABOUT THE STACK **/
void printDebugInt();

#endif
