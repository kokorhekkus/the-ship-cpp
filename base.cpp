// Base classes that many classes in The Ship inherit from

#include "base.h"
#include "engine.h"

#include <string>
using namespace std;

//----------------------------------------------------------------------
// ShipObject class implementation
//----------------------------------------------------------------------
ShipObject::ShipObject() {}
ShipObject::~ShipObject() {}

//----------------------------------------------------------------------
// ScreenObject class implementation
//----------------------------------------------------------------------
ScreenObject::ScreenObject(int a_xloc, int a_yloc, 
						   mapColor a_color, char a_look) :
  xloc(a_xloc), yloc(a_yloc), color(a_color), look(a_look) {}
ScreenObject::~ScreenObject() {}

// Getters
int* ScreenObject::getLocation() const {
  // TODO: will this cause a memory leak..? no cleanup
  // of array
  int* location_array = new int[2];
  location_array[0] = xloc;
  location_array[1] = yloc;
  return location_array;
}

// Setters

// set location by actual coordinates
void ScreenObject::setLocation(int new_xloc, int new_yloc) {
  // TODO: ensure we aren't in a wall or some other tile that can only
  // hold one thing
  xloc = new_xloc;
  yloc = new_yloc;
}

// set location by cardinal directions: equivalent to saying that the
// object has moved e.g. north, south-east, etc
// 
// returns 1 for a successful move, 0 for a failed move
int ScreenObject::setLocation(direction direction, LevelMap level) {
  // calculate new co-ords, then check if it's OK to move to there
  int* new_location = new int[2];
  int new_yloc = yloc;
  int new_xloc = xloc;

  switch (direction) {
  case NORTH:
	new_yloc++;
	break;
  case NORTHEAST:
	new_xloc++; new_yloc++;
	break;
  case EAST:
	new_xloc++;
	break;
  case SOUTHEAST:
	new_xloc++; new_yloc--;
	break;
  case SOUTH:
	new_yloc--;
	break;
  case SOUTHWEST:
	new_xloc--; new_yloc--;
	break;
  case WEST:
	new_xloc--;
	break;
  case NORTHWEST:
	new_xloc--; new_yloc++;
	break;
  default:
	string msg = "setLocation called with incorrect direction ";
	error_exit(msg);
  }

  // check to make sure we are not going to place this object in
  // a space it cannot occupy on the level map
  //
  // TODO: needs a lot more work
  if (level.at(new_xloc, new_yloc) == WALL) {
	return 0;
  }
  
  xloc = new_xloc;
  yloc = new_yloc;

  new_location[0] = new_xloc;
  new_location[1] = new_yloc;
  return 1;
}
