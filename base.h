#ifndef SHIP_BASE
#define SHIP_BASE 1

#include "enums.h"
#include "map.h"

// The base class for all classes in The Ship
// Doesn't do anything yet
class ShipObject {
public:
  ShipObject();
  virtual ~ShipObject();
};

// forward declaration
class LevelMap;

// The base class for all displayable objects in The Ship
class ScreenObject {
protected:
  int xloc;
  int yloc;
  mapColor color; // color when visible
  char look;        // symbol to represent object on floor
    
public:
  ScreenObject(int xloc, int yloc, mapColor color, char look);
  virtual ~ScreenObject();

  // Getters

  // returns an array of 2 integers for [x,y]
  int* getLocation() const;

  // Setters

  // set location by cardinal directions: equivalent to saying that the
  // object has moved e.g. north or north-east
  // returns 1 on success, 0 on error
  int setLocation(direction direction, LevelMap level);
  
  // set location by actual coordinates
  void setLocation(int new_xloc, int new_yloc);
};

#endif
