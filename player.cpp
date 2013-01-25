// The Player Character

#include "player.h"
#include "log.h"
#include "engine.h"

#include <boost/lexical_cast.hpp>

#include <ncurses.h>

#include <string>

using namespace std;

//----------------------------------------------------------------------
// Player class implementation
//----------------------------------------------------------------------

// Constructor that sets all Player variables
Player::Player(char* a_name, playerWorld a_world, playerCareer a_career,
			   short int xloc, short int yloc, 
			   mapColor color, char look) :
  name(a_name), world(a_world), career(a_career),
  ScreenObject(xloc, yloc, color, look) {

  string msg = "Creating new Player object";
  shiplog(msg, 10);
  genPrimaryStats();
  calcSecondaryStats();
  // TODO: generate starting inventory
}
Player::~Player() {
  string msg = "Destroying Player object";
  shiplog(msg, 10);
}

// Getters
char* Player::getName() const { return name; }
playerWorld Player::getWorld() const { return world; }
playerCareer Player::getCareer() const { return career; }
short int Player::getStrength() const { return strength; }
short int Player::getIntelligence() const { return intelligence; }
short int Player::getConstitution() const { return constitution; }
short int Player::getDexterity() const { return dexterity; }
short int Player::getLuck() const { return luck; }
short int Player::getXP() const { return xp; }
short int Player::getHP() const { return hp; }
short int Player::getMaxHP() const { return max_hp; }
short int Player::getArmour() const { return armour; }
short int Player::getSpeed() const { return speed; }
short int Player::getDodge() const { return dodge; }

// Setters
void Player::setStrength(short int new_strength) {
  strength = new_strength;
  calcSecondaryStats();
}
void Player::setIntelligence(short int new_intelligence) {
  intelligence = new_intelligence;
  calcSecondaryStats();
}
void Player::setConstitution(short int new_constitution) {
  constitution = new_constitution;
  calcSecondaryStats();
}
void Player::setDexterity(short int new_dexterity) {
  dexterity = new_dexterity;
  calcSecondaryStats();
}
void Player::setLuck(short int new_luck) {
  luck = new_luck;
  calcSecondaryStats();
}
void Player::setXP(short int new_xp) { xp = new_xp; }
void Player::setHP(short int new_hp) { hp = new_hp; }
void Player::setMaxHP(short int new_max_hp) { max_hp = new_max_hp; }
void Player::setArmour(short int new_armour) { armour = new_armour; }
void Player::setSpeed(short int new_speed) { speed = new_speed; }
void Player::setDodge(short int new_dodge) { dodge = new_dodge; }
 
string Player::itos(int i) {
   stringstream ss;
   ss << i;
   return ss.str();
}

void Player::printMainScreenInfo() {

  // Primary stats
  string s = itos(strength);
  char* sc = (char*)s.c_str(); 
  write_string(77, 3, sc, L_BLUE);

  s = itos(intelligence);
  sc = (char*)s.c_str(); 
  write_string(77, 5, sc, L_BLUE);

  s = itos(dexterity);
  sc = (char*)s.c_str(); 
  write_string(77, 7, sc, L_BLUE);

  s = itos(constitution);
  sc = (char*)s.c_str(); 
  write_string(77, 9, sc, L_BLUE);

  s = itos(luck);
  sc = (char*)s.c_str(); 
  write_string(77, 11, sc, L_BLUE);

  // Secondary stats
  s = itos(hp);
  sc = (char*)s.c_str(); 
  write_string(29, 23, sc, L_BLUE);

  s = itos(max_hp);
  sc = (char*)s.c_str(); 
  write_string(33, 23, sc, L_BLUE);

  s = itos(xp_level);
  sc = (char*)s.c_str(); 
  write_string(43, 23, sc, L_BLUE);

  s = itos(speed);
  sc = (char*)s.c_str(); 
  write_string(52, 23, sc, L_BLUE);

  s = itos(armour);
  sc = (char*)s.c_str(); 
  write_string(62, 23, sc, L_BLUE);

  s = itos(dodge);
  sc = (char*)s.c_str(); 
  write_string(71, 23, sc, L_BLUE);

  // Print name
  write_string(0, 22, name, MAGENTA);
  
  s = title();
  sc = (char*)s.c_str();
  write_string(0, 23, sc, MAGENTA);
}

// TODO: -Change title based on experience
//       -Ensure a limit of 28 characters
string Player::title() {
  string title;
  
  switch(world) {
  case EARTH:
	title.append("Terran ");
	break;
  case NEWBEIJING:
	title.append("Beijinger ");
	break;
  case SPARTA:
	title.append("Spartan ");
	break;
  }

  switch(career) {
  case COMMANDO:
	title.append("Commando");
	break;
  case MEDIC:
	title.append("Medic");
	break;
  case SAPPER:
	title.append("Sapper");
	break;
  case SCOUT:
	title.append("Scout");
	break;
  case TECHNICIAN:
	title.append("Technician");
	break;
  case HIGHCOMMAND:
	title.append("General");
	break;
  case ENGINEER:
	title.append("Engineer");
	break;
  }

  return title;
} 


void Player::genPrimaryStats() {
  strength = 10;
  intelligence = 10;
  constitution = 10;
  dexterity = 10;
  luck = 10;
}

void Player::calcSecondaryStats() {
  xp = 0;
  xp_level = 1;
  hp = 20;
  max_hp = 20;
  armour = 5;
  dodge = 5;
  speed = 10;
}

void Player::addToInventory(const Thing& t) {
  inventory.push_back(t);
}
