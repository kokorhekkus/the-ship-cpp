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
			   int xloc, int yloc, 
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
int Player::getStrength() const { return strength; }
int Player::getIntelligence() const { return intelligence; }
int Player::getConstitution() const { return constitution; }
int Player::getDexterity() const { return dexterity; }
int Player::getLuck() const { return luck; }
int Player::getXP() const { return xp; }
int Player::getHP() const { return hp; }
int Player::getMaxHP() const { return max_hp; }
int Player::getArmour() const { return armour; }
int Player::getSpeed() const { return speed; }
int Player::getDodge() const { return dodge; }

// Setters
void Player::setStrength(int new_strength) {
  if (checkStatRange(new_strength,1,50)) {
	strength = new_strength;
	calcSecondaryStats();
  } else {
	string msg = "STR not in range; not setting";
	shiplog(msg,5);
  }
}
void Player::setIntelligence(int new_intelligence) {
  if (checkStatRange(new_intelligence,1,50)) {
	intelligence = new_intelligence;
	calcSecondaryStats();
  } else {
	string msg = "INT not in range; not setting";
	shiplog(msg,5);
  }
}
void Player::setConstitution(int new_constitution) {
  if (checkStatRange(new_constitution,1,50)) {
	constitution = new_constitution;
	calcSecondaryStats();
  } else {
	string msg = "CON not in range; not setting";
	shiplog(msg,5);
  }
}
void Player::setDexterity(int new_dexterity) {
  if (checkStatRange(new_dexterity,1,50)) {
	dexterity = new_dexterity;
	calcSecondaryStats();
  } else {
	string msg = "DEX not in range; not setting";
	shiplog(msg,5);
  }
}
void Player::setLuck(int new_luck) {
  if (checkStatRange(new_luck,1,50)) {
	luck = new_luck;
	calcSecondaryStats();
  } else {
	string msg = "LCK not in range; not setting";
	shiplog(msg,5);
  }
}
void Player::addXP(int add_xp) {
  xp = xp + add_xp;
  // TODO: set xp_level appropriately
}
void Player::setHP(int new_hp) {
  if (checkStatRange(new_hp,1,max_hp)) {
	hp = new_hp;
  } else {
	// TODO: handle death when hp goes below 1
  }
}
void Player::setMaxHP(int new_max_hp) {
  if (checkStatRange(new_max_hp,1,999)) {
	max_hp = new_max_hp;
  } else {
	string msg = "Max HP not in range; not setting";
	shiplog(msg,5);
  }
}
void Player::setArmour(int new_armour) {
  if (checkStatRange(new_armour,0,99)) {
	armour = new_armour;
  } else {
	string msg = "Armour not in range; not setting";
	shiplog(msg,5);
  }
}
void Player::setSpeed(int new_speed) {
  if (checkStatRange(new_speed,0,99)) {
	speed = new_speed;
  } else {
	string msg = "Speed not in range; not setting";
	shiplog(msg,5);
  }
}
void Player::setDodge(int new_dodge) {
  if (checkStatRange(new_dodge,0,99)) {
	dodge = new_dodge;
  } else {
	string msg = "Dodge not in range; not setting";
	shiplog(msg,5);
  }
}
 
string Player::itos(int i) const {
   stringstream ss;
   ss << i;
   return ss.str();
}

void Player::print() const {
  write_char(xloc, yloc, look, color);
}

void Player::printMainScreenInfo() const {

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
string Player::title() const {
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
  setStrength(10);
  setIntelligence(10);
  setConstitution(10);
  setDexterity(10);
  setLuck(10);
}

void Player::calcSecondaryStats() {
  xp = 0;
  xp_level = 1;
  setHP(20);
  setMaxHP(20);
  setArmour(5);
  setDodge(5);
  setSpeed(10);
}

void Player::addToInventory(const Thing& t) {
  inventory.push_back(t);
}

int Player::checkStatRange(int i, int min, int max) {
  if (i > max || i < min) {
	return 0;
  } else {
	return 1;
  }
}
