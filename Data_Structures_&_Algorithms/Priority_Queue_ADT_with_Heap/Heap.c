#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"Heap.h"



//------------------------------------------------------------------------
// TODO: Implement funcs for fetching parent and left/right child,
// for a heap starting with index 0
int parent(int i)
{
  return (i-1)/2;
}
//________________________________________________________________________




//------------------------------------------------------------------------
// Description:- You can access every odd index with this. Hence giving
// us the left child for a heap starting with index 0.
int left(int i){
  return ((2 * i) + 1);
}
//________________________________________________________________________




//------------------------------------------------------------------------
// Description:- You can access every even index with this. Hence giving
// us the right child for a heap starting with index 0.
int right(int i){
  return ((2 * i) + 2);
}
//________________________________________________________________________




//------------------------------------------------------------------------
// TODO: Helper function for swapping A[i] and A[j] elements in an array
//---------------
// Description:- We take in two indexes and an array.
// We save one of the values at one of the indexes and then save the other
// value at it's place, then we store the saved value into another space.
void swap(int* A, int i, int j){
  int tempo = A[i];
  A[i] = A[j];
  A[j] = tempo;
}
//________________________________________________________________________




//------------------------------------------------------------------------
/* TODO: declare the Heap struct as in the header file
This Heap struc has the following fields:
- len: length of the array used for implementing the heap
- size: number of elements in the backbone array that are 'heapified' or ordered as heap
- array: (pointer to) array used for implementing the heap
*/
typedef struct Heap
{
  int length;
  int size;
  int *heap_arr;
}Heap;
//________________________________________________________________________




//------------------------------------------------------------------------
/* TODO: implement initializeHeap function which instantiates a heap using malloc.
This function takes in the following arguments:
- length of the array used for implementation
- size of the heap; i.e. number of elements in array that we want to be ordered as heap
- pointer to array used for implementing the heap
It returns a pointer to the instantiated heap
*/

Heap* initializeHeap(int len, int h_size, int* arr){

  Heap *h = malloc(sizeof(Heap));

  h->length = len;
  h->size = h_size;
  h->heap_arr = arr;
  
  return h;
}
//________________________________________________________________________




//------------------------------------------------------------------------
/*  TODO: implement heap destructor that frees memory allocated to heap */

void destructHeap(Heap* h){
  if (h == NULL){
    printf("Error: Cannot Destruct Heap. It is already NULL!");
  }

  free(h);
  h = NULL;
  return;
}
//________________________________________________________________________





//------------------------------------------------------------------------
/* TODO: implement 'heapify' function, given a heap pointer and an index i
This function maintain (max) Heap property given an index i for heap h
*/
// Description:- We start by default setting index i to be contain the largest
// value. Then we get the left and the right child of i. Now we check if the
// value of the left child is greater than i, if it is then we replace the
// value of the left child to be the largest. Next, we take the now largest
// value and compare it with the right. If the value of the right child is 
// bigger than the current largest value, we replace it. Then we check if
// the largest value is either the left or the right child, then we must
// call swap and then call heapify again with the index of the largest 
// element.

void heapify(Heap* h, int i){
    int largest = i; 
    int left = (2 * i) + 1; 
    int right = (2 * i) + 2; 
   
    if (left < h->size && h->heap_arr[left] > h->heap_arr[largest]){ 
        largest = left; 
    }
   
    if (right < h->size && h->heap_arr[right] > h->heap_arr[largest]) {
        largest = right; 
    }
 
    if (largest != i) { 
        swap(h->heap_arr,i, largest); 
        heapify(h, largest); 
    }
    return;
}
//________________________________________________________________________





//------------------------------------------------------------------------
/* TODO: implement array_to_heap function
You may use initializeHeap function for implementing this function
*/
// Description:- For this function, we basically start from the last
// parent of the heap and go all the way to the top of the heap and
// calling heapify to maintain the max heap structure

Heap* array_to_Heap(int* A, int len, int size){
  Heap *h = initializeHeap(len, size, A);
  
	for (int i = ((size - 1) / 2) ; i >= 0; i--) { 
		heapify(h, i); 
	} 
	
  return h;
}
//________________________________________________________________________





//------------------------------------------------------------------------
/* TODO: implement utility functions:
- size(): returns the size field of a heap
- len(): returns the length field of a heap
*/

// returns the number of elements in the heap
int size(Heap* h){
  return h->size;
}

// returns the total length of the heap i.e its capacity
int len(Heap* h){
  return h->length;
}
//________________________________________________________________________


