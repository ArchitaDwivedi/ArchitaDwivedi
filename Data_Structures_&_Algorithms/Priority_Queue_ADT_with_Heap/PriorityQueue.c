#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Heap.c"
#include"PriorityQueue.h"


//------------------------------------------------------------------------
/* TODO: implement get_max
returns largest element in heap/highest priority
*/
// Description:- Returns the value of the 0th index i.e the
// largest value of the Heap.
int get_max(Heap* h){
  return h->heap_arr[0];
}
//------------------------------------------------------------------------







//------------------------------------------------------------------------
/* TODO: implement extract_max
extracts and returns max element in heap
note that heap property must be maintained after extraction
also check for valid input (cannot extract from empty heap)
*/
// Description:- This function is used to extract the largest element
// of the heap, restore the max heap structure of the heap and then
// return the largest element of the heap.
// For this, we first do the check to see if there are elements in the
// heap. If there are not then we exit. Else, we first get the max
// element from the heap. Then we take the smallest element of the 
// heap and store it to the 0th position. After this, we decreament 
// the size of the heap as we extracted an element. Finally, we call
// heapify on the 0th index to restore the max heap structure of the
// heap. Finally return the max element.

int extract_max(Heap* h){
  if (h->size < 0){
    printf("Error! Heap underflow!");
  }

  int max = h->heap_arr[0];
  h->heap_arr[0] = h->heap_arr[h->size - 1];
  h->size = h->size - 1;
  heapify(h, 0);
  return max;
}
//------------------------------------------------------------------------







//------------------------------------------------------------------------
/* TODO: implement increase_priority
This function increases priority/value of element at index i to 'new_value'
*/
// Description:- Given a certain priority/key, this function sets the
// value to its correct position in the heap depending on its priority/key.
// For this, we first check if the key/priority is smaller than the value
// at the index. Then there will be no position resetting. Otherwise, we 
// will first set the value at the index to be the priority/key provided.
// Now that it has a new value. We must set it to its relevant position.
// So we loop until the index is positive and the parent of index i is 
// less than the value of i itself. In this loop, we call swap on the
// heap, the parent and i. Finally, we set i's index to be that of its 
// parent's and then continue the loop until the max heap structure is 
// restored i.e the value with new priority/key finds its position on
// the heap.

void increase_priority(Heap* h, int i, int new_value){
  if (new_value < h->heap_arr[i] ){
    printf("Error! New key smaller than current key");
    return;
  }
  h->heap_arr[i] = new_value;
  while ( i > 0 && h->heap_arr[parent(i)] < h->heap_arr[i]){
    swap(h->heap_arr,i,parent(i));
    i = parent(i);
  }
}
//------------------------------------------------------------------------






//------------------------------------------------------------------------
/* TODO: implement insert functionality
This function inserts priority 'value' into heap
You will need to have implemented the increase_priority and use it here
*/
// Description:- This function is used to make space and insert a key
// into the heap and then we use the increase_priority function to restore 
// max heap structure.
// For this, we first check if the size of the heap is not zero and that
// the number of elements is not exceeding the heap's capacity. If it isnt
// then we first increament the size i.e make space. Then we add the key
// to the last position with some arbitrary value and then we finally
// call the increase_priority function on the heap to restore max heap
// structrue.

void insert(Heap* h, int value){
  if (h->size < 0 || h->size > h->length){
   exit(1);
  }
  h->size = h->size + 1;
  h->heap_arr[h->size - 1] = -2147483648;
  increase_priority(h, h->size - 1, value);
}
//------------------------------------------------------------------------