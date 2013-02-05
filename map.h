#ifndef SHIP_MAP
#define SHIP_MAP 1

#include "screenobject.h"
#include "engine.h"
#include "enums.h"
#include "config.h"

// a character to be displayed on the map
struct MapChar {
  levelFeature id;
  char symbol;
  mapColor color;

  MapChar();
  MapChar(levelFeature id, char symbol, mapColor color);
  ~MapChar();
};

// initialise a list of map drawing characters
extern MapChar mapDrawingChars[8];
void initMapDrawingChars();

// a representation of a single level
class LevelMap {
private:
  // level ID
  int depth;
  mapBranch branch;

  // x,y locations of map drawing characters held
  // in a multidimensional array
  //
  // TODO: account for terminals of different sizes
  MapChar levelMap[xTerminalSize][yTerminalSize];

  // write a single feature to a location on the level
  void writeFeature(int x, int y, levelFeature feature);

public:
  LevelMap(int depth, mapBranch branch);
  ~LevelMap();

  // functions to draw stuff
  void makeRoom(roomType type, int x_start, int y_start,
				 int x_length, int y_length);

  void generate(int depth, levelType type);

  // returns the feature at the given location
  levelFeature at(int x, int y) const;

  // print out the level to terminal
  void print() const;

  // Getters
  int getDepth() const;
  mapBranch getBranch() const;
};

#endif
