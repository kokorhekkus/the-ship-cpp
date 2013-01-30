// Map implementation

#include "map.h"
#include "log.h"

#include <vector>
#include <sstream>
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
// MapChar struct implementation
//----------------------------------------------------------------------
MapChar::MapChar() {}

MapChar::MapChar(levelFeature a_id, char a_symbol, mapColor a_color) :
  id(a_id), symbol(a_symbol), color(a_color) {}

MapChar::~MapChar() {}

//----------------------------------------------------------------------
// LevelMap class implementation
//----------------------------------------------------------------------
LevelMap::LevelMap(int a_depth, mapBranch a_branch) :
  depth(a_depth), branch(a_branch) {
  
  // create a blank map for an 80x24 screen
  // (do not fill bits where there is screen furniture)
  for (int x = xMinMapSize; x < xMaxMapSize; x++) {
	for (int y = yMinMapSize; y < yMaxMapSize; y++) {
	  levelMap[x][y] = mapDrawingChars[WALL];
	}
  }

  ostringstream oss;
  oss << "Creating new LevelMap object of depth " << depth << " branch " << branch;
  string s = oss.str();
  shiplog(s, 10);
}

LevelMap::~LevelMap() {
  ostringstream oss;
  oss << "Destroying LevelMap object of depth " << depth << " branch " << branch;
  string s = oss.str();
  shiplog(s, 10);
}

// write a single feature to a location on the level
void LevelMap::writeFeature(int x, int y, levelFeature feature) {
  levelMap[x][y] = mapDrawingChars[feature];
}

void LevelMap::makeRoom (roomType type, int x_start, int y_start,
						 int x_length, int y_length) {
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

void LevelMap::generate(int depth, levelType type) {
  makeRoom(SQUARE, 10, 10, 4, 4);
}

// returns the feature at the given location
levelFeature LevelMap::at(int x, int y) const {
  return levelMap[x][y].id;
}

// print out the level to terminal
void LevelMap::print() const {
  for (int x = xMinMapSize; x < xMaxMapSize; x++) {
	for (int y = yMinMapSize; y < yMaxMapSize; y++) {
	  write_char(x, y, levelMap[x][y].symbol, levelMap[x][y].color);
	}
  }
}

int LevelMap::getDepth() const {
  return depth;
}
mapBranch LevelMap::getBranch() const {
  return branch;
}
