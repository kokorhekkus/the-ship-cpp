#ifndef SHIP_MAP
#define SHIP_MAP 1

#include "base.h"
#include "engine.h"
#include "enums.h"

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
  // X,Y locations of map drawing characters held
  // in a multidimensional array
  //
  // TODO: account for terminals of different sizes
  MapChar levelMap[80][24];

public:
  LevelMap();
  ~LevelMap();

  // functions to draw stuff
  void makeRoom(roomType type, short int x_start, short int y_start,
				 short int x_length, short int y_length);

  void generate(short int depth, levelType type);

  // returns the feature at the given location
  levelFeature at(short int x, short int y);
};

#endif
