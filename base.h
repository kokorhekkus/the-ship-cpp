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
  short int xloc;
  short int yloc;
  mapColor color; // color when visible
  char look;        // symbol to represent object on floor
    
public:
  ScreenObject(short int xloc, short int yloc, mapColor color, char look);
  virtual ~ScreenObject();

  // Getters

  // returns an array of 2 integers for [x,y]
  short int* getLocation() const;

  // Setters

  // set location by cardinal directions: equivalent to saying that the
  // object has moved e.g. north or north-east
  // returns 1 on success, 0 on error
  short int setLocation(direction direction, LevelMap level);
  
  // set location by actual coordinates
  void setLocation(short int new_xloc, short int new_yloc);
};

#endif
