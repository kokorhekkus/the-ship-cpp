#ifndef SHIP_OBJECT
#define SHIP_OBJECT 1

#include "map.h"
#include "base.h"
#include "enums.h"

#include <string>
#include <fstream>

class Thing : public ShipObject, public ScreenObject {
  short int id;
  std::string name;
  short int weight;

public:
  Thing(short int id, std::string& name, short int weight,
		short int xloc, short int yloc,
		mapColor color, char look);
  ~Thing();

  // Getters
  short int getId() const;
  std::string getName() const;
  short int getWeight() const;
};

// a gun
class Gun : public Thing {
  // weapon stats
  short int range;
  short int dmgdice_num;
  short int dmgdice_sides;
  short int to_hit;

public:
  Gun(short int id, std::string& name, short int weight,
	  short int xloc, short int yloc,
	  mapColor color, char look,
	  short int range, short int to_hit,
	  short int dmgdice_num, short int dmgdice_sides);
  ~Gun();
};

// Object initialisation: create a set of starting objects
void init_objects();

#endif
