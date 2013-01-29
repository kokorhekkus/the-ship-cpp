// Random number and dice functionality
// TODO: Argument checking on numbers passed to functions

#include "random.h"
#include "log.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//----------------------------------------------------------------------
// Random class implementation
//----------------------------------------------------------------------

Random::Random() {
  shiplog("Creating new Random object", 10);
}
Random::~Random() {
  shiplog("Destroying Random object", 10);
}

// returns a number in the range lowest >= num <= highest
// REMEMBER TO SEED THE RNG
int Random::inRange(int lowest, int highest) {
  highest++;
  int base_random = rand(); // in [0, RAND_MAX]
  if (RAND_MAX == base_random) {
	return inRange(lowest, highest);
  }
  // now guaranteed to be in [0, RAND_MAX]
  int range     = highest - lowest;
  int remainder = RAND_MAX % range;
  int bucket    = RAND_MAX / range;
  // There are range buckets, plus one smaller interval
  // within remainder of RAND_MAX
  if (base_random < RAND_MAX - remainder) {
    return lowest + base_random/bucket;
  } else {
    return inRange(lowest, highest);
  }
}

// returns true if the percent chance is 'beaten'
bool Random::percentChance(int percent) {
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
	int frnum = random.inRange(1, numSides);
	rnum += frnum;
  }
  return rnum + modifier;
}
