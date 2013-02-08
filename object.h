#ifndef SHIP_OBJECT
#define SHIP_OBJECT 1

#include "screenobject.h"
#include "enums.h"

#include <string>
#include <fstream>
#include <vector>

// Base class for all objects in the game
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
class Weapon : public Thing {
  // weapon stats
  int range;
  int dmgdice_num;
  int dmgdice_sides;
  int to_hit;

public:
  Weapon(unsigned int id, std::string& name, int weight, inventoryType type,
	  int xloc, int yloc,
	  mapColor color, char look,
	  int range, int to_hit,
	  int dmgdice_num, int dmgdice_sides);
  ~Weapon();
};

// Object initialiser, contains all the data we need to
// instantiate every actual object in the game
class ThingMaker {
private:
  unsigned int objectSerial;
  std::vector<std::string> LRWDat;
  std::vector<std::string> SRWDat;
  std::vector<std::string> BodyDat;
  std::vector<std::string> HeadDat;
  std::vector<std::string> LegDat;
  std::vector<std::string> FootDat;
  std::vector<std::string> AmmoDat;

  // use this to assign a unique serial number to game objects
  unsigned int getSerial();

  // convert an integer to a mapColor enum
  mapColor getMapColor(int i);

public:
  ThingMaker();
  ~ThingMaker();

  // set up the vector of condensed information on objects
  void initThings();

  // actually create an object
  Thing* instantiate(inventoryType type, int xloc, int yloc);
};

#endif
