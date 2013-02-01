// Level implementation

#include "level.h"
#include "log.h"

#include <sstream>
#include <algorithm>

using namespace std;

//----------------------------------------------------------------------
// LevelMap class implementation
//----------------------------------------------------------------------

Level::Level(LevelMap* a_levelMap) :
  levelMap(a_levelMap) {

  shiplog("Creating a new Level object",10);
}

Level::~Level() {
  shiplog("Destroying a Level object",10);
}

// return 0 if no object at location, otherwise return object ID 
unsigned int Level::objectAt(int x, int y) {
  // we can easily compare vectors, so convert from arrays
  int locArray1[2] = {x, y};
  vector<int> locVector1(locArray1, locArray1 + sizeof(locArray1) / sizeof(int));
  
  for(vector<Thing>::iterator it = objects.begin(); it != objects.end(); ++it) {
	
	int* locArray2p = it->getLocation();
	int locArray2[2] = {*(locArray2p), *(locArray2p+1)};
	vector<int> locVector2(locArray2, locArray2 + sizeof(locArray2) / sizeof(int));

	if (locVector1 == locVector2) {
	  unsigned int retId = it->getId();
	  ostringstream oss;
	  oss << "Found object ID " << retId << " at location (" << x << "," << y << ")";
	  string s = oss.str();
	  shiplog(s,50);
	  return retId;
	}
  }
  shiplog("No object found here",50);
  return 0;
}

// return a ref to an object with a certain ID,
// CAUTION: use with objectAt() above, or this function could go out of scope
//          without returning anything!
// TODO: Make this less dumb and dangerous to use, cf. above
Thing& Level::getObject(unsigned int id) {
  for(vector<Thing>::iterator it = objects.begin(); it != objects.end(); ++it) {
	if (it->getId() == id) {
	  shiplog("Returning a ref to an object in Level::getObject()",50);
	  return *it;
	}
  }
  shiplog("Whoops! Should not be here; we will not return correctly from Level::getObject()",1);
}

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
