#include "gameLimits.hpp"

void shipCount() {
  
}

void boardDisplay() {
  
}

void placeShip() {
  
}

/* Starting the game, this function calls upon a few other functions to set up
   the board mapping, times it's set up, and then allows ship placement. */
void initiation() {
  cout << "Starting Game...";
  int startupTime = clock();
  boardShape();
  int timeCompletion = clock() - startupTime;
  
  boardDisplay(); placeShip();
  
  
  
}

// Checks a square for a 
bool checkHit() {
  
}

void shipSunk() {
  
}
