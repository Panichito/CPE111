//
// Created by ASUS on 3/13/2021.
//

#ifndef HELPMENU_H
#define HELPMENU_H


typedef struct _helpItem
{
	const char* commandName;
	const char* commandArgs;
	const char* commandDef;
}HELP_T;

/* printallhelp function
 * Printing all command including names, arguments, drescription
 * printing list of 5 commands at a time. 
 * Arguements
 *      no argument.
 *
 * recieving Y as ture to proceed printing commands
 * recieving N as false to exit function
 */
void printallhelp();

/* printallhelp_color function
 * Printing all color command including names, arguments, drescription
 * 
 * Arguements
 *      no argument.
 */
void printallhelp_color(int count);

/* printonehelp function
 * Printing only selected command
 * 
 * Arguements
 *      helpIndex - selected command position in the array.
 *      colorindex - indicate which is general command or color command
 *                   0 - general command
 *                   1 - color command
 */
void printonehelp(int helpIndex, int colorindex);

/* askforhelp function
 * recieve mode from main as integer then send to print
 * 
 * Arguements
 *      commandIndex - MODE from commandFunctions
 */
void askforhelp(int commandIndex);

/* askforhelp_color function
 * recieve MODE as integer then send to print
 * 
 * Arguements
 *      commandIndex_color - MODE from colorFunctions
 */
void askforhelp_color(int commandIndex_color);

#endif
