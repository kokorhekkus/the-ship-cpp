#ifndef SHIP_LEVEL
#define SHIP_LEVEL 1

#include "map.h"
#include "object.h"

#include <vector>

// A class basically used to store a level map and the objects found on
// that level.  The Thing vector wasn't added to the LevelMap object due
// to class/header dependency hell that I am currently to lazy/stupid
// to fix
class Level {
private:
  std::vector<Thing> objects;
  LevelMap* levelMap;

public:

  Level(LevelMap* a_levelMap);
  ~Level();

  // add an object to the level
  void addObject(const Thing& t);

  // remove an object from the level
  void delObject(const Thing& t);

  // print all objects on the level to the terminal
  void printObjects() const;

  // prints everything on the level
  void print() const;
};

#endif
