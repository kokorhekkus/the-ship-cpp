#ifndef SHIP_MONSTER
#define SHIP_MONSTER 1

#include "map.h"
#include "base.h"

#include <string>

// An individual monster
class Monster : public ShipObject, public ScreenObject {
  short int id;
  std::string name;
  short int life;
  short int speed;
  short int armour;
  short int weapon;
  short int xloc;
  short int yloc;

public:
  // Constructor that sets all Monster variables
  Monster(short int id, std::string& name, short int life,
		  short int speed, short int armour, short int weapon,
		  short int xloc, short int yloc, mapColor color, char look);
  ~Monster();

  // Getters
  short int getId() const;
  std::string getName() const;
  short int getLife() const;
  short int getSpeed() const;
  short int getArmour() const;
  short int getWeapon() const;

  // Setters
  void setLife(short int new_life);
  void setSpeed(short int new_speed);
  void setArmour(short int new_armour);
  void setWeapon(short int new_weapon);
};

// Monster intitialisation: set up a list of starting monsters
void init_monsters();

#endif
