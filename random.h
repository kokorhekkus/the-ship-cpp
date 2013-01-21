#ifndef SHIP_RANDOM
#define SHIP_RANDOM 1

#include "base.h"

// Various utilities related to random numbers
class Random : public ShipObject{
 public:
  Random();
  ~Random();

  int inRange(int lowest, int highest);
  bool percentChance(short int percent);
};

// Representation of a dice roll 
class Dice : public ShipObject {
  Random random;
  short int numDice;
  short int numSides;
  short int modifier;

public:
  // Returns a number which is equivalent to rolling a
  // dice like, '3d4+5' where num_dice = 3, num_sides = 4, mod = 5
  Dice(short int numDice, short int numSides, short int modifier);
  ~Dice();
  
  short int roll();
};

#endif
