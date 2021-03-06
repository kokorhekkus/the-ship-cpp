#ifndef SHIP_CHARACTER
#define SHIP_CHARACTER 1

#include "map.h"
#include "screenobject.h"
#include "object.h"
#include "enums.h"

#include <list>
#include <string>

// The player
class Player : public ScreenObject {
private:
  std::string name; // max 28 characters
  playerWorld world;
  playerCareer career;

  // Primary stats
  // These can be a max of 50
  int strength;
  int intelligence;
  int constitution;
  int dexterity;
  int luck;

  // Secondary stats
  int xp;
  int xp_level; // max 99
  int hp;       // max 999
  int max_hp;   // max 999
  int armour;   // max 99
  int dodge;    // max 99
  int speed;    // max 99

  // XP level calculation array
  int xpCalcArray[100];

  // inventory: needs to be pointers to the base class due to
  //            object slicing
  std::list<Thing*> inventory;

  // used for initial generation of primary stats
  // based on homeworld and career, in constructor
  void genPrimaryStats();

  // calculates secondary stats from primary ones and inventory
  void calcSecondaryStats();

  // convert an integer to a string
  std::string itos(int i) const; 

  // print out a title for the player
  std::string title() const;

  // returns true if stat is not in the range min-max, otherwise false
  bool checkStatRange(int i, int min, int max);

  // logic to print out inventory items
  int printItems(const char* heading, inventoryType type, int position) const;

public:
  Player(std::string& name, playerWorld world, playerCareer career,
		 int xloc, int yloc,
		 mapColor color, char look);
  ~Player();

  // Getters
  std::string getName() const;
  playerWorld getWorld() const;
  playerCareer getCareer() const;
  int getStrength() const;
  int getIntelligence() const;
  int getConstitution() const;
  int getDexterity() const;
  int getLuck() const;
  int getXP() const;
  int getHP() const;
  int getMaxHP() const;
  int getArmour() const;
  int getSpeed() const;
  int getDodge() const;
  
  // Setters
  void setStrength(int new_strength);
  void setIntelligence(int new_intelligence);
  void setConstitution(int new_constitution);
  void setDexterity(int new_dexterity);
  void setLuck(int new_luck);
  void setHP(int new_hp);
  void setMaxHP(int new_max_hp);
  void setArmour(int new_armour);
  void setSpeed(int new_speed);
  void setDodge(int new_dodge);

  void addXP(int add_xp);

  // Printers
  void printMainScreenInfo() const; // print stats and name
  int printInventory() const;

  // Functionality
  int addToInv(Thing& t); // return 1 on success, 0 on failure
  void delFromInv(unsigned int id);
};

#endif
