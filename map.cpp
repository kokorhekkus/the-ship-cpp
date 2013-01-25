// Map implementation

#include "map.h"
#include "log.h"
#include "engine.h"

#include <vector>
using namespace std;

MapChar mapDrawingChars[8]; // declared extern in the header 

void initMapDrawingChars() {

  MapChar wall(WALL, '#', D_GREY);
  MapChar floor(FLOOR, '.', L_GREY);
  MapChar grass(GRASS, '.', GREEN);
  MapChar ustair(USTAIR, '<', WHITE);
  MapChar dstair(DSTAIR, '>', WHITE);
  MapChar cdoor(CDOOR, '+', WHITE);
  MapChar odoor(ODOOR, '/', WHITE);

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
  // (do not fill bits where there is screen furniture)
  for (int x = 0; x < 72; x++) {
	for (int y = 2; y < 22; y++) {
	  levelMap[x][y] = mapDrawingChars[WALL];
	}
  }
  string msg = "Creating new LevelMap object";
  shiplog(msg, 10);
}

LevelMap::~LevelMap() {}

// write a single feature to a location on the level
void LevelMap::writeFeature(short int x, short int y, levelFeature feature) {
  levelMap[x][y] = mapDrawingChars[feature];
}

void LevelMap::makeRoom (roomType type, short int x_start, short int y_start,
						 short int x_length, short int y_length) {
  switch(type) {
  case SQUARE:
	// top left hand corner at [x_start, y_start]
	// (write floorspace within the 'solid' level)
	for (int x = 0; x < x_length; x++) {
	  for (int y = 0; y < y_length; y++) {
		levelMap[x_start + x][y_start + y] = mapDrawingChars[FLOOR];
	  }
	}
	break;
  case ROUND:
	// TODO
	break;
  }

}

void LevelMap::generate(short int depth, levelType type) {
  makeRoom(SQUARE, 10, 10, 4, 4);
}

// returns the feature at the given location
levelFeature LevelMap::at(short int x, short int y) {
  return levelMap[x][y].id;
}

// print out the level to terminal
void LevelMap::print() {
  for (int x = 0; x < 72; x++) {
	for (int y = 2; y < 22; y++) {
	  write_char(x, y, levelMap[x][y].symbol, levelMap[x][y].color);
	}
  }
}
