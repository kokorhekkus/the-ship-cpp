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
  short int strength;
  short int intelligence;
  short int constitution;
  short int dexterity;
  short int luck;

  // Secondary stats
  short int xp;
  short int xp_level; // max 99
  short int hp;       // max 999
  short int max_hp;       // max 999
  short int armour;   // max 99
  short int dodge;    // max 99
  short int speed;    // max 99

  // inventory
  std::vector<Thing> inventory;

  // used for initial generation of primary stats
  // based on homeworld and career, in constructor
  void genPrimaryStats();

  // calculates secondary stats from primary ones
  void calcSecondaryStats();

  // convert an integer to a string
  std::string itos(int i); 

  // print out a title for the player
  std::string title();

public:
  Player(char* name, playerWorld world, playerCareer career,
		 short int xloc, short int yloc,
		 mapColor color, char look);
  ~Player();

  // Getters
  char* getName() const;
  playerWorld getWorld() const;
  playerCareer getCareer() const;
  short int getStrength() const;
  short int getIntelligence() const;
  short int getConstitution() const;
  short int getDexterity() const;
  short int getLuck() const;
  short int getXP() const;
  short int getHP() const;
  short int getMaxHP() const;
  short int getArmour() const;
  short int getSpeed() const;
  short int getDodge() const;
  
  // Setters
  void setStrength(short int new_strength);
  void setIntelligence(short int new_intelligence);
  void setConstitution(short int new_constitution);
  void setDexterity(short int new_dexterity);
  void setLuck(short int new_luck);
  void setHP(short int new_hp);
  void setMaxHP(short int new_max_hp);
  void setArmour(short int new_armour);
  void setSpeed(short int new_speed);
  void setDodge(short int new_dodge);

  void addXP(short int add_xp);

  // Printers
  void printMainScreenInfo(); // print stats and name
  void print(); // prints actual pc to the terminal

  // Functionality
  void addToInventory(const Thing& t);  
};

#endif
