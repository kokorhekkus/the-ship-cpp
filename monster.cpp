// Monsters

#include "monster.h"
#include "log.h"

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

//----------------------------------------------------------------------
// Monster class implementation
//----------------------------------------------------------------------

// Constructor that sets all Monster variables
Monster::Monster(short int a_id, string& a_name, short int a_life,
				 short int a_speed, short int a_armour,
				 short int a_weapon, short int xloc, 
				 short int yloc, mapColor color, char look) :
  id(a_id), name(a_name), life(a_life), speed(a_speed),
  armour(a_armour), weapon(a_weapon),
  ShipObject(),
  ScreenObject(xloc, yloc, color, look) {

  string s = "Creating new Monster object with id ";
  ostringstream oss;
  oss << id;
  s.append(oss.str());
  shiplog(s, 10);
}
Monster::~Monster() {
  string s = "Destroying Monster object with id ";
  ostringstream oss;
  oss << id;
  s.append(oss.str());
  shiplog(s, 10);
}

// Getters
short int Monster::getId() const { return id; }
string Monster::getName() const { return name; }
short int Monster::getLife() const { return life; }
short int Monster::getSpeed() const { return speed; }
short int Monster::getArmour() const { return armour; }
short int Monster::getWeapon() const { return weapon ; }

// Setters
void Monster::setLife(short int new_life) { life = new_life; }
void Monster::setSpeed(short int new_speed) { speed = new_speed; }
void Monster::setArmour(short int new_armour) { armour = new_armour; }
void Monster::setWeapon(short int new_weapon) { weapon = new_weapon; }

// Monster intitialisation: set up a list of starting monsters
void init_monsters() {

}
