#ifndef SHIP_LEVEL
#define SHIP_LEVEL 1

#include "map.h"
#include "object.h"

#include <vector>

// A class basically used to store a level map and the objects found on
// that level.  The Thing vector wasn't added to the LevelMap object due
// to class/header dependency hell that I am currently to lazy/stupid
// to fix

// TODO: Add a print() func that calls the LevelMap print and the printObjects()
//       call, and move levelMap back to being private
class Level {
private:
  std::vector<Thing> objects;

public:
  LevelMap* levelMap;

  Level(LevelMap* a_levelMap);
  ~Level();

  // add an object to the level
  void addObject(const Thing& t);

  // print all objects on the level to the terminal
  void printObjects() const;
};

#endif