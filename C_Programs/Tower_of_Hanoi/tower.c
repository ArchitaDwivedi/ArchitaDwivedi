#include <stdio.h>
#include "stack.h"
#include "stack.c"
#include <math.h> 
#include <stdlib.h> 
#include <stdbool.h>
#include <unistd.h>


int calc_min(int total){
int fin;
int ans=1;
for(int i = 1; i <= total ; i++){

ans = ans * 2;

}
fin = ans - 1;
return fin;
}

int recursive_exec(int total_disks,char a,char b,char c){

if (total_disks<=0){
return 0;
}    

if(total_disks>0){

recursive_exec(total_disks-1,a,c,b); 
printf("Move disk %d from peg %c to peg %c\n",total_disks,a,b);
recursive_exec(total_disks-1,c,b,a);
}
return 0;

}




void execute_iteration(struct Stack *FROM, struct Stack *TO, char source, char destination) 
{ 

int small_disk = stack_pop(FROM); 
int large_disk = stack_pop(TO);


// ->>>> execute 
// When pole 1 is empty 
if (small_disk == -2) 
{ 
if (stack_peek(FROM) != -3){
stack_push(FROM, large_disk); 
printf("Move disk %d from peg %c to peg %c\n", large_disk, destination, source); 
}
} 

// When pole2 pole is empty 
else if (large_disk == -2) 
{ 
if (stack_peek(TO) != -3){
stack_push(TO, small_disk); 
printf("Move disk %d from peg %c to peg %c\n", small_disk, source, destination);     
} 
} 

// When top disk of pole1 > top disk of pole2 
else if (small_disk > large_disk) 
{ 
if (stack_peek(FROM) != -3){
stack_push(FROM, small_disk); 
stack_push(FROM, large_disk);
printf("Move disk %d from peg %c to peg %c\n", large_disk, destination, source);      
}
} 

// When top disk of pole1 < top disk of pole2 
else
{ 
if (stack_peek(TO) != -3){
stack_push(TO, large_disk); 
stack_push(TO, small_disk); 
printf("Move disk %d from peg %c to peg %c\n", small_disk, source, destination); 
}
} 
} 

int stack_exec(int total_disks,int minimum_moves){

struct Stack *peg_A, *peg_B, *peg_C; 

// Create three stacks of size 'total_disks' 
// to hold the disks 
peg_A = stack_create(total_disks,'A'); 
peg_C = stack_create(total_disks,'C'); 
peg_B = stack_create(total_disks,'B'); 

//tohIterative(total_disks, src, aux, dest); 

int i; 
char begin = peg_A -> name, endpoint = peg_B -> name, middle = peg_C -> name; 


if (total_disks % 2 == 0) 
{ 
char x = endpoint; 
endpoint = middle; 
middle = x; 
} 



//Larger disks will be stack_pushed first 
for (i = total_disks; i >= 1; i--) 
stack_push(peg_A, i); 

for (i = 1; i <= minimum_moves; i++) 
{ 
if (i % 3 == 1) 
execute_iteration(peg_A, peg_B, begin, endpoint); 

else if (i % 3 == 2) 
execute_iteration(peg_A, peg_C, begin, middle); 

else if (i % 3 == 0) 
execute_iteration(peg_C, peg_B, middle, endpoint); 
} 

stack_delete(peg_A);
stack_delete(peg_B);
stack_delete(peg_C);

return 0; 
} 



int main(int argc, char **argv)
{
int total_disks = 0;
int minimum_moves;
int opt;
int loop = 0;
int r_opt,s_opt;
int counter = 1;
bool n_val= false,r_val = false,s_val = false;

while ((opt = getopt(argc, argv, "n:sr")) != -1) 
{
switch(opt) 
{
// -s -r -n 2
case 'n':
n_val = true;
counter = 2;
total_disks = atoi(optarg);
loop++;
if (total_disks == 0){
total_disks = 5;}
break;

case 's':
s_val = true;
loop++;
s_opt = loop;
if (total_disks == 0){
total_disks =5;}
break;

case 'r':
r_val = true;
loop++;
r_opt = loop;
if (total_disks == 0){
total_disks = 5;}           
break;

default:
printf("Input any number after -n");
return 0;
}
}    



if (n_val == true){
counter = 2;
}
else{
counter = 1;
}

if (r_val == true && s_val == true)
{

if (r_opt < s_opt)
{
///////////////

minimum_moves = calc_min(total_disks);


printf("================================\n");
printf("--------   RECURSIVE   ---------\n");
printf("================================\n");

recursive_exec(total_disks,'A','B','C');      

printf("\n");
printf("Number of moves: %d\n",minimum_moves);


if (counter != loop){
printf("\n");}
counter++;
///// stack /////
printf("================================\n");
printf("----------   STACKS   ----------\n");
printf("================================\n");

stack_exec(total_disks,minimum_moves);


printf("\n");
printf("Number of moves: %d\n",minimum_moves);

if (counter != loop){
printf("\n");}
counter++;
return 0;
//////////////

}

else if (s_opt < r_opt)
{
printf("================================\n");
printf("----------   STACKS   ----------\n");
printf("================================\n");

minimum_moves = calc_min(total_disks);
stack_exec(total_disks,minimum_moves);


printf("\n");
printf("Number of moves: %d\n",minimum_moves);

if (counter != loop){
printf("\n");}
counter++;

//////
printf("================================\n");
printf("--------   RECURSIVE   ---------\n");
printf("================================\n");

recursive_exec(total_disks,'A','B','C');      

printf("\n");
printf("Number of moves: %d\n",minimum_moves);


if (counter != loop){
printf("\n");}

counter++;


return 0;
}
}


else if (r_val == true && s_val == false){
minimum_moves = calc_min(total_disks);
printf("================================\n");
printf("--------   RECURSIVE   ---------\n");
printf("================================\n");

recursive_exec(total_disks,'A','B','C');      

printf("\n");
printf("Number of moves: %d\n",minimum_moves);


if (counter != loop){
printf("\n");}
counter++;


return 0;

}

else if (s_val == true && r_val == false){
printf("================================\n");
printf("----------   STACKS   ----------\n");
printf("================================\n");

minimum_moves = calc_min(total_disks);
stack_exec(total_disks,minimum_moves);

printf("\n");
printf("Number of moves: %d\n",minimum_moves);

if (counter != loop){
printf("\n");}
counter++;
return 0;
}

return 0;
}
