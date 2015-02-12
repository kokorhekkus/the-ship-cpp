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
  // Object attributes
  unsigned int id;
  char invID;
  std::string name;
  inventoryType type;
  int weight;

  // List of available inventory letters, and a mask to indicate which are taken already,
  // for use with inventory letter assigning accents
  // -Declared static so it's a shared resource between all objects
  const static std::string invIDs;
  static std::string invIDsAvailable;
  // get an available letter to identify an object in the player's inventory
  char getNextInvID();
  

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
  char getInvID() const;

  // used when an object is added/removed to/from the inventory
  void setInventoryLetter();
  void delInventoryLetter();
};

// a weapon
class Weapon : public Thing {
  // weapon stats
  int range;
  // the following three equate to:
  // 1d6+2 : 1 = dmgdice_num, 6 = dmgdice_sides, 2 = dmg_extra
  int dmgdice_num;
  int dmgdice_sides;
  int dmg_extra;
  int to_hit;

public:
  Weapon(unsigned int id, std::string& name, int weight, inventoryType type,
		 int xloc, int yloc,
		 mapColor color, char look,
		 int range, int to_hit,
		 int dmgdice_num, int dmgdice_sides, int dmg_extra);
  ~Weapon();
};

// a piece of armour
class Armour : public Thing {
  // armour stats
  int modArmour;
  int modDodge;

public:
  Armour(unsigned int id, std::string& name, int weight, inventoryType type,
	  int xloc, int yloc,
	  mapColor color, char look,
	  int modArmour, int modDodge);
  ~Armour();
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

  std::vector<std::string> adjectivesGun;
  std::vector<std::string> adjectivesArmour;

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
