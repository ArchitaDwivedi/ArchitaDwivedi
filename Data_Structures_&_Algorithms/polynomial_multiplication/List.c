/*********************************************************************************
* Archita Dwivedi, adwivedi
* List.c
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "List.h"


//-----------------------------------------
// private ListObj type
typedef struct NodeObj{
  int data;
  struct NodeObj* next;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
  Node cursor;
  int length;

} ListObj;
//-----------------------------------------




//-----------------------------------------
// newList():-
// Creates and returns a new empty List.
List newList(void){
  List L = NULL;
  L = malloc(sizeof(ListObj *));
  
  if(L == NULL){
    printf("List newList: Space cannot be malloced!\n");
  }

  else{
    L->cursor = NULL;
    L->length = 0;
  }
  return (L);
}
//------------------------------------



// Private
//------------------------------------
// newNode():-
// Creates and returns a new node with data.
Node newNode(int data){
  Node N;
  N = malloc(sizeof(NodeObj *));
  
  if(N == NULL){
    printf("List newNode: Could create Node. Node is NULL.\n");
  }
  else{
    (N)->data = data;
    (N)->next = NULL;
  }
  return(N);
}
//------------------------------------



// Private
//------------------------------------
// freeNode():-
// Frees a Node and sets pointer to NULL.
void freeNode(Node* pN){
  if( pN!=NULL && *pN!=NULL ){
    free(*pN);
    *pN = NULL;
  }
}
//------------------------------------





//------------------------------------
// freeList():-
// Frees a List and sets pointer to NULL.
void freeList(List* pL){
  if( *pL==NULL && pL==NULL )
  {
    printf("Error!");
    return;
  }
  else{
    Node tmp = ((*pL)->cursor);
    Node n;
   while (tmp != NULL)
    {
       n = tmp->next;
       freeNode(&tmp);
       tmp = n;
    }

  freeNode(&tmp);
  free(*pL);
  *pL = NULL;
  }
return;
}
//-----------------------------------------------------




//-----------------------------------------------------
// length():-
// Return the length of the List i.e the number of
// elements in the list.
int length(List L){
  if( L == NULL )
  {
    printf("List lenth: List is Null!\n");
    return 0;
  }

  return L->length;
}
//-----------------------------------------------------



//-----------------------------------------------------
// max():-
// Return the index of largrest element of the List.
int max(List L){
    Node temp = L->cursor;
    int max_value = L->cursor->data;
    int max_index = 0;
    temp = temp->next;
    int length = L->length;
    int counter = 1;

    for(counter = 1; counter <= length && temp!=NULL; counter++)
    {

        int td = temp->data;
        if(temp->data > max_value)
        {
            max_value = temp->data;
            max_index = counter;
        }
        temp = temp->next;
    }
    return max_index;
}
//-----------------------------------------------------



//-----------------------------------------------------
// max():-
// Return the index of first occurence of i in the list
// and returns -1 if i is not found in the list
int find( List L, int i ){
  int index = 0;
	Node temp = L->cursor;

  while (temp != NULL){
    if (temp->data == i){
      return index;
    }
    index += 1;
    temp=temp->next;
  }
  return -1;
}
//------------------------------------------



//------------------------------------------
// delElement():-
// deletes the ith element of the list and return the 
// data of it. Returns -1 if i is not found in the list.
int delElement( List L, int i ){
  int data;

  if( length(L) < 1 ){
    printf("List delElement: length of List is 0 or less\n");
    return 0;
  }
  if(L == NULL){
    printf("List delElement: List is Null \n");
    return 0;
  }

  
  if ( i > length(L) - 1){
    printf("List delElement: the index to delete is larger in number than the list elements! \n");
    return 0;
  }


   Node temp = L->cursor;
  
    if (i == 0){
      L->cursor = temp->next;
      data = temp->data;
      free(temp);
      L->length--;
      return data;
    }
  
    if (temp != NULL){
    for (int counter = 0; counter < i-1; counter++)
      temp = temp->next;
    }     
  
    if (temp == NULL){ 
      return 0;
    }

    if (temp->next == NULL){      
      return 0;
    }
  
    Node next = temp->next->next;
  
    data = temp->next->data;

    free(temp->next);
    L->length--;
    temp->next = next;

    return data;
}
//-----------------------------------------------------



//-----------------------------------------------------
// appendList():-
// append i to the end of the list.
void appendList( List L, int i ){

  if( L == NULL ){
    printf("List appendList: List is Null\n");
    return;
  }

  // create a temporary node
  Node new_node = newNode(i);
  Node temp_cursor = L->cursor;

  // if length of list if 0 then we simply add to the list
  if( length(L) == 0 ){
    L->cursor = new_node;
    L->length++;
  }

  // else if it isnt 0 add to end of list
  else{
    while(1){
      if (temp_cursor->next == NULL){
        temp_cursor->next = new_node;
        new_node->next = NULL;
        break;
      }
      temp_cursor = temp_cursor->next;
    }
    L->length++;
  }


return;
}
//-----------------------------------------------------



//-----------------------------------------------------
// printList():-
// print all data of the list with specified pattern.
void printList(List L){

  if(L == NULL){
    printf("List printList: List is NULL!\n");
    return;
  }

  Node N = (L->cursor);

  while (N != NULL) {
    printf("%d", N->data);
    printf(", ");
    N = N->next;
    }
    printf("\n");
}
//-----------------------------------------------------


