#ifndef SHIP_LEVEL
#define SHIP_LEVEL 1

#include "map.h"
#include "object.h"
#include "enums.h"

#include <list>

// A class basically used to store a level map and the objects found on
// that level.  The Thing vector wasn't added to the LevelMap object due
// to class/header dependency hell that I am currently to lazy/stupid
// to fix
class Level {
private:
  // needs to be pointers to the base class due to object slicing
  std::list<Thing*> objects;
  LevelMap* levelMap;

  inventoryType getInventoryType(int i);

public:
  Level(LevelMap* a_levelMap);
  ~Level();

  // add a load of random items to the floor of the level, percent chance
  // to generate an item is chanceToGen
  void addFloorItems(int chanceToGen);

  // return the location of an empty map location
  int* findEmptyLocation() const;

  // return 0 if no object at location, otherwise return object ID 
  unsigned int objectAt(int x, int y);

  // return a ref to an object with a certain ID,
  // use with objectAt() above or you may not get anything back
  Thing& getObject(unsigned int id);

  // add an object to the level
  void addObject(Thing& t);

  // remove an object from the level, using its ID
  void delObject(unsigned int id);

  // print all objects on the level to the terminal
  void printObjects() const;

  // prints everything on the level
  void print() const;
};

#endif
