#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"


//_____________________________________________
// Description:- This function is used to 
// add two Power/Degree Lists together.
// For this purporse,
// The function takes in 2 lists, sets up 
// some counters. Saves the initial length
// of the 2 lists. After that it takes an 
// element out of the first List, and in 
// a loop adds it with another List's elements.
// While doing so, It makes sure to not modify
// the original list by appending every deleted
// element to the original List. Simultaneously,
// it also appends the result into the Final List.
List poly_power(List C1, List C2){

  List Final = newList();
  int i = 0 , j = 0, len_c1, len_c2, m1, m2;
  len_c1 = length(C1);
  len_c2 = length(C2);

  while( i < len_c1){
    m1 = max(C1);
    int val1 = delElement(C1, m1);
    i++;
    j = 0;

    while( j < len_c2 ){
      int val2 = delElement(C2, 0);
      int res = val1 + val2;
      j++;
      appendList(Final, res);
      appendList(C2, val2);
    }
  }
  return Final;
}
//_____________________________________________




//_____________________________________________
// Description:- This function is used to 
// add two Coefficient Lists together.
// For this purporse,
// The function takes in 2 lists, sets up 
// some counters. Saves the initial length
// of the 2 lists. After that it takes an 
// element out of the first List, and in 
// a loop adds it with another List's elements.
// While doing so, It makes sure to not modify
// the original list by appending every deleted
// element to the original List. Simultaneously,
// it also appends the result into the Final List.
List poly_coeff(List C1, List C2){

  List Final1 = newList();
  int i = 0 , j = 0,len_c1,len_c2,m1,m2;
  len_c1 = length(C1);
  len_c2 = length(C2);

  while( i < len_c1){
    int val1 = delElement(C1, 0);
    i++;
    j=0;

    while( j < len_c2 ){
      int val2 = delElement(C2, 0);
      int res = val1 * val2;
      j++;
      appendList(Final1, res);
      appendList(C2, val2);
    }
  }
  return Final1;
}
//_____________________________________________






//_____________________________________________
// Description:- These are the helper functions
// which were provided in class and have been
// implemented just like was specified.
int  isPlus( char c )   // returns true if c is '+'
{
  if (c == '+')
    return true;

  else
    return false;

}

int  isMinus( char c )    // returns true if c is '-'
{
  if (c == '-')
    return true;

  else
    return false;  
}

int  isVar( char c )    // returns true if c in range '[a..z]'
{
  if (c >= 'a' && c<= 'z')
    return true;

  else
    return false;
}

int  isPower( char c )    // returns true if c is '^'
{
  if (c == '^')
    return true;

  else
    return false;  

}

int  isWhite( char c )    // returns true if c is blank/tab
{
  if (c == ' ')
    return true;

  else
    return false;  
}
//_____________________________________________




//_____________________________________________
// Description:- This function is used to print
// the values of the Final List, after the 
// polynomial Multiplication. There are Mutiple
// Cases which are explained in the code. 
void printFinal (List Pow , List Coeff,char v){
  int valu2_new = 0;       // gets values
  int pcount = 0;          // counter to see if its the first term
  int counter = 0;         // loop counter
  int len_of_pow = length(Pow); // store length of Power List


  // We loop until counter < length of Power/Degree List
  while(counter < len_of_pow){
    // Get values from Power/Degree and Coefficient Lists
    int valu1 = delElement(Pow, 0);
    int valu2 = delElement(Coeff, 0);


  //---> Case for when we encounter a Power/Degree > 1
  if (valu1 > 1)
  {
    //-> If the Coefficient is positive
    if (valu2 > 1)
    {
      //-> Check if its the first term we're dealing with
      if ( pcount == 0) 
      {
        //-> Dont print a space before term
        printf("%d%c^%d",valu2,v,valu1); 
        pcount = 1; // set to 1, now that the first term is dealt with
      }
      // If it's not the first term
      else
      {
      // print with space and + before term
      printf(" + %d%c^%d",valu2,v,valu1);
      }
    }


    //-> If the Coefficient is 1 or -1
    else if (valu2 == 1 || valu2 == -1){
      // convert and save value in negative
      valu2_new = 0 - valu2;  
      
      // If Coefficient is 1
      if (valu2 == 1){
        // and its the first term
        if ( pcount == 0 )
          {
            // print nothing before character
            printf("%c^%d",v,valu1);
            pcount = 1;
          }

          // if its not the first term
          else
          {
          // print nothing before character 
          printf(" + %c^%d",v,valu1);
          }          
      }
      

      // If Coefficient is -1
      if (valu2 == -1){
        // and is the first term
        if ( pcount == 0 )
          {
            // print - before character
            printf("-%c^%d",v,valu1);
            pcount = 1;
          }
          // else if it is not the first character
          else
          {
          // print - before character and space 
          printf(" - %c^%d",v,valu1);
          }          
      }
           
    }


    // Is less than -1
    else if ( valu2 < -1 )
    {
      // convert and save value in negative
      valu2_new = 0 - valu2;
      // if the first term
      if ( pcount == 0)
      {
        // print - before character without space
        printf("-%d%c^%d",valu2_new,v,valu1);
        pcount = 1; // first term is dealt with so set to 1
      }
      else
      {
      // print - before character with space
      printf(" - %d%c^%d",valu2_new,v,valu1);
      }
    }


  }
//-------------------------------------------------------


  //---> Case for when we encounter a Power/Degree  = 1
  else if (valu1 == 1)
  {
    // if Coefficient is > 1
    if (valu2 > 1)
    {
      // and it's the first term
      if ( pcount == 0 )
      {
        // print without space
        printf("%d%c",valu2,v);
        pcount = 1;
      }
      // else if it isnt the first term
      else
      {
      // print with space
      printf(" + %d%c",valu2,v);
      }
    }
    
    
    // if Coefficient is is 1 or -1
    else if (valu2 == 1 || valu2 == -1){
      // convert and save negative
      valu2_new = 0 - valu2;
      
      // if Coefficient is 1
      if (valu2 == 1){
        // if it is the first term
        if ( pcount == 0 )
          {
            // print just the character
            printf("%c",v);
            pcount = 1; // first term is dealt with so set to 1
          }
          // if it is not the first character
          else
          {      
          // print with + and space
          printf(" + %c",v);
          }          
      }


      // if Coefficient is -1 
      if (valu2 == -1){
        // if it is the first term
        if ( pcount == 0 )
          {
            // print just the character with - and no space
            printf("-%c",v);
            pcount = 1; // first term is dealt with so set to 1
          }
          // if it is not the first character
          else
          {   
          // print with - and space
          printf(" - %c",v);
          }          
      }      
           
    }
    
    
    
    // if Coefficient is <  -1
    else if(valu2 < -1)
    {
      // convert and save negative 
      valu2_new = 0 - valu2;
      // if it is the first term
      if ( pcount == 0)
      {
        // print just the character with - and no space
        printf("-%d%c",valu2_new,v);
        pcount = 1;
      }
      // if it is not the first character
      else
      {      
      // print with - and space
      printf(" - %d%c",valu2_new,v);
      }
    }
  }
//-------------------------------------------------------


  //---> Case for when we encounter a Power/Degree  = 0
  else if(valu1 == 0)
  {
    // if Coefficient is positive
    if (valu2 > 0)
    {
      // and it's the first term
      if ( pcount == 0)
      {
        // print number
        printf("%d",valu2);
        pcount = 1; // first term is dealt with so set to 1
      }
      // if it is not the first character
      else
      {       
      // print with space
      printf(" + %d",valu2);
      }
    }


    // if Coefficient is negative
    else if (valu2 < 0)
    {
      // convert and save negative value
      valu2_new = 0 - valu2;

      // and it's the first term
      if ( pcount == 0)
      {
        // print number with a -
        printf("-%d",valu2_new);
        pcount = 1; // first term is dealt with so set to 1
      }
      // if it is not the first character
      else
      {
      // print with space and -
      printf(" - %d",valu2_new);
      }
    }
  }

  // Append the values to Power and Coefficient Lists 
  // so as to preserve the original state of the list.
  appendList(Pow, valu1);
  appendList(Coeff, valu2);
  // update loop counter and continue
  counter ++;
}

// print new line
printf("\n");
return;
}





//------------------------------------------
// Description:- Main Function Begins here
int main(){


//___________________________________
// LIST and Counter INITIALIZATION
  List L1 = newList();
  List L1_C = newList();

  List L2 = newList();
  List L2_C = newList();

  List P1 = newList();
  List C1 = newList();

  
  int count_var = 0;
  int MAX_LEN = 1000;
  int c = 0;
  int sign=1;
  int isvar = 0;
  int isnum = 0;
  int ispow = 0;
  int number = 0;
  int i = 0;
  int j = 0;
  int p = 0;
//___________________________________



//___________________________________
// Set up strings for user input

  // creating dynamic variables
  char* poly1 = (char *)calloc(MAX_LEN,sizeof(char));
  char* poly2 = (char *)calloc(MAX_LEN,sizeof(char));
  //--


  // Get input
  fgets(poly1, MAX_LEN, stdin);
  fgets(poly2, MAX_LEN, stdin);
  //--


  // Save length of strings
  int len = strlen(poly1);
  int len1 = strlen(poly2);
  //--


  // Null terminate them
  poly1[len-1]='\0';
  poly2[len1-1]='\0';
  //--


  // Update new lengths
  len = strlen(poly1);
  len1 = strlen(poly2);
  //--



  // Initialize chars
  // chars to store variable
  // and other to store characters
  // while parsing.
  char var = '\0';
  char ch = '\0';
  //--

  // Initialize chars
  // to build strings
  // out of characters. i.e '-' + '1'
  // = '-1'
  char co[len];
  char po[len];

  char co1[len1];
  char po1[len1];

  co[0]='\0';
  po[0]='\0';

  co1[0]='\0';
  po1[0]='\0';
  //--
  




  //___________________________
  // To Parse polynomial 1
  // Loop till the end of the 
  // polynomial is reached
  while (i < strlen(poly1)){


  //___________________________
  // To Parse polynomial 1
  // Description: This is used
  // to parse the first polynomial.
  // For the minus and plus checks,
  // we set the sign variable.
  // If there is a space after 
  // each, we update loop counter
  // twice to avoid the space.
  //----
  if(isMinus(poly1[i])){
    sign = -1;
    i++;
    if (isWhite(poly1[i])){
      i++;
    }
    continue;
  }
  //----

  else if(isPlus(poly1[i]))
  {
    sign = 1;
    i++;
    if (isWhite(poly1[i])){
      i++;
    }
    continue;
  }
  //---------



  //___________________________
  // For the Variable check, we
  // store the variable. Then,
  // we check if the current variable 
  // is the last variable, if it is then 
  // its power must be 1. Else if it is 
  // the first variable then we must 
  // store a 1 for the coefficient of 
  // the variable. Otherwise, we assume
  // the coefficient is also stored from the 
  // coefficient check and update counters
  // and set isvar flag to 1, so know we had
  // encounter a variable
  //----
  else if(isVar(poly1[i])){
    if ( 'a' <= poly1[i] && 'z' >= poly1[i] && count_var == 0){
      count_var = 1;
      var = poly1[i];
    }

    if ( i == (strlen(poly1) - 1) ){
      appendList(L1, 1);
    }

    if (isnum == 0){
      number = sign * 1;
      appendList(L1_C, number);
      // reset string, so it has 0 contents
      for (p = 0 ; p < strlen(co);p++){
        strncpy(co,"",strlen(co));
        co[i]='\0';
    }
    }

    isnum = 0;
    isvar = 1;
    i++;
  }
  //----




  //___________________________
  // For the Power check, we go the number after
  // the power symbol and in loop get the number.
  // We append this to the Power List and simply set
  // its flag to 1.    
    else if (isPower(poly1[i])){
      i++;
      while(!(isVar(poly1[i])) && !(isWhite(poly1[i])) && i < (strlen(poly1))){
        ch = poly1[i];
        strncat(po,&ch,1);
        i++;
      }

      number = atoi(po);
      appendList(L1, number);
      // reset string, so it has 0 contents
     for (p = 0 ; p < strlen(po);p++){
         strncpy(po,"",strlen(po));
          po[i]='\0';
      }
      ispow = 1;
    }
    //----



 //___________________________
  // For the WhiteSpace check, we first check
  // if there was power taken in before the
  // whitespace. If it was then we update counter
  // and move on. Else if there was a constant 
  // before space, we append it to the Coefficient List
  // and a 0 to the Power List. Else if there was a 
  // variable before the whitespace then we append a
  // one to the Power List and update counter and 
  // reset counters.
  else if (isWhite(poly1[i])){
    if (ispow == 1){
      isvar = 0;
      ispow = 0;
      i++;
      continue;
    }

    if (isnum == 1){
      appendList(L1, 0);
      isnum = 0;
    }

    else if (isvar == 1){
      appendList(L1, 1);
      isvar = 0;
    }
    i++;
    continue;
  }
  //----



  //___________________________
  // For the Coefficient check, in a loop we take in the 
  // number, append it to the Coefficient List. If the 
  // Coefficient happens to be the last term, then we 
  // Append power to 0 as well.
  //-----
  else{
    while(!(isVar(poly1[i])) && !(isWhite(poly1[i])) && i < strlen(poly1)){
      ch = poly1[i];
      strncat(co,&ch,1);
      i++;
    }
    
    if ( i >= (strlen(poly1)) ){
      appendList(L1, 0);
      i++;
    }
    
    isnum = 1;
    number = sign * atoi(co);
    appendList(L1_C, number);
    // reset string, so it has 0 contents
    for ( p = 0 ; p < strlen(co);p++){
        strncpy(co,"",strlen(co));
        co[i]='\0';
    }
  }
  //----

  }
//__________________________________






//__________________________________
// To Parse polynomial 2
// Reset Counters and Perform the 
// exact same steps as above for 
// polynomial 2
  c = 0;
  sign=1;
  isvar = 0;
  isnum = 0;
  ispow = 0;
  number = 0;

 //-----
 while (j < strlen(poly2)){

  //-----
  if(isMinus(poly2[j]))
  {
    sign = -1;
    j++;
    if (isWhite(poly2[j])){
      j++;
    }
    continue;
  }
  //-----

  //-----
  else if(isPlus(poly2[j]))
  {
    sign = 1;
    j++;
    if (isWhite(poly2[j])){
      j++;
    }
    continue;
  }
  //-----

  //-----
  else if(isVar(poly2[j]))
  {
    if ( j == (strlen(poly2) - 1) ){
      appendList(L2, 1);
    }

    if (isnum == 0){
      number = sign * 1;
      appendList(L2_C, number);
      for (p = 0 ; p < strlen(co1);p++){
        strncpy(co1,"",strlen(co1));
        co1[j]='\0';
      }
    }

    isnum = 0;
    isvar = 1;
    j++;
  }
  //-----

  //-----
  else if (isPower(poly2[j]))
  {
    j++;
    while(!(isVar(poly2[j])) && !(isWhite(poly2[j])) && j < (strlen(poly2))){
      ch = poly2[j];
      strncat(po1,&ch,1);
      j++;
    }

    number = atoi(po1);
    appendList(L2, number);
    for (p = 0 ; p < strlen(po1);p++){
       strncpy(po1,"",strlen(po1));
        po1[j]='\0';
    }
    ispow = 1;
  }
  //-----

  //-----
  else if (isWhite(poly2[j])){
    if (ispow == 1){
      isvar = 0;
      ispow = 0;
      j++;
      continue;
    }

    if (isnum == 1){
      appendList(L2, 0);
      isnum = 0;
    }

    else if (isvar == 1){
      appendList(L2, 1);
      isvar = 0;
    }
    j++;
    continue;
  }
  //-----

  //-----
  else
  {
    while(!(isVar(poly2[j])) && !(isWhite(poly2[j])) && j < strlen(poly2)){
      ch = poly2[j];
      strncat(co1,&ch,1);
      j++;
    }
    
    if ( j >= (strlen(poly2)) ){
      appendList(L2, 0);
      j++;
    }
    
    isnum = 1;
    number = sign * atoi(co1);
    appendList(L2_C, number);
    for ( p = 0 ; p < strlen(co1); p++){
        strncpy(co1,"",strlen(co1));
        co1[j]='\0';
    }
  }
  //-----

  }
//__________________________________






 
//__________________________
// SORTING !
// Description: Now that we
// have our inputs, we must 
// Sort them depending on their
// Powers. For this, we loop
// through the list, get the
// index of largest element,
// after which we delete it from
// the List and append it to the
// new Sorted List. We do the
// same for the Coefficient.
//----------------------------
//-- For polynomial 2
List Sorted_p1 = newList();
List Sorted_c1 = newList();

while(length(L1)){
  int ind = max(L1);
  int valu1 = delElement(L1, ind);
  int valu2 = delElement(L1_C, ind);
  appendList(Sorted_p1, valu1);
  appendList(Sorted_c1, valu2);
}

//-- For polynomial 2
List Sorted_p2 = newList();
List Sorted_c2 = newList();

while(length(L2)){
  int ind = max(L2);
  int valu1 = delElement(L2, ind);
  int valu2 = delElement(L2_C, ind);
  appendList(Sorted_p2, valu1);
  appendList(Sorted_c2, valu2);
}
//__________________________







//---------------------------------
// Print Statement for Final printing
//__________________________
printFinal(Sorted_p1,Sorted_c1,var);
printf("multiply by\n");
printFinal(Sorted_p2,Sorted_c2,var);
printf("is\n");
//__________________________





//__________________________
// Intermediary values
// We call the poly_power and poly_coeff,
// function to get the raw intermediary
// sorted form of polynomial power addition
// and polynomial coefficient multiplication.
// Store the intermediary values in result
// Lists.
List P = poly_power(Sorted_p1, Sorted_p2);
List C = poly_coeff(Sorted_c1, Sorted_c2);

// Call printFinal to print intermediary value
printFinal(P,C,var);
//__________________________





//---------------------------------
// print statement for final printing 
printf("which simplifies to\n");
//---------------------------------




//__________________________
// Simplification
// Description:- Here we simplify
// the intermediary values, by adding
// up the like terms.
// For this, we parse through the length
// of the Power List, then we get an
// element from it and the Coefficient
// List. Then we store the Coeff value.
// We loop through the power list and
// check if there is another term of 
// the same power. If there is indeed,
// then we add the coefficients and 
// dissolve to only one power term
// and append the result to the final
// lists. But incase we dont find it.
List PF = newList();
List CF = newList();
int value1,value2,res,res1,res_garb;

while(length(P)){
  res = 0;
  value1 = delElement(P,0);
  value2 = delElement(C,0);
  res = value2;

  // if same power not found
  if (find(P,value1) == -1){
    appendList(PF, value1 );
    appendList(CF, value2 );
    continue;
  }

  // if found
  else{
    // keep findind elements
    // and adding them, if 
    // done, then append to
    // final lists.
    while(find(P,value1)!= -1){
      int k = find(P,value1);
      res1 = delElement(C,k);
      res_garb = delElement(P,k);

      res = res + res1;
    }

    appendList(PF, value1);
    appendList(CF, res);
  }
}
//__________________________





//__________________________
// This is a safety block,
// where elements are sorted
// again, incase the order was
// disturbed while simplification.
// The steps for sorting are the
// same as earlier.
List Pow = newList();
List Coeff = newList();

while(length(PF)){
  int ind = max(PF);
  int valu1 = delElement(PF, ind);
  int valu2 = delElement(CF, ind);
  appendList(Pow, valu1);
  appendList(Coeff, valu2);
}
//__________________________




//__________________________
// Print Final Resulting
// polynomial and a new line
// after it.
printFinal(Pow,Coeff,var);
printf("\n");


//-------------------------
// Free all Lists
freeList(&L1);
freeList(&L1_C);
freeList(&L2);
freeList(&L2_C);
freeList(&Sorted_p1);
freeList(&Sorted_p2);
freeList(&Sorted_c1);
freeList(&Sorted_c2);
freeList(&P);
freeList(&C);
freeList(&PF);
freeList(&CF);
freeList(&Pow);
freeList(&Coeff);

// exit
return 0;



}