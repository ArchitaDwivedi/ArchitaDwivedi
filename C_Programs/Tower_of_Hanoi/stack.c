#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
#include <stdbool.h>

/////////////////////////////////
Stack *stack_create(int capacity,char name) {
  if (capacity < 1){
	  capacity = 1;
	  }
	struct Stack* current_stack = (struct Stack*) malloc(sizeof(struct Stack));
  	current_stack -> name = name; 
	current_stack -> capacity = capacity;
	current_stack -> top = -1;

	current_stack -> items = (int *)malloc(current_stack -> capacity * sizeof(int));

	return current_stack;
	
	}

/////////////////////////////////
void stack_delete(struct Stack *current_stack){
	free(current_stack);
	current_stack -> top = -1;
}

/////////////////////////////////
int stack_pop(struct Stack* current_stack) 
{ 
	if(current_stack -> top == -1) 
	{ 
		return -2;  
	} 
	else{
		int val = current_stack -> items[current_stack -> top];
		current_stack -> top -= 1; 
    return val;
}
}

/////////////////////////////////
// Function to add an item to stack. It increases 
// top by 1 
void stack_push(struct Stack *current_stack, int item) 
{ 
  if (current_stack -> top != current_stack -> capacity - 1){
    current_stack -> top += 1;
	  current_stack -> items[current_stack -> top] = item;
    return;}
  
  else {
  return;
  }
}

/////////////////////////////////
// Stack is empty when top is equal to -1 
bool stack_empty(struct Stack* current_stack) 
{ 
	if (current_stack -> top == -1){
	return true;}
	else{ 
	return false;}
} 

/////////////////////////////////
int stack_peek(struct Stack *current_stack){

  if (current_stack -> top == current_stack -> capacity - 1){
    return -3;                                
  }
  else {
  int peek_value = current_stack -> items[0];	
	return peek_value;}
}
