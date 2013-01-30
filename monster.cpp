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
Monster::Monster(int a_id, string& a_name, int a_life,
				 int a_speed, int a_armour,
				 int a_weapon, int xloc, 
				 int yloc, mapColor color, char look) :
  id(a_id), name(a_name), life(a_life), speed(a_speed),
  armour(a_armour), weapon(a_weapon),
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
int Monster::getId() const { return id; }
string Monster::getName() const { return name; }
int Monster::getLife() const { return life; }
int Monster::getSpeed() const { return speed; }
int Monster::getArmour() const { return armour; }
int Monster::getWeapon() const { return weapon ; }

// Setters
void Monster::setLife(int new_life) { life = new_life; }
void Monster::setSpeed(int new_speed) { speed = new_speed; }
void Monster::setArmour(int new_armour) { armour = new_armour; }
void Monster::setWeapon(int new_weapon) { weapon = new_weapon; }

// Monster intitialisation: set up a list of starting monsters
void init_monsters() {

}
