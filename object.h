#ifndef SHIP_OBJECT
#define SHIP_OBJECT 1

#include "base.h"
#include "enums.h"

#include <fstream>

class Thing : public ScreenObject {
private:
  unsigned int id;
  char* name;
  int weight;

public:
  // ALWAYS use getSerial() to get a unique serial number for the ID
  Thing(unsigned int id, char* name, int weight,
		int xloc, int yloc,
		mapColor color, char look);
  ~Thing();

  // Getters
  unsigned int getId() const;
  char* getName() const;
  int getWeight() const;
};

// a gun
class Gun : public Thing {
  // weapon stats
  int range;
  int dmgdice_num;
  int dmgdice_sides;
  int to_hit;

public:
  Gun(unsigned int id, char* name, int weight,
	  int xloc, int yloc,
	  mapColor color, char look,
	  int range, int to_hit,
	  int dmgdice_num, int dmgdice_sides);
  ~Gun();
};

// Object initialisation: set up data for all potential game objects
void init_objects();

#endif
