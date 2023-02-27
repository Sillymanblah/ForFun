#ifndef BOARD_HPP
#define BOARD_HPP

#include "gameLimits.hpp"

class Board {
  private:
    /*
      Integers to hold the size of the board, the dimensions will determine
      max ship length, total size will determine ship number.
    */
    int length, width, numShips, numShipSquares, maxShipLength;
    // Boolean value to hold the shape of the board, square, rectangle, or irregular shaped
    bool isSquare, isRectangular;
    // Holds values for squares not included in irregularly shaped boards.
    int* missingSquares;
    // Holds the variables for the ship types, this will allow implementation of abilities.
    Ship* ships;
  
    void addShip();
    
  public:
    Board(int length, int width);
    Board(int length, int width, int* emptySquares);
    ~Board();
    bool isHit(int xPos, int yPos);
};

// Trying something different, what is below is for reference.

// void shipCount() {
  
// }

// void boardDisplay() {
  
// }

// void placeShip() {
  
// }

// /* Starting the game, this function calls upon a few other functions to set up
//    the board mapping, times it's set up, and then allows ship placement. */
// void initiation() {
//   cout << "Starting Game...";
//   int startupTime = clock();
//   boardShape();
//   int timeCompletion = clock() - startupTime;
  
//   boardDisplay(); placeShip();
  
  
  
// }

// // Checks a square for a 
// bool checkHit() {
  
// }

// void shipSunk() {
  
// }

#endif
