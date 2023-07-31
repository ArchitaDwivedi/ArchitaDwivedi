# CSE130 - Assignment 2 : Bounded Buffer

This program gives user access to a queue and multiple operations on it. These multiple operations support synchronization between multiple threads!


## List of files:

The program directory should include:

```
README.md - Details about the program.

queue.c - Main program file (source code),

queue.h - Header file for queue.c.

Makefile - To make (compile, clean, format, etc.) the object file (queue.o) only.

test_files - This is a directory, that contains the files that maybe required by the scripts in test_scripts. (Given by professor).

test_scripts - This is a directory that contains the test scripts.
```

## How to run the program:

Make sure  you're in the directory where 'queue.c', 'queue.h' and 'Makefile' exists and run the following command
```
make (you could also use - make all)
```

Next, run the following command and you'll notice that an object file is created. To test and use the functions, you will have to create '.c' files yourself.


## Test Scripts

There are some test scripts in the test_scripts directory, you should run this from within that directory itself, you do not need to move them anywhere else. Otherwise, they wont work. The files that these test scripts use are in the test_files directory and they are files that were provided to us in class.
If the tests pass, 'echo $?' command should return 0, else it should return 1.

## Program Design (Part 1)

In the code, there is a queue struct that has the following field:-
1. void** data_array  - This is the main array for our Queue where things will be pushed and popped.

2. int elements_in_array - This is going to tell you the number of elements in an array.

3.  int head - This signifies the head of the queue.

4.  int tail - This signifies the tail of the queue.

5.  int capacity - This signifies how big our queue can be. i.e its capacity.


There are about 4 operations that can be done on a queue using this program:-
    1. Create a new queue
    2. Delete a queue
    3. Push to a queue
    4. Pop from a queue

Out of these, pushing and popping to a queue, support synchronization between multiple threads.

# Synchronization and Condition Variables (Part 2)
For synchronization between multiple threads, I have used the pthread library. From this, I have used mutexes to lock and unlock segments of code and not semaphores because we just want to support 1 thread accessing our locked segments at a time and semaphores would be a little too fancy for this whereas mutexes are quite straightforward. Essentially, the code to push and pop variables has been locked so that only 1 thread can access it at a time. 

There can be an edge case in this situation. When a stack is full, we cannot push any more elements on it and when the stack is empty, we cannot pop from it. For this, a while loop that checks if they're full or empty have been added to push and pop respectively, however, this is a busy waiting technique, which is not good. Especially, in the case of mutex locks. For example, lets say we were popping from an empty stack, which is an edge case, due to which we went into a loop i.e we won't pop until the queue atleast has 1 element. In this case, we want our request to be blockedd i.e it must essentially wait until something is added to the queue.

For this, we need conditional variables, which we can declare just like mutexes. So, once we enter an edge case loop, we use pthread_cond_wait() in the loop, which tells us to wait until data changes i.e the queue changes in this case. But, just like waiting, we need some other mechanism to tell us if the queue has changed i.e we need some form of signal. For this, we use pthread_cond_signal(). This function will signal to your wait function if some data (queue) was changed. 

This has been implemented for both edge cases i.e in push and in pop. For this, two condition variables have been used.
