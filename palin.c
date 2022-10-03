/***********************************
* Filename: palin.c
************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

void myStrInput ( char s[ ] );
int palindrome( char s[ ] );

main()
{
   char strg[ MAX_SIZE ];
   myStrInput( strg );
   printf( "%s\n", palindrome( strg ) ? "YES" : "NO" );
}


/******************************************************************/
/************* DO NOT MODIFY ANYTHING ABOVE THIS LINE *************/
/******************************************************************/

/***********************************
* EECS2031 - Lab Test 1
* Filename: palin.c
* Author: Ukhin, Alexander
* Email: alexanderukhin@gmail.com
* Login ID: sashauk
************************************/

/******************************************************************/
/*********************  YOUR CODE STARTS HERE *********************/
/******************************************************************/

/************* YOU MAY ADD YOUR OWN FUNCTION(S) HERE **************/


/* Function myStrInput
   Input: an array of char.
   Output: the same array that stores the user's input string.
   Note: The length of each input string is less than the array size.
   So no error checking for the string length is required.
   Do not modify the function definition.
 */

void myStrInput ( char s[ ] )
{
   /* Add your code here. */
   /* You may define additional variables or call functions that you write. */
   /* Do not use any C library functions, except for input. */
   scanf("%[^\n]%*c", s);
}

/* Function palindrome
   Input: a string in array s.
   Output: returns 1 if the string is a palindrome;
                returns 0 otherwise
   An empty string is considered a palindrome.
   Do not modify the function definition.
 */

int palindrome( char s[ ] )
{

   /* Add your code here. */
   /* You may define additional variables, or call functions that you write. */
   /* Do not use any C library functions. */
   int stringLength;
   int counter = 0;
   while(s[counter] != '\0'){
    ++counter;
   }
   counter = counter - 1;
   int counterTotal = counter;
   counter = counter/2;

   int result = 0;
    int i = 0;
   while(i != counter){
    if(s[i] == s[counterTotal - i] || s[i] == (s[counterTotal - i]+32) || ((s[i]+32) == s[counterTotal - i])){
        result = 1;
        ++i;
    }
    else{
        return (0);
    }
   }

   return (result);     /* replace this line with your own code */


}

/*************************** END OF FILE ****************************/

