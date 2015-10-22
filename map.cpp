// Map implementation

#include "map.h"
#include "log.h"
#include "random.h"
#include "enums.h"

#include <vector>
#include <sstream>

using namespace std;

MapChar mapDrawingChars[8];

void initMapDrawingChars() {
  shiplog("Initialising map drawing characters...",1);

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

void LevelMap::makeSquareRoom(int x_start, int y_start, int x_length, int y_length) {
  // top left hand corner at [x_start, y_start]
  // (write floorspace within the 'solid' level)
  for (int x = 0; x < x_length; x++) {
    for (int y = 0; y < y_length; y++) {
    levelMap[x_start + x][y_start + y] = mapDrawingChars[FLOOR];
    }
  } 
}

void LevelMap::makeRoundRoom(int x_start, int y_start, int x_length, int y_length) {

}

void LevelMap::makeCavernLevel() {
  // variables
  int initialWallFill = 35;
  int changeCutoff1 = 5; //make any tile a wall if surrounded by n adjacent wall tiles
  int changeCutoff2 = 3; //leave a wall tile a wall if surrounded by n adjacent wall tiles
  int generations = 5;

  // Fill map with random wall or floor
  for (int x = xMinMapSize; x < xMaxMapSize; x++) {
  for (int y = yMinMapSize; y < yMaxMapSize; y++) {
    if (percentChance(initialWallFill)) {
      levelMap[x][y] = mapDrawingChars[WALL];
    } else {
      levelMap[x][y] = mapDrawingChars[FLOOR];
    }
  }
  }

  // run cellular automata
  for (int n=0; n<generations; n++) {

    for (int x = xMinMapSize; x < xMaxMapSize; x++) {
    for (int y = yMinMapSize; y < yMaxMapSize; y++) {
      // get adjacent wall tiles for element
      int adjWallCount = 0;
      for (int i=-1;i<=1; i++) {
      for (int j=-1;j<=1; j++) {
        if (levelMap[x+i][y+j].id != FLOOR) {
          adjWallCount++;
        }
      }
      }

      // set tiles
      if (adjWallCount >= changeCutoff1) {
        levelMap[x][y] = mapDrawingChars[WALL];
      } else {
        if (levelMap[x][y].id == WALL && adjWallCount >= changeCutoff2) {
          levelMap[x][y] = mapDrawingChars[WALL];
        } else {
          levelMap[x][y] = mapDrawingChars[FLOOR];
        }
      }
    }
    }
  }

  // make map edges solid
  for (int xx = xMinMapSize; xx < xMaxMapSize; xx++) {
    levelMap[xx][yMinMapSize] = mapDrawingChars[WALL];
    levelMap[xx][yMaxMapSize-1] = mapDrawingChars[WALL];
  }
  for (int yy = yMinMapSize; yy < yMaxMapSize; yy++) {
    levelMap[xMinMapSize][yy] = mapDrawingChars[WALL];
    levelMap[xMaxMapSize-1][yy] = mapDrawingChars[WALL];
  }
}

void LevelMap::generate(int depth, levelType type) {
  if (type = CAVERN) {
    makeCavernLevel(); 
  }
  if (type = CORRIDORS) {
    makeSquareRoom(10, 10, 4, 4);
  }
  
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


