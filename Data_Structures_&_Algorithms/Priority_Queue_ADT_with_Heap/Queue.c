#include <stdio.h>
#include <stdlib.h>


//------------------------------------------------
// Description:- Queue ADT where length is the
// total length of the Queue. Count is the number
// of elements in the Queue. The head points to
// the frontmost element in the queue and the 
// the tail points to the backmost element in the
// Queue. This Queue has been implemented using
// an array.

typedef struct Queue
{
  int length;
  int count;
  int head;
  int tail;
  int *arr;
}Queue;
//------------------------------------------------






//------------------------------------------------
// Description:- This function is the Constructor
// of the queue. We malloc size for the Queue.
// Then we set it length, and arr to the parameters.
// Finally we set the count,tail and head to zero
// and return the queue.

Queue* initializeQueue(int n, int* arr){
  Queue* queue = malloc(sizeof(Queue));

    queue->length = n;
    queue->tail = queue->count = 0;
    queue->head = 0;
    queue->arr = arr;
    return queue;
}
//------------------------------------------------






//------------------------------------------------
// Description:- This function is the Destructor
// of the queue. We first check if q exists and
// has some elements in it. Finally we set its
// count and length to zero and free the queue.

void destructQueue(Queue *q){
  if (!q || q->count == 0 || q->length == 0 ){
      printf("Error: Empty Queue!\n");
      return;
  }
  q->count = 0;
  q->length = 0;
  free(q);
  return;
}
//------------------------------------------------






//------------------------------------------------
// Description:- This function is used to populate
// the Queue. We first check if the array is full.
// If it is then we know there is an Overflow!
// else we set the value to the tail index. We make
// sure that the tail index is within the length
// of the Queue array and for that reason we use
// mod (%). Finally after each append we increament
// the count.

void enqueue(Queue* q, int x){
  if((q->count >= q->length) || q->tail > q->length )
	{
		printf("Queue Overflow \n");
		exit(1);
	}

  q->arr[q->tail] = x ;
  q->tail = (q->tail + 1) % q->length;
  q->count++;
  return;
}
//------------------------------------------------






//------------------------------------------------
// Description:- This function is used to extract
// values out of the Queue. We first check if 
// there are elements in the Queue to dequeue.
// If there aren't, then we know there is an
// Underflow! Else, get the item at the head index
// set the value at the head to be some arbitrary
// number (-2) and then we increament the head
// and decreament the count. We make sure that the 
// head index is within the length of the Queue 
// array and for that reason we use mod (%).

int dequeue(Queue* q)
{
  int item;
  if (q->count <= 0 || q->head >= q->length){
  	printf("Undeflow!");
    return 0;
  }


  item = q->arr[q->head];
  q->arr[q->head] = -2;
  q->head = (q->head + 1) % q->length;
  q->count = q->count - 1;
  return item;
}
//------------------------------------------------





//------------------------------------------------
// Description:- This function is simply used to print
// the Queue. We first check if the array is not NULL
// and that there are elements in it. If there arent
// we exit with an error message. Else, we first
// save the heads position and acquire the element at 
// the head. We loop from 0 upto the number of elements 
// in the array.We print the value at the head and 
// then increament the head by 1. Finally, after 
// printing, we reset the head back to its original 
// position.

void printQueue(Queue* q){

  int i = 0;
  if (!q || q->length == 0 || q->count == 0)
  {
    printf("Error: Empty Queue!\n");
    return;
  }
  int first = q->head;
  while (i < q->count){
    printf("Queue: %d \n", q->arr[q->head]); 
    q->head = q->head + 1;
    i++;
  }
  q->head = first;

}
//------------------------------------------------





//------------------------------------------------
// Description:- If the array is of size 0, return
// -1. Else return the number of elements in the
// array.

int count(Queue* q){
  if (q->length == 0){
    return -1;
  }
  return q->count;
}
//------------------------------------------------