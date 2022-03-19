#include "boardUpdates.hpp"

bool startGame() {
  char start;
  cout << "Welcome to Battleship!" << endl;

  for (;;) {
    cout << "Would you like to play a game? (y/n)" << endl;
    cin >> start;
    
    switch (start) {
      case 'y':
      case 'Y':
        return 1;
      case 'n':
      case 'N':
        return 0;
      default:
        cout << "Invalid selection, please select either 'y' or 'n'." << endl << endl;
    }
  }
}

void placement() {
  
}

void getTarget() {
  
}
