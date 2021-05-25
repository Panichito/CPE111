/** 
 *  linkedListUtilMod.h
 *
 *  Header file for utility linked list module
 *  Used to create and manage lists that are part of other data
 *    structures.
 *
 *  Each call to newList() creates a new list and returns the pointer
 *  to that list. So by calling newList() multiple times, the calling
 *  program can create and manage many linked lists.
 *
 *  The list can hold any kind of data, via a void* pointer. It assumes
 *  that the calling program will manage the memory for that data,
 *  so it does not free it.
 *
 *  Created by Sally Goldin, 12 February 2013 for CPE113
 *
 *  Modified with permission by Pada Cherdchoothai on 10 March 2021
 *  Made the following changes:
 *      add new function listItemSwap
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/* opaque pointer to a list */
typedef void* LIST_HANDLE;

/* Creates a new list, empty list.
 * Returns a pointer to the created list, or NULL if a memory allocation
 * error occurs. All other public functions require the list pointer
 * as their first argument.
 */
LIST_HANDLE newList();


/* Frees all memory associated with this list, that is
 * the list items and the list structure itself.
 * Does not free the data.
 * Arguments
 *   linkedList  -   list to free. Once this function is called
 *                   this pointer is no longer valid
 */
void listDestroy(LIST_HANDLE list);


/* Find out how many items currently are stored in the passed list
 * Arguments
 *   linkedList  -   list to whose size we want to know
 * Returns the number of elements (could be zero)
 * a -1 if the list has not been created/initialized.  
 */
int listSize(LIST_HANDLE list);


/* Add a new element to the end of a list
 * Arguments:
 *   linkedList  -   list we want to add to
 *   data        -   pointer to the information to store in the list
 * Returns the 1 if successful or 0 if the list is not initialized.
 * Returns -1 if a memory allocation error occurs.
 */
int listInsertEnd(LIST_HANDLE list, void * data);

/* Removes the element at a specified position and
 * returns its data. Frees the list item but does not
 * free the data.
 * Arguments:
 *   linkedList  -   list we want to remove from
 *   position    -   position in the list to remove, where 0 is the head
 *                   of the list. If 'position' is larger than the number
 *                   of elements in the list, we simply remove the last element
 *                   rather than returning an error.
 * Returns the data for the item removed. 
 * Returns NULL if the list is empty or the list pointer is NULL
 */
void* listRemove(LIST_HANDLE list, int position);


/* Resets the "current" list pointer to the beginning
 * of the list.
 * Arguments:
 *   linkedList  -   list we want to remove from
 * Returns 1 if successful, 0 if the list is empty,
 * -1 if the list has not been initialized.  
 */
int listReset(LIST_HANDLE list);

/* Returns the data stored at the "current" list 
 * position, then moves the current position to the 
 * next position in the list.
 * Arguments:
 *   linkedList  -   list we want to remove from
 * Returns data if successful, null if we are
 * already at the end of the list or if the
 * list has not been initialized.  
 */
void* listGetNext(LIST_HANDLE list);

/* Find out if the current list position is past the
 * end. 
 * Arguments:
 *   linkedList  -   list we want to remove from
 * Return 1 if the position is past the end of the list,
 * Return 0 if the position is not past the end.
 * Return -1 if the list has not been initialized.
 */
int listAtEnd(LIST_HANDLE list);

/* Swap two elements at a specified position and
* returns its data of the second data to indicate success.
* Arguments:
*   linkedList  -   list we want to remove from
*   position1        -   position of the first item must be more than 0
 *                  and larger than the 2nd item
 *  position2        -   position of the 2nd item
* Returns the data of the 2nd item.
* Returns NULL if the list is empty or the list pointer is NULL
*/
void *listItemSwap(LIST_HANDLE list, int pos1, int pos2);

/* Move data to another position in the list
* returns its data of the second data to indicate success.
* Arguments:
*   linkedList  -   list we want to move item
*   position1        -   position of the first item
 *  position2        -   position of the 2nd item
* Returns the data of the 2nd item.
* Returns NULL if the list is empty or the list pointer is NULL
*/
void *listItemMove(LIST_HANDLE list, int position1, int position2);

/* Change the pointer to data of a list item
*
* Arguments:
*   linkedList  -   list we want to swap data from
*   oldData - pointer to the old data
*   newData - pointer to the new data
* Returns the data of the old item.
* Returns NULL if the list is empty or the list pointer is NULL
*/
void *listSwapData(LIST_HANDLE list, void *oldData, void *newData);

#endif