// The Player Character

#include "player.h"
#include "log.h"

#include <ncurses.h>

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
void Player::setArmour(short int new_armour) { armour = new_armour; }
void Player::setSpeed(short int new_speed) { speed = new_speed; }
void Player::setDodge(short int new_dodge) { dodge = new_dodge; }

void Player::genPrimaryStats() {
}

void Player::calcSecondaryStats() {
}

void Player::addToInventory(const Thing& t) {
  inventory.push_back(t);
}
