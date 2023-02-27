#ifndef SHIP_HPP
#define SHIP_HPP

#include "Coordinate.hpp"

enum ShipTypes {
  patrol_boat = 1;
  frigate = 2;
  submarine = 3;
  battleship = 4;
  destroyer = 5;
  aircraft_carrier = 10; // 5x2
};

class Ship {
  private:
    Coordinate startPos, endPos;
    bool isSunk, isVertical;
    ShipTypes shipType;
    int timesHit;
    // Need something for abilities.
  
  public:
    
};

#endif
