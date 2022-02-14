#include<stdlib.h>
#include<stdio.h>
#include"List.h"
#include"graph.h"


//____________________________________________________________________
// Graph constructor:- Here we build a grapha and intialize its members!
graph createGraph(int num){
  
  // malloc space
  graph g = malloc(sizeof(graphObj));
  
  // do a NULL check
  if (!g){
     return 0;
   }

  // if exists
  else{
    // set the dimensions of the graph
    g->n = num; 

    // calloc space for matrix row i.e with all 0's
    g->matrix = (int**)calloc(g->n , sizeof(int *));

    // calloc space for columns in the matrix in a loop
    for (int i = 0; i <  g->n; i++){
        g->matrix[i]= calloc(g->n , sizeof(int)); 
    }
  }

  // return graph
  return g;
}
//_____________________________________________________________________




//_____________________________________________________________________
// Graph destructor:- Here we destruct a graph and its members!
void destructGraph(graph g){

  // If the graph exists
  if (g) {
    // loop through it row wise and destruct it!
    for (int i = 0; i < g->n; i++) { 
      free(g->matrix[i]);
    }

    // free the space malloced for the matrix
    free(g->matrix);
    g->matrix = NULL;
    // free the graph
    free(g);
    g = NULL;
  }
  return;
}
//_____________________________________________________________________





//_____________________________________________________________________
// TODO: implement addEdge function
// addEdge:- This function adds an edge from vertex i to vertex j
void addEdge(graph g, int i, int j){

  // if i and j are not within bounds, exit
  if ( i > g->n || j > g->n){
    printf("Error! i and j are not in range!\n");
    return;
  }

  // else if they are, set the value from i to j
  else{
    g->matrix[i][j] = 1;
  }
  return;
}
//_____________________________________________________________________





//_____________________________________________________________________
// TODO: implement removeEdge function
// removeEdge:- This function removes edge from vertex i to vertex j
void removeEdge(graph g, int i, int j){

  // if i and j are not within bounds, exit
  if ( i > g->n || j > g->n){
    printf("Error! i and j are not in range!\n");
    return;
  }

  // else if they are, unset the value from i to j
  else{
    g->matrix[i][j] = 0;
  } 

  return;
}
//_____________________________________________________________________





//_____________________________________________________________________
// TODO: implement hasEdge function
// indicates if graph g has edge from vertex i to vertex j
int hasEdge(graph g, int i, int j){

  // if i and j are not within bounds, exit
  if ( i > g->n || j > g->n){
    printf("Error! i and j are not in range!\n");
    exit(1);
  } 

  // else if they are
  else{
    // check if the matrix has an edge
    if (g->matrix[i][j] != 0){
      // if so, return 1
      return 1;
    }
    else{
      // else return 0
      return 0;
    }
  }

}
//_____________________________________________________________________





//_____________________________________________________________________
// TODO: implement outEdges function
// outEdges:- takes in an empty list and adds to it all outgoing edges
// out of vertex i
void outEdges(graph g, int i, node** list){

  // if the index is not within bounds, exit
  if ( i > g->n ){
    printf("Error! i and j are not in range!\n");
    exit(1);    
  }

  // else
  else
  {
    // initialize a node to NULL
    node *n = NULL;
    // loop through the matrix column wise for row i
    for (int k = 0; k < g->n ; k++)
    {

      // in row i, as we loop through the columns, if we
      // encounter a 1 i.e there is an edge from i to k,
      // then we create a node and insert k in the list
      if (g->matrix[i][k] == 1)
      {
        n = createList(k);
        insertList(list, n);
	      n = NULL;  
      }

    }

  }
}
//_____________________________________________________________________





//_____________________________________________________________________
// TODO: implement inEdges function
// inEdges:- takes in an empty list and adds to it all incoming edges 
// into vertex j
void inEdges(graph g, int j, node** list){

  // if the index is not within bounds, exit
  if ( j > g->n ){
    printf("Error! i and j are not in range!\n");
    exit(1);    
  }

  // else
  else{

    // initialize a node to NULL
    node *n = NULL;

    // loop through the matrix row wise for column i
    for (int k = 0; k < g->n ; k++)
    {

      // in column i, as we loop through the rows, if we
      // encounter a 1 i.e there is an incoming edge from i
      // to k, then we create a node and insert k in the list
      if (g->matrix[k][j] == 1)
      {
        n = createList(k);
        insertList(list, n);
        n = NULL;   
      }
    }
  }
}
//_____________________________________________________________________




//_____________________________________________________________________
// TODO: implement getNumVer
// getNumVer:- getter function for number of vertices in a graph
int getNumVer(graph g){
  // Return the number of vertices of the graph
  return g->n;

}
//_____________________________________________________________________





//_____________________________________________________________________
// TODO: implement printGraph
// printGraph:- prints the matrix representation of the graph
void printGraph(graph g){

  // Loop through the row
  for (int i = 0; i < g->n; i++) {
    // Loop through the column
    for (int j = 0; j < g->n; j++) {
      // print
      printf("%d ", (g->matrix[i][j]));
    }
    // print a new line
    printf("\n");
  }

}
//_____________________________________________________________________






