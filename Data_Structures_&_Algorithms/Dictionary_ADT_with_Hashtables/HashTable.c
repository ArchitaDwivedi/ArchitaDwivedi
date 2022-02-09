#include"HashTable.h"


//-------------------------------------------------------
// Converts a 5 letter key into an integer
// CC###: ascii equivalent of letters and digits are simply added together.
// #####: ascii equivalent of digits are simply added together.
// -------------------------------
// Description:- This function takes in
// a char type of string (key). We loop
// each character of the string, convert it
// into its integer equivalent and add them
// all together. Finally we return the sum.
// -------------------------------
int convert( char key[5] )
{
  int res = 0, ascii_eq = 0;

  for (int i = 0 ; i < 5 ; i++){
    ascii_eq = (int)key[i];
    res = res + ascii_eq;
  }
  return res;
}



// -------------------------------
// Hash function that returns an index into the hash table given a key
// use the module formula on page 263 of CLRS.
// -------------------------------
// Description:- This function takes in
// a char type of string (key) and the
// total number of slots in a hashtable.
// We first call convert to get the 
// integer value of the key. Then we 
// mod it with the number of slots. 
// Finally we return the final converted
// index back. 
// -------------------------------
int hash( char key[5], int slots )
{
  int val = convert(key);
  val = val % slots;
  return val;
}

