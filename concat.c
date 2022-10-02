/***********************************
* Filename: concat.c
************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 500

void myStrInput ( char s[ ] );
void concatenate( char s1[ ], char s2[ ] );

main()
{
   char strg1[ MAX_SIZE ], strg2[ MAX_SIZE ];
   myStrInput( strg1 );
   myStrInput( strg2 );
   concatenate( strg1, strg2 );
   printf( "%s\n", strg1 );
}


/******************************************************************/
/************* DO NOT MODIFY ANYTHING ABOVE THIS LINE *************/
/******************************************************************/

/***********************************
* EECS2031 - Lab Test 1
* Filename: concat.c
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
   scanf("%[^\n]%*c", s);
   /* Add your code here. */
   /* You may define additional variables,  or call functions that you write. */
   /* Do not use any C library functions, except for input. */
}



/* Function concatenate
   Input: two arrays of char s1 and s2.
   Output: string 1 followed by string 2 and stored in array s1.
   Assume that array s1 has enough space for the concatenated string.
   Do not modify the function definition.
 */

void concatenate( char s1[ ], char s2[ ] )
{
   /* Add your code here. */
   /* You may define additional variables,  or call functions that you write. */
   /* Do not use any C library functions. */
   int counter1 = 0;
   int counter2 = 0;
   while(s1[counter1] != '\0'){
    ++counter1;
   }
   while(s2[counter2] != '\0'){
    ++counter2;
   }
   //--counter1; //gets total length of string including empty character
   //--counter2;

   int totalFinalStringSize = counter1 + counter2;

   int tempCounter = 0; //counter for the second string to keep location

   int i = counter1;

   while(i != totalFinalStringSize){
    s1[i] = s2[tempCounter];
    ++i;
    ++tempCounter;
   }
}

/************************** END OF FILE ****************************/

