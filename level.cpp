// Level implementation

#include "level.h"

using namespace std;

//----------------------------------------------------------------------
// LevelMap class implementation
//----------------------------------------------------------------------

Level::Level(LevelMap* a_levelMap) :
  levelMap(a_levelMap) {}

Level::~Level() {}

// add an object to the level
void Level::addObject(const Thing& t) {
  objects.push_back(t);
}

// remove an object from the level
void Level::delObject(unsigned int id) {
  // TODO: does not seem hugely efficient to me
  for(vector<Thing>::iterator it = objects.begin(); it != objects.end(); ++it) {
	if (it->getId() == id) {
	  objects.erase(it);
	}
  }
}

// print all objects on the level to the terminal
void Level::printObjects() const {
  for(vector<Thing>::const_iterator it = objects.begin(); it != objects.end(); ++it) {
	it->print();
  }
}

// prints everything on the level
void Level::print() const {
  levelMap->print();
  printObjects();
}
