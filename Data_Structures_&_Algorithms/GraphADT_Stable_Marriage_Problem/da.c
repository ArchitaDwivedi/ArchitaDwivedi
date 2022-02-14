#include<stdio.h>
#include"List.h"
#include"graph.h"
#include<stdlib.h>






//_________________________ Helper Function __________________________
// printFinal:- 
void printFinal(graph fin,int dimen){
  node *v = NULL;
  node *vl = v;
  int vv = 0;
  
  
  for (int i = 0; i < dimen/2 ; i++){
    if ( i == 0 ){
        printf("M-Optimal matches are:");
    } 
    outEdges(fin, i , &vl);
    vv = vl->value;
    
    printf(" (%d, %d)",i,vv);
    
  }
  printf("\n");
  return;
}
//____________________________________________________________________







//_________________________ Helper Function __________________________
// check_pref:- This function takes in the preference list of a women, 
// the current man, the new man who proposed and the dimension of the graph.
// Procedure:-
// We loop over the preference list of women which starts from 
// dimension / 2. If we happen to find a value same as the current_man,
// we store its index, similarly when we find a value same as the new
// man we store its index as well. Finally, once we are done with the 
// loop, we compare the two indexes and we know that whichever is the 
// smaller one comes first in the preference list. So, if current_man
// is smaller then we need not break the woman's current engagement, so
// we return 0, otherwise, we return 1.
int check_pref(int *preference_list,int current_man,int i,int dimen){

  int k = 0, cmi = 0, nmi = 0;

  // Loop through the woman's preference list
  for (k = 0; k < dimen/2; k++){

    // if we find current_man in woman's list, store
    // the index
    if ( preference_list[k] == current_man ){
      cmi = k;
    }

    // if we find new man in woman's list, store
    // the index
    else if (preference_list[k] == i){
      nmi = k;
    }
  }

  // If current_man's index is smaller, do not change 
  if (cmi < nmi){
    return 0;
  }

  // else, we need to swap the current_man with new man.
  else{
    return 1;
  }
}
//____________________________________________________________________








//____________________________________________________________________
// This is main function. Here, I have implemented the input and 
// algorithm.
int main(void)
{
  
  int dimen = 0, i = 0, j = 0;

  
  //----------------- Input ------------------

  // Take dimensions as input
  scanf("%d",&dimen);

  // base check
  if (dimen <= 0){
    printf("Enter a valid value for the dimension!\n");
    return 0;
  }

  // build an input matrix of dimension -> dimen x dimen / 2
  int preference_list[dimen][dimen/2];


  // Take input
  for(i=0; i < dimen; i++)    
  {    
    for(j=0; j < dimen/2; j++)    
    {    
    scanf("%d",&preference_list[i][j]);    
    }    
  }   
  //-----------------------------------------





  // --------- create graph and nodes -----------
    graph main_graph = createGraph(dimen);
    
    node *l = NULL;
    node *man_list = l;
    
    node *n = NULL;
    node *woman_list = n;
  //----------------------------------------------


    // keeps track of number of free men
    int freemen = dimen/2;
 

    // while there are free men
    while (freemen > 0)
    {

      int m = 0;
      
      // in this loop we check the man who is free i.e has no edge
      for (m = 0; m < dimen / 2 ; m++){ 

          // we call outEdges to check if there are no outgoing edges from man
          // i.e he is not engaged
          outEdges(main_graph, m , &man_list);

          // if not engaged
          if (!man_list){
              // break
              break;
          }
          // else we first empty our container and continue checking other men
          man_list = NULL;
      }


      // Now that we have a man who is free, we go through his preference list/
      // We loop through it until the man is free and the counter is in bounds
      for (int i = 0; i < dimen/2 && !man_list; i++)
      {
        // we get the women in the preference list
        int w = preference_list[m][i];  

        // check if woman is free by called inEdges i.e there are no incoming 
        // edges to the women
        inEdges(main_graph, w , &woman_list);


        // if woman is free
        if (!woman_list)
        {
            // we add an edge from the free man to the woman
            addEdge(main_graph,m,w);
            
            // we free our containers
            woman_list = NULL;
            man_list = NULL;

            // reduce the number of free men
            freemen--;
            // go to next man
            break;
        }


        // else if woman is already paired up
        else  
        {
          // get her current
          int m1 = woman_list->value;

          // check the woman's preference list and see if she
          // prefers her current man over her new man.
          // If she prefers the new man
          if (check_pref(preference_list[w],m1,m,dimen) == 1)
          {
              // we break the pair between her and her current man
              removeEdge(main_graph, m1, w);
              // we pair her up with her new man
              addEdge(main_graph, m, w);
              // we free our containers
              woman_list = NULL;
              man_list = NULL;
              // we move onto the next man
              break;
          }
          // else if she prefers her current man, we free the
          // container and container and continue finding a new
          // woman for our man.
          woman_list = NULL;
        } 
      } 
    } 
 

    // print the final output
    printFinal(main_graph,dimen);

    // free the containers
    free(man_list);
    man_list = NULL;
    free(woman_list);
    woman_list = NULL;

    // free the graph
    destructGraph(main_graph);
    main_graph = NULL;

    // return 
    return 0;
}
//____________________________________________________________________


