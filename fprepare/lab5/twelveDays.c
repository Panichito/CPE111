/*
 *  Simple demo to show how the "Twelve Days of Christmas" song can
 *  be generated using a recursive algorithm.
 *  
 *    Created by Sally Goldin, 4 January 2012
 *    Minor updates 22 January 2013
 */

#include <stdio.h>

/* static array of gifts for each day - this is a "table"
 * in the sense introduced in Lecture 2 
 */
char * gifts[] = {"NOT USED",
                  "A partridge in a pear tree",
                  "Two turtle doves",
		  "Three French hens",
		  "Four calling birds",
		  "Five golden rings",
		  "Six geese a-laying",
		  "Seven swans a-swimming",
		  "Eight maids a-milking",
		  "Nine ladies dancing",
		  "Ten lords a-leaping",
		  "Eleven pipers piping",
		  "Twelve drummers drumming"};

char * ordinals[] = {"NOT USED",
		     "First", "Second", "Third", "Fourth", "Fifth",
		     "Sixth", "Seventh", "Eighth", "Ninth", "Tenth",
		     "Eleventh", "Twelfth"};

/* Print the gifts for a particular day 
 * This is a recursive function. Day == 1 is the base case.
 * Arguments 
 *    day    Day whose gifts we want to print. Includes
 *             all previous days' gifts
 */
void printGifts(int day)
{ 
    printf("   %s\n",gifts[day]);
    if (day == 2)
        printf("    And\n");
    if (day > 1)
	printGifts(day-1);
}

/* main asks what the user wants to do */
int main(int argc, char* argv[])
{
    int whichDay = 0;
    char buffer[32];    
    while (whichDay >=0)
       {
       printf("\nPrint gifts for what day? (-1 to exit, 0 for all twelve) ");
       fgets(buffer,sizeof(buffer),stdin);
       sscanf(buffer,"%d",&whichDay);
       if ((whichDay > 0) && (whichDay < 13))
           {
	   printf("On the %s Day of Christmas, my true love gave to me\n",
                      ordinals[whichDay]);
	   printGifts(whichDay);
           }
       else if (whichDay == 0)
           {
	   int i = 0;
           for (i = 1; i < 13; i++)
	      {
	      printf("On the %s Day of Christmas, my true love gave to me\n",
		     ordinals[i] );
	      printGifts(i);
              printf("\n{Type Enter to continue}\n");
	      fgets(buffer,sizeof(buffer),stdin);
              }
           }
       else if (whichDay > 12) /* error */
           {
	   printf("Bad input! Please enter a value between -1 and 12\n");
           }
       }
}
