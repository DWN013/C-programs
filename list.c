/***********************************
* EECS 2031N - Lab Test 2
* Filename: list.c
* Author: Ukhin, Alexander
* Email: alexanderukhin@gmail.com
* EECS login ID: sashauk
************************************/


#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*  Defined in "list.h"
typedef struct list {
   int data;
   struct list *next;
} List;
*/

List *head;


/* Display an error message. */

void prtError( char *errMsg )
{
   printf( "%s \n", errMsg );
}


/* Initialize the list. */
/* Create a dummy node to simplify insertion and deletion. */
/* After the list is created, pointers head and tail both point to the dummy node. */
/* Return NULL if a node cannot be created. */
/* Otherwise, return the pointer to the dummy node. */

List *init()
{
   head = ( List * ) malloc( sizeof( List ) );
   if ( head == NULL ) {
      prtError( "Insufficient memory!" );
      return( NULL );
   }
   head->data = -1;
   head->next = NULL;
   return ( head );
}


/* Print the content of the list (including the dummy node). */

void prtList()
{
   List *p;
   for ( p = head; p != NULL; p = p->next )
        printf( "%6d", p->data );
   printf( "\n" );
}



/************* DO NOT MODIFY ANYTHING ABOVE THIS LINE, *************/
/************* EXCEPT THE HEADER CONTAINING YOUR INFO **************/


/* Insert a new data element d into the list. */
/* Insert at the front of the list. */
/* The newly inserted element will become the new head of the list. */
/* Return NULL if a new node cannot be created. */
/* Otherwise, return the pointer to the newly created node. */

List *insertFront( int d )
{
   List *l;
   l = (List*)malloc(sizeof(List));

   if(l == NULL){
     return NULL;
   }

   l->data = d;
   l->next = head;
   head = l;

   return l;

}

/*************************** END OF FILE ***************************/
