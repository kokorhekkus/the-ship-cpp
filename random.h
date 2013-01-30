#ifndef SHIP_RANDOM
#define SHIP_RANDOM 1

// Various utilities related to random numbers

// returns a number in the range lowest-highest
int inRange(int lowest, int highest);
// returns true if the percent chance is 'beaten'
bool percentChance(int percent);

// Representation of a dice roll 
class Dice {
private:
  int numDice;
  int numSides;
  int modifier;

public:
  // Returns a number which is equivalent to rolling a
  // dice like, '3d4+5' where num_dice = 3, num_sides = 4, mod = 5
  Dice(int numDice, int numSides, int modifier);
  ~Dice();
  
  int roll();
};

#endif
