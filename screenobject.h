#ifndef SHIP_SCREENOBJECT
#define SHIP_SCREENOBJECT 1

#include "enums.h"
#include "map.h"

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

  // returns location
  int* getLocation() const; // returns an array [x,y]
  int getX() const;
  int getY() const;

  // Setters

  // set location by cardinal directions: equivalent to saying that the
  // object has moved e.g. north or north-east
  // returns 1 on success, 0 on error
  int setLocation(direction direction, const LevelMap& level);
  
  // set location by actual coordinates
  void setLocation(int new_xloc, int new_yloc);

  // prints object to the terminal
  virtual void print() const; 
};

#endif
