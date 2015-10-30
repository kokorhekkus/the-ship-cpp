// Level implementation

#include "level.h"
#include "log.h"
#include "random.h"
#include "config.h"
#include "object.h"

#include <sstream>
#include <algorithm>

using namespace std;

//----------------------------------------------------------------------
// LevelMap class implementation
//----------------------------------------------------------------------

Level::Level(LevelMap* a_levelMap) : levelMap(a_levelMap) {
  shiplog("Creating a new Level object",10);
}

Level::~Level() {
	shiplog("Destroying a Level object",10);
}

// add a load of random items to the floor of the level
void Level::addFloorItems(int chanceToGen) {
	shiplog("Adding random floor items",10);

	ThingMaker tm;
	tm.initThings();

	// Go through all empty spaces on map and have a chance of creating an object there
	for (int x = xMinMapSize; x < xMaxMapSize; x++) {
	for (int y = yMinMapSize; y < yMaxMapSize; y++) {
		if (levelMap->at(x,y) == FLOOR) {
			if (percentChance(chanceToGen)) {
				int objType = inRange(0,5);
				Thing* thing = tm.instantiate(getInventoryType(objType),x,y);
				this->addObject(*thing);
			}
		}
	}
	}
}

// find a random empty map location (i.e. floor only)
int* Level::findEmptyLocation() const {
	// TODO: will this cause a memory leak..? no cleanup
	// of array
	int* location_array = new int[2];
	int x, y;
	for(;;) {
		x = inRange(xMinMapSize,xMaxMapSize);
		y = inRange(yMinMapSize,yMaxMapSize);
		if (levelMap->at(x,y) == FLOOR) {
			break;
		}
	}
	location_array[0] = x;
	location_array[1] = y;
	return location_array;
}

// return 0 if no object at location, otherwise return object ID 
unsigned int Level::objectAt(int x, int y) {
  // we can easily compare lists, so convert from arrays
  // (easy to initialise a list from an array)
  int locArray1[2] = {x, y};
  list<int> locList1(locArray1, locArray1 + sizeof(locArray1) / sizeof(int));
  
  for(list<Thing*>::iterator it = objects.begin(); it != objects.end(); ++it) {
	
	int* locArray2p = (*it)->getLocation();
	int locArray2[2] = {*(locArray2p), *(locArray2p+1)};
	list<int> locList2(locArray2, locArray2 + sizeof(locArray2) / sizeof(int));

	if (locList1 == locList2) {
	  unsigned int retId = (*it)->getId();
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
  for(list<Thing*>::iterator it = objects.begin(); it != objects.end(); ++it) {
	if ((*it)->getId() == id) {
	  shiplog("Returning a ref to an object in Level::getObject()",50);
	  return *(*it);
	}
  }
  shiplog("Whoops! Should not be here; we will not return correctly from Level::getObject()",1);
}

// add an object to the level
void Level::addObject(Thing& t) {
  objects.push_back(&t);
}

// remove an object from the level
void Level::delObject(unsigned int id) {
  shiplog("->Level::delObject",60);
  for(list<Thing*>::iterator it = objects.begin(); it != objects.end(); ++it) {
	if ((*it)->getId() == id) {
	  shiplog("Found matching object",60);
	  objects.erase(it);
	  shiplog("Erased object from level",60);
	  // must return, as erasing an element will break the iteration
	  // over the rest of the list
	  return;
	}
  }
  shiplog("<-Level::delObject",60);
}

// print all objects on the level to the terminal
void Level::printObjects() const {
  for(list<Thing*>::const_iterator it = objects.begin(); it != objects.end(); ++it) {
	(*it)->print();
  }
}

// prints everything on the level
void Level::print() const {
  levelMap->print();
  printObjects();
}

// convert an integer to an inventoryType enum
inventoryType Level::getInventoryType(int i) {
  switch (i) {
    case 0:
      return LRW;
      break;
    case 1:
      return SRW;
      break;
    case 2:
      return BODY;
      break;
    case 3:
      return HEAD;
      break;
    case 4:
      return LEG;
      break;
    case 5:
      return FOOT;
      break;
  }
}