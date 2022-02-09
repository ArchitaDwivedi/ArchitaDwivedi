#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"

// -----------------------------
// Returns ptr to node with matching key, else returns NULL
// -----------------------------
node_t *findList( node_t *head, char *key )
{
  node_t *ptr;

  ptr = head;
  while( ptr != NULL )
  {
    if (strncmp(ptr->key,key,5) == 0)
      break;
    else    ptr = ptr->next;
  }
  return( ptr );
}

// -----------------------------
// Returns ptr to node with matching key, else returns NULL
// -----------------------------
void insertList( node_t **head, node_t *new )
{
	// insert new node as head of list
	if (*head == NULL)
	  {	
      *head = new;
		  (*head)->next = NULL;
		  (*head)->prev = NULL;
	  }
	else{	
    new->next  = *head;
		(*head)->prev = new;
		new->prev  = NULL;
		*head      = new;
	  }
 return;
}

// -----------------------------
// Deletes node pointed to by del from the list.
// You can assume that del points to a node in the list.
// -----------------------------
// Description:- This function takes in a head i.e the 
// start of a list and node we want to delete. 
// We first check if the head is null. If it is, we
// return. Otherwise, we check if the head is the node
// we want to delete. If it is, we set the head node to 
// point the del node's next. Otherwise if it some node in
// the middle, we simply unlink the nodes. Finally we free
// the node and return.
// -----------------------------
void deleteList( node_t **head, node_t *del )
{

  if (*head == NULL)
  {	
      return;
	  }

  else if ( *head == del ){
    *head = del->next;
  }

  else{
    del->prev->next = del->next;
    if (del)
    	del->next->prev = del->prev;
  }
  free(del);
  return;

}
  


// -----------------------------
// Prints key field of each node in the list starting at head.
// -----------------------------
// Description:- This function takes in a 
// head i.e the start of the list. We first 
// check if the head is null. If it is we exit.
// Otherwise, we loop until the head becomes null.
// and print the key in a loop and return.
// -----------------------------
void printList( node_t *head )
{
    if(head == NULL){
    printf("Error: Null Error!\n");
    exit(EXIT_FAILURE);
  }
  node_t *N = NULL;
  N = head;
  while( N != NULL){

    printf("%s ",N->key);
    N = N->next;
  }
  printf("\n");
 return;  
}

