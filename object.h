#ifndef SHIP_OBJECT
#define SHIP_OBJECT 1

#include "base.h"
#include "enums.h"

#include <string>
#include <fstream>

class Thing : public ScreenObject {
  int id;
  std::string name;
  int weight;

public:
  Thing(int id, std::string& name, int weight,
		int xloc, int yloc,
		mapColor color, char look);
  ~Thing();

  // Getters
  int getId() const;
  std::string getName() const;
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
  Gun(int id, std::string& name, int weight,
	  int xloc, int yloc,
	  mapColor color, char look,
	  int range, int to_hit,
	  int dmgdice_num, int dmgdice_sides);
  ~Gun();
};

// Object initialisation: set up data for all potential game objects
void init_objects();

#endif
