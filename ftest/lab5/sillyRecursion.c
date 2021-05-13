/* sillyRecursion. c
 *
 * This program shows how you could calculate the length of a string
 * using a recursive function.
 *
 * This is NOT a good way to solve this problem, but it shows
 * how recursion works.
 *
 * Created by Sally Goldin, Jan 2014, for CPE 113
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int stringLength(char* item)
{
  if (item[0] == '\0')
    return 0;
  else 
    return (1 + stringLength(&item[1])); 
}


int main()
{
  int length = 0;
  char input[64];
  while (1)
    {
    memset(input,0,sizeof(input)); 
    printf("Enter string to count (CR to end): ");
    fgets(input,sizeof(input),stdin);
    if (input[strlen(input)-1] == '\n')
      input[strlen(input)-1] = '\0';
    length = stringLength(input);
    if (length == 0)
      break;
    else 
      printf("'%s' is %d characters long\n", input,length);
    } 
}
