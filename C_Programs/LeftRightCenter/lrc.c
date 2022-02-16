#include <stdio.h>
#include <stdlib.h>

///************** Global Variable Definition ***************/// 

const char * names[] = {
  "Happy",
  "Sleepy",
  "Sneezy",
  "Dopey",
  "Bashful",
  "Grumpy",
  "Doc",
  "Mirror Mirror",
  "Snow White",
  "Wicked Queen"
  };

typedef enum faciem {
  LEFT,
  RIGHT,
  CENTER,
  PASS
  }
  faces;
faces die[] = {
  LEFT,
  RIGHT,
  CENTER,
  PASS,
  PASS,
  PASS
  };

  int money_in_pot = 0;                                                        //~~ Counter to track money in pot

  // ************* Left and Right Position Calculating Function **************//
  //The following two functions will receive the position of the current player and the 
  //total number of players and will return the position of the player to the left or to 
  // the right depending on the function called.

  int left(int current_player, int total_players){       
  return ((current_player + total_players - 1) % total_players);
  };

  int right(int current_player, int total_players){
  return ((current_player + 1) % total_players);
  };


  // ************* Function to handle the result of the die roll ************* //
  // This function takes the result of the die roll, the current player, the total number of 
  // players and switches to the relevant case and updates the money in bank for the current 
  // player and the player to the left or right or puts it in the pot or passes depending on 
  // the output.

  int output_handler(int outcome,int current_player,int total_players,int money_array[]){
  int LOR_player;                                                            //~~ Store position result of players beside the current player

  // Switch statement to handle dice outputs
  switch (outcome){

  // If the die rolls 0 i.e LEFT  
  case 0:
  LOR_player = left(current_player,total_players);                       // Call the left function to get position of left player w.r.t current
  money_array[LOR_player]++;                                             // Add 1 dollar to the left player's bank
  money_array[current_player]--;                                        // Subtract 1 dollar from the current players bank

  printf("gives $1 to %s ",names[LOR_player]);
  break;
    
  // If the die rolls 1 i.e RIGHT 
  case 1:                                             
  LOR_player = right(current_player,total_players);                      // Call the right function to get position of right player w.r.t current
  money_array[LOR_player]++;                                            // Add 1 dollar to the right player's bank
  money_array[current_player]--;                                        // Subtract 1 dollar from the current players bank
  printf("gives $1 to %s ",names[LOR_player]);
  break;
    
  // If the die rolls 2 i.e CENTER  
  case 2:
  money_in_pot++;                                                        // Add 1 dollar to the pot
  money_array[current_player]--;                                        // Subtract 1 dollar from the current players bank
  printf("puts $1 in the pot ");
  break;
    
  // If the die rolls 3,4,5 i.e PASS 
  default:                                            
  if (outcome==3 || outcome==4 || outcome==5){                          // If die outcome is 3,4 or 5 then the current player gets a pass
  printf("gets a pass ");
  break;}
  }
  return 0;
  }


  // ************* Function where actual game begins ************* //
  // This function is called from the main function //

  int start_game (int seed, int num_of_player) {
  srand(seed);                                                               //~~ Providing seed to srand
  int outcome;                                                               //~~ outcome varible to store die outcome
  int check_counter;                                                         //~~ check_counter varible for zero checking loop
  int counter;                                                               //~~ counter variable to keep track of current player
  // *********** If 1 < number of players <= 10 *********** //
  if (1 < num_of_player && num_of_player <= 10) {

  //*** Initializing variable and arrays *** //                

  // ********** Initiliazing money array to store ********** //
  int money_array[num_of_player];                                          //~~ money_array variable - to keep track of money of all players in the running game 
  for (counter = 0; counter < num_of_player; ++counter){
  money_array[counter] = 3;}                                             //~~ Initializing array as [3,3,3,3,]


  // ********** ROLL DICE BEGINS ********** //
  while (1) {
  int coun=0;                                                            //~~ coun variable to count number of zeroes

  // ********** Check how many zeroes money_array has and update counter ********* //
  for (check_counter=0; check_counter < num_of_player; check_counter++){
  if (money_array[check_counter]==0){
  coun++;}}

  // ********** If the only one player has money remaining then break ************ // 
  if (coun == (num_of_player-1)){
  printf("\n");
  break;}

  // ********** Else continue with the game ********** //
  else {

  // ***** for loop that has counter variable which will keep track of which player is playing from the names list ***** //
  for (counter = 0; counter < num_of_player; counter++) {    
  int roll_times = 0;                                                  //~~ roll_times keeps track of how many rolls each player has
        
  // ***** If current player has 3 or more dollars ***** //
  if (money_array[counter] >= 3) {
  int roll_times = 0;                                                // Re-initiliaze roll_times to 0

  // Loop thrice as the player can roll 3 dice
  while (roll_times < 3) {

  // roll the dice and store the result in the outcome variable
  outcome = (rand() % 6);

  // If the first player is rolling then print the players name and then call the output_handler function
  if (roll_times == 0){
  coun=0;                                                        // Re-initialiaze coun to 0

  // Before printing or calling, check the money array and the number of players left with money in bank
  for (check_counter=0;check_counter<num_of_player;check_counter++){
  if (money_array[check_counter]==0){
  coun++;}}
  if (coun >= (num_of_player-1)){
  printf("%s wins the $%d pot with $%d left in the bank!",names[counter],money_in_pot,money_array[counter]);
  printf("\n");
  break;}
  printf("%s rolls... ",names[counter]);
        
  // **** Call the output handler function and increment roll_times variable **** //
  output_handler(outcome,counter,num_of_player,money_array);
  roll_times++;}

  // If the last player is rolling then call the output_handler function and then go to a new line 
  else if (roll_times == 2){
  coun=0;                                                           // Re-initialiaze coun to 0

  // Before printing or calling, check the money array and the number of players left with money in bank
  for (check_counter=0;check_counter<num_of_player;check_counter++){
  if (money_array[check_counter]==0){
  coun++;}}
  if (coun >= (num_of_player-1)){
  printf("%s wins the $%d pot with $%d left in the bank!",names[counter],money_in_pot,money_array[counter]);
  printf("\n");
  break;}

  // **** Call the output handler function and increment roll_times variable **** //
  output_handler(outcome,counter,num_of_player,money_array);
  printf("\n");
  roll_times++;}//else if

  // For all other players simply call the output handler function
  else {
  coun=0;                                                           // Re-initialiaze coun to 0

  // Before printing or calling, check the money array and the number of players left with money in bank
  for (check_counter=0;check_counter<num_of_player;check_counter++){
  if (money_array[check_counter]==0){
  coun++;}}
  if (coun >= (num_of_player-1)){
  printf("%s wins the $%d pot with $%d left in the bank!",names[counter],money_in_pot,money_array[counter]);
  printf("\n");
  break;}

  // **** Call the output handler function and increment roll_times variable **** //
  output_handler(outcome,counter,num_of_player,money_array);
  roll_times++;}//inner else
  }// while inner
  }//if inner
          
  // ***** If current player has 2 dollars ***** //  
  else if(money_array[counter] == 2){
  int roll_times = 0;                                                    // Re-initiliaze roll_times to 0

  // Loop twice as the player can roll 2 dice
  while (roll_times < 2) {

  // roll the dice and store the result in the outcome variable
  outcome = (rand() % 6);

  // If the first player is rolling then print the players name and then call the output_handler function
  if (roll_times==0){
  coun=0;                                                            // Re-initiliaze coun to 0

  // Before printing or calling, check the money array and the number of players left with money in bank
  for (check_counter=0;check_counter<num_of_player;check_counter++){
  if (money_array[check_counter]==0){
  coun++;}}
  if (coun >= (num_of_player-1)){
  printf("%s wins the $%d pot with $%d left in the bank!",names[counter],money_in_pot,money_array[counter]);
  printf("\n");
  break;}

  // **** Call the output handler function and increment roll_times variable **** //
  printf("%s rolls... ",names[counter]);
  output_handler(outcome,counter,num_of_player,money_array);
  roll_times++;}

  // If the last player is rolling then call the output_handler function and then go to a new line    
  else if (roll_times==1){
  coun=0;                                                          // Re-initiliaze coun to 0

  // Before printing or calling, check the money array and the number of players left with money in bank
  for (check_counter=0;check_counter<num_of_player;check_counter++){
  if (money_array[check_counter]==0){
  coun++;}}
  if (coun >= (num_of_player-1)){
  printf("%s wins the $%d pot with $%d left in the bank!",names[counter],money_in_pot,money_array[counter]);
  printf("\n");
  break;}//inner if

  // **** Call the output handler function and increment roll_times variable **** //
  output_handler(outcome,counter,num_of_player,money_array);
  printf("\n");
  roll_times++;
  }//else if
  }//while
  }//else if main

  // ***** If current player has 1 dollar ***** //
  else if (money_array[counter] == 1) {
  int roll_times = 0;                                                     // Re-initiliaze roll to 0
  coun=0;                                                                 // Re-initiliaze coun to 0

  // Before printing or calling, check the money array and the number of players left with money in bank
  for (check_counter=0;check_counter<num_of_player;check_counter++){
  if (money_array[check_counter]==0){
  coun++;}}
  if (coun >= (num_of_player-1)){
  printf("%s wins the $%d pot with $%d left in the bank!",names[counter],money_in_pot,money_array[counter]);
  printf("\n");
  break;}

  // **** Call the output handler function and increment roll_times variable **** //
  outcome = (rand() % 6);
  printf("%s rolls... ",names[counter]);
  output_handler(outcome,counter,num_of_player,money_array);
  printf("\n");
  roll_times++;}
  }
  }
  }
  }
  return 0;
  }

  int main() {

  // **** Initializing GIVEN PARAMETERS and Other VARIABLES **** //

  int seeding, number_of_players;


  // INPUT FOR SEED
  printf("Random Seed: ");
  scanf("%d", & seeding);

  // INPUT FOR NUMBER OF PLAYERS
  printf("How many players? ");
  scanf("%d", & number_of_players);

  // CALL start_game FUNCTION to start the game
  start_game(seeding, number_of_players);

  return 0;
  }