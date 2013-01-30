#ifndef SHIP_MONSTER
#define SHIP_MONSTER 1

#include "map.h"
#include "base.h"
#include "enums.h"

#include <string>

// An individual monster
class Monster : public ScreenObject {
private:
  int id;
  std::string name;
  int life;
  int speed;
  int armour;
  int weapon;
  int xloc;
  int yloc;

public:
  // Constructor that sets all Monster variables
  Monster(int id, std::string& name, int life,
		  int speed, int armour, int weapon,
		  int xloc, int yloc, mapColor color, char look);
  ~Monster();

  // Getters
  int getId() const;
  std::string getName() const;
  int getLife() const;
  int getSpeed() const;
  int getArmour() const;
  int getWeapon() const;

  // Setters
  void setLife(int new_life);
  void setSpeed(int new_speed);
  void setArmour(int new_armour);
  void setWeapon(int new_weapon);
};

// Monster intitialisation: set up a list of starting monsters
void init_monsters();

#endif
