#include <stdio.h>
#include <stdlib.h>

  // Define global variables
  int dim1,dim2,border,fill,xc,yc;
  int **arr = NULL;

  // Recursive function
  int recursion(int yc, int xc){

    // If co-ordinates are out of bounds return to previous co-ordinate
    if ( yc >= dim1 || yc < 0 || xc < 0 || xc >= dim2 ){
      return 0;
    }

    // If value at co-ordinate in array is the border value or filled, 
    // return to previous co-ordinate
    if ( (arr[yc][xc] == border) || (arr[yc][xc] == 11 ) ){
      return 0;
    }

    // Else fill the location
    arr[yc][xc] = fill;
    // Go North
    recursion(yc - 1,xc);

    // Go East
    recursion(yc,xc + 1);

    // Go West 
    recursion(yc,xc - 1);

    // Go South
    recursion(yc + 1,xc);

    // return value 1
    return 1;
  }

  //----------------------------------------------------------------//


  int main(){
    // Input Dimensions of the matrix
    scanf("%d  %d",&dim1,&dim2);

    // Input Polygon border value
    scanf("%d",&border);


    // Input Fill color value
    scanf("%d",&fill);


    // Input Starting co-ordinates
    scanf("%d  %d",&yc,&xc);


    // Allocate row space dynamically for the matrix
    // This means we will have these many spaces to be filled
    // in the array
    arr = malloc(dim1 * sizeof(int *));

    // loop counter
    int i, j;	


    // Allocate column space dynamically for the matrix
    // i.e inside the row space we allocated previously, 
    // we can fill elements column wise in a loop.
    for (i = 0; i < dim1; i++){
      arr[i] = malloc(dim2 * sizeof(int));
    }


    // Take input in the newly made array, in 
    // form of rows and columns i.e array[rows][columns]
    for (i = 0; i < dim1; i++) // row
    {
      for (j = 0; j < dim2; j++) // column
      {
        scanf( "%d ", &arr[i][j] );
      }
    }


    // Call recursive function with user given co-ordinates
    int final = recursion(yc,xc);

    // After function returns print the array
    if (final == 1)
    {

      printf("\n");  // print a space before print loop
      
      for (i = 0; i < dim1; i++) // row
      {
        for (j = 0; j < dim2; j++) // column
        {
          printf( "%4d", arr[i][j] );
        }
        printf("\n");
      }
    }

    // exit
    return 0;
  }
