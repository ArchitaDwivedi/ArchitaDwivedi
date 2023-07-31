#include <stdio.h>
#include <sys/syscall.h>      /* Definition of SYS_* constants */
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h> 
#include "queue.h"




// Typedef for queue
typedef struct queue{
    void** data_array;
    int elements_in_array;
    int head;
    int tail;
    int capacity;
    pthread_mutex_t mutex;
    pthread_cond_t condQueue1;
    pthread_cond_t condQueue2;
}queue_t; 



// Create a new queue
queue_t *queue_new(int size){
    
    // malloc space
    struct queue* q;
    q = (queue_t *)malloc(size * sizeof(queue_t));
    
    // if space was malloced,
    if ( q != NULL ){
      // malloc space for data_array in queue
      q->data_array = (void*)malloc( size * sizeof(void *) );
      // set the capacity to the size passed
      q->capacity = size;
      // Initialise array elemens, head and tail to 0.
      q->elements_in_array = 0;
      q->head = -1;
      q->tail = -1;

      pthread_mutex_init(&(q->mutex), NULL);
      pthread_cond_init(&(q->condQueue1), NULL);
      pthread_cond_init(&(q->condQueue2), NULL);

    }
    return q;
}


void queue_delete(queue_t **q){
    // If the q passed is not null
    if( q != NULL && *q!=NULL ){
        // free the space for the array
        free( (*q)->data_array );
          pthread_mutex_destroy(&(*q)->mutex);
          pthread_cond_destroy(&(*q)->condQueue1);
          pthread_cond_destroy(&(*q)->condQueue2);
    }


    // free q and set it to null
    free(*q);
    *q = NULL;
}


bool queue_push(queue_t *q, void *elem){

    // If the capacity is equal to the elements in the array i.e
    // if the array is full! Dont accept any push requests!
    
    if (!q){
    
    	return false;
    }
    
    pthread_mutex_lock(&q->mutex);

    while( q->capacity == q->elements_in_array ){
      // Don't accept push request!
      pthread_cond_wait(&q->condQueue1, &q->mutex);
    }
    


    
    if (q->head == -1 && q->tail == -1){
        q->head = 0;
        q->tail = 0;
        q->data_array[q->tail] = elem;
        
    }
    
    else{
    
        q->tail = (q->tail + 1) % q->capacity;
        q->data_array[q->tail] = elem;
    }


    q->elements_in_array += 1;
   // printf("PUSH %p to index: %d and head is: %d\n",elem, q->tail,q->head);
    pthread_cond_signal(&q->condQueue2);
    pthread_mutex_unlock(&q->mutex);


    // return true
    return true;
}




bool queue_pop( queue_t *q, void **elem ){
    
    // If the elements in the array are 0 i.e it is empty.
    // Dont accept any pop requests!


   if (!q){
    
        return false;
    }
    
    pthread_mutex_lock(&q->mutex);


    while( q->elements_in_array <= 0 ){
      // Don't accept push request!
      pthread_cond_wait(&q->condQueue2, &q->mutex);
    }

    // Otherwise, store value in elem
    
    if (q->head == q->tail){
        *elem = q->data_array[q->head];

        q->head = q->tail = -1;
    
    }
   
    
   else{
        *elem = q->data_array[q->head];

    // Ensure we dont go beyond the space allocated i.e circular queue.
        q->head=( q->head + 1 ) % q->capacity;
   
   }
    
    // Decrement the number of elements in array
    q->elements_in_array -= 1;

    //printf("POST POP %p from index(head): %d and tail is: %d\n",*elem, q->head,q->tail);
    
    pthread_cond_signal(&q->condQueue1);
    pthread_mutex_unlock(&q->mutex);

    // IF CONDIITON THAT SAYS --> IF THE ARRAY IS FULL AND WE ARE POPPING FROM HERE, THEN SIGNAL TO PUSH
    // return true
    return true;
}



