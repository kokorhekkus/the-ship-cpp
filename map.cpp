// Map implementation

#include "map.h"
#include "log.h"

#include <vector>
using namespace std;

MapChar mapDrawingChars[8]; // declared extern in the header 

void initMapDrawingChars() {

  MapChar blank(BLANK, '\0', WHITE);
  MapChar wall(WALL, '#', D_GREY);
  MapChar floor(FLOOR, '.', L_GREY);
  MapChar grass(GRASS, '.', GREEN);
  MapChar ustair(USTAIR, '<', WHITE);
  MapChar dstair(DSTAIR, '>', WHITE);
  MapChar cdoor(CDOOR, '+', WHITE);
  MapChar odoor(ODOOR, '/', WHITE);

  mapDrawingChars[BLANK] = blank;
  mapDrawingChars[WALL] = wall;
  mapDrawingChars[FLOOR] = floor;
  mapDrawingChars[GRASS] = grass;
  mapDrawingChars[USTAIR] = ustair;
  mapDrawingChars[DSTAIR] = dstair;
  mapDrawingChars[CDOOR] = cdoor;
  mapDrawingChars[ODOOR] = odoor;
}

//----------------------------------------------------------------------
// MapChar class implementation
//----------------------------------------------------------------------
MapChar::MapChar() {}

MapChar::MapChar(levelFeature a_id, char a_symbol, mapColor a_color) :
  id(a_id), symbol(a_symbol), color(a_color) {}

MapChar::~MapChar() {}

//----------------------------------------------------------------------
// LevelMap class implementation
//----------------------------------------------------------------------
LevelMap::LevelMap() {
  // create a blank map for an 80x24 screen
  for (int x = 0; x < 80; x++) {
	for (int y = 0; y < 24; y++) {
	  levelMap[x][y] = mapDrawingChars[BLANK];
	}
  }
  string msg = "Creating new LevelMap object";
  shiplog(msg, 10);
}

LevelMap::~LevelMap() {}

void LevelMap::makeRoom (roomType type, short int x_start, short int y_start,
						 short int x_length, short int y_length) {
  if (type == SQUARE) {
	// top left hand corner at [x_start, y_start]
	// (write floorspace within the 'solid' level)
	for (int i = 0; i < y_length; i++) {
	  levelMap[x_start + i][y_start] = mapDrawingChars[FLOOR];
	}
	for (int i = 0; i < x_length; i++) {
	  levelMap[x_start][y_start + i] = mapDrawingChars[FLOOR];
	}
  }
}

void LevelMap::generate(short int depth, levelType type) {

}

// returns the feature at the given location
levelFeature LevelMap::at(short int x, short int y) {
  return levelMap[x][y].id;
}
