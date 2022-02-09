#include "HashTable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef struct {
  char    key[5];  
  void*   value;
  }   element; 


typedef struct {
  int   slots; 
  int   size;  
  node_t    *hash_table; 
  }   dictionary;







// -------------------------------
// create( *D, n ) -- creates a dictionary with n slots
// Initializes slots to n, and size to 0.
// -------------------------------
// -------------------------------
// Description:- This function takes in a 
// dictionary and the number of slots in 
// the dictionary's hashtable. 
// We initialize the dictionary's members' 
// values, then in a loop we malloc space
// in the hashtable i.e dummy nodes and 
// also set each slot's members' values.
// -------------------------------
void create(dictionary *D, int n)
{   
    D->slots = n;
    D->size = 0;

    D->hash_table = (node_t *)calloc(n, sizeof(node_t));    

    for ( int i = 0 ; i < n ; i++ ){

      memcpy(D->hash_table[i].key,"",5);
      D->hash_table[i].value = NULL;
      D->hash_table[i].next = NULL;
      D->hash_table[i].prev = NULL;

    }    
  return;
}






// -------------------------------
// TODO: implement insert
// insert( *D, *e ) -- inserts element e->key:e->value into the dictionary.
// First, make sure that e->key does not exist in *D yet.
// If it does, return an error code of -1.
// Otherwise, update the size of *D, and return 0.
// -------------------------------
// -------------------------------
// Description:- This function takes in a
// dictionary and an element type to insert
// in that dictionary.
// We first find the relevant index in the 
// hashtable where we want to insert our element
// node. In a loop we iterate to the end of the 
// of that slot and through the nodes if present,
// to check if the element key is alreay present
// in the hashtable. If it is we return -1. Else,
// we first build a node i.e malloc space. Then
// we copy the key and the value to this newly
// created node. Depending on the index we find
// for that particular key, we get the slot,
// loop to the end of that slot to make sure we 
// append to the end of the linked list, if other
// nddes are present. We append the newly created
// node to the end and then we update the counters
// of the Dictionary respectively and return.
// -------------------------------
int insert(dictionary* D, element* e)
{

    int index = hash(e->key,D->slots);
    node_t *start = &(D->hash_table[index]);


    while( start != NULL ){
      if (strncmp(start->key,e->key,5) == 0){
        return -1;
      }
      start = start->next;
    }


    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->prev = new_node->next = NULL;
    memcpy(new_node->key, e->key,5);
    new_node->value = e->value;


    int index_2 = hash(e->key,D->slots);
    node_t *index_node = &(D->hash_table[index_2]);

    while (index_node->next != NULL ){
      index_node = index_node->next;
    }
    
    index_node->next = new_node;
    new_node->prev = index_node;
    D->size++;

    return 0;
}







// -------------------------------
// TODO: implement delete
// delete( *D, *key ) -- deletes element with key (*key) from the dictionary.
// If *key does not exist in *D, return an error code of -1.
// Update the size of *D, and return 0.
// -------------------------------
// Description:- This function takes in the
// a dictionary and key.
// We first the slot in which the element(node)
// is in. Then we loop through it check if the 
// node exists. If it doesnt we return an error.
// Otherwise, if it is the first element, then
// we set the prev and next accordingly, 
// update the counters and free the node.
// If it is not the last element (node), then
// we set the prev and next accordingly, 
// update counters and free the node.
// Otherwise, if it is some node in between,
// then we we set the prev and next accordingly, 
// update the counters and then free the node.
// otherwise the loop will end if the node 
// reaches NULL and returns -1.
// -------------------------------
int delete(dictionary* D, char* key)
{

    int index = hash(key,D->slots); 
    node_t *start = &(D->hash_table[index]);  


    while( start != NULL ){
      if (strncmp(start->key,key,5) == 0){

        if (start->prev == NULL){
          start->next->prev = NULL;
          start->next->prev = start->prev; 
          D->size--;
          free(start);
          return 0;
        }

        else if (start->next == NULL){
          start->prev->next = NULL;
          D->size--;
          free(start);
          return 0;
        }

        else{
          start->prev->next = start->next;
          start->next->prev = start->prev;
          D->size--;
          free(start);
          return 0;         
        }
      }
      start = start->next;
    }

    return -1;
}






// -------------------------------
// TODO: implement find
// find( D, k ) -- returns pointer to node whose key is *k from dictionary *D.
// If *k is not found in *D, then return NULL.
// -------------------------------
// -------------------------------
// Description:- This function takes in the
// a dictionary and key.
//  We first find the index in which the node
// is in. Then we start from the head of that
// slot and loop upto the end. In between, if 
// we find the node with the same key as we 
// want, we return the pointer, otherwise we 
// return NULL.
// -------------------------------
node_t* find(dictionary* D, char* k)
{


    int index = hash(k,D->slots);
    node_t *start = &(D->hash_table[index]);


    while( start != NULL ){

      if (strncmp(start->key,k,5) == 0){
        return start;
      }
      start = start->next;
    }

    return NULL;
}





// -------------------------------------------------------------------
// TODO: implement print
// print( dictionary *D ) -- prints the dictionary.
// Specifically, it looks at the non-empty slots of the hash table,
// and prints the key field of each node in the list.
// -------------------------------------------------------------------
// Description:- In this function, we 
// take in a dictionary.
// We first start with a pointer to the first
// slot's first node (i.e head). We create a 
// loop from the first slot upto the total number
// of slots. Inside the loop, we set the node pointer.
// we do a NULL check. If not, we call printList() with
// the first node upto the last, keep printing each list.
// Finally we return.
// -------------------------------
void print(dictionary* D)
{
  int i = 0;
  node_t *start = &(D->hash_table[i]);

  while ( i < D->slots ){
    start = &(D->hash_table[i]);
    
     if (start->next != NULL)
      {
        printList(start->next);
      }
    
    i++;
  }
 return;
}


