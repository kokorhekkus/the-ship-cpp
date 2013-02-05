#ifndef SHIP_OBJECT
#define SHIP_OBJECT 1

#include "screenobject.h"
#include "enums.h"

#include <string>
#include <fstream>

class Thing : public ScreenObject {
private:
  unsigned int id;
  std::string name;
  inventoryType type;
  int weight;

public:
  // ALWAYS use getSerial() to get a unique serial number for the ID
  Thing(unsigned int id, std::string& name, int weight, inventoryType type,
		int xloc, int yloc,
		mapColor color, char look);
  ~Thing();

  // Getters
  unsigned int getId() const;
  std::string getName() const;
  int getWeight() const;
  inventoryType getType() const;
};

// a gun
class Gun : public Thing {
  // weapon stats
  int range;
  int dmgdice_num;
  int dmgdice_sides;
  int to_hit;

public:
  Gun(unsigned int id, std::string& name, int weight, inventoryType type,
	  int xloc, int yloc,
	  mapColor color, char look,
	  int range, int to_hit,
	  int dmgdice_num, int dmgdice_sides);
  ~Gun();
};

// Object initialisation: set up data for all potential game objects
void init_objects();

#endif
