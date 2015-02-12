// Random number and dice functionality
// TODO: Argument checking on numbers passed to functions

#include "random.h"
#include "log.h"

#include <random>
#include <iostream>

using namespace std;

// returns a number in the range lowest >= num <= highest
int inRange(int lowest, int highest) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> distribution(lowest, highest);
  return distribution(mt);
}

// returns true if the percent chance is 'beaten'
bool percentChance(int percent) {
  int num = inRange(0, 100);
  if (num > percent) {
	return false;
  } else {
	return true;
  }
}

//----------------------------------------------------------------------
// Dice class implementation
//----------------------------------------------------------------------

Dice::Dice(int a_numDice, int a_numSides,
		   int a_modifier = 0) :
  numDice(a_numDice), numSides(a_numSides), modifier(a_modifier) {

  shiplog("Creating new Dice object", 10);
}
Dice::~Dice() {
  shiplog("Destroying Dice object", 10);
}

// Returns a number which is equivalent to rolling a
// dice like, '3d4+5' where numDice= 3, numSides = 4, modifier = 5
int Dice::roll() {
  int rnum = 0;
  for (int i = 0; i<numDice; i++) {
	int frnum = inRange(1, numSides);
	rnum += frnum;
  }
  return rnum + modifier;
}
