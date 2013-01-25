#ifndef SHIP_CHARACTER
#define SHIP_CHARACTER 1

#include "map.h"
#include "base.h"
#include "object.h"
#include "enums.h"

#include <string>
#include <vector>

// The player
class Player : public ShipObject, public ScreenObject {
private:
  char* name; // max 28 characters
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
  int max_hp;       // max 999
  int armour;   // max 99
  int dodge;    // max 99
  int speed;    // max 99

  // inventory
  std::vector<Thing> inventory;

  // used for initial generation of primary stats
  // based on homeworld and career, in constructor
  void genPrimaryStats();

  // calculates secondary stats from primary ones
  void calcSecondaryStats();

  // convert an integer to a string
  std::string itos(int i) const; 

  // print out a title for the player
  std::string title() const;

  // returns 0 if stat is not in the range min-max, otherwise 1
  int checkStatRange(int i, int min, int max);

public:
  Player(char* name, playerWorld world, playerCareer career,
		 int xloc, int yloc,
		 mapColor color, char look);
  ~Player();

  // Getters
  char* getName() const;
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
  void print() const; // prints actual pc to the terminal

  // Functionality
  void addToInventory(const Thing& t);  
};

#endif
