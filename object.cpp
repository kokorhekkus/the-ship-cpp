// Objects

#include "object.h"
#include "log.h"

#include <sstream>

using namespace std;

//----------------------------------------------------------------------
// Thing class implementation
//----------------------------------------------------------------------
Thing::Thing(unsigned int a_id, string& a_name, int a_weight,
			 int xloc, int yloc,
			 mapColor color, char look) :
  ScreenObject(xloc, yloc, color, look),
  id(a_id), name(a_name), weight(a_weight) {
  
  ostringstream oss;
  oss << "Creating new Thing object with id " << id;
  string s = oss.str();
  shiplog(s, 10);
}

Thing::~Thing() {
  ostringstream oss;
  oss << "Destroying Thing object with id " << id;
  string s = oss.str();
  shiplog(s, 10);
}

// Getters
unsigned int Thing::getId() const { return id; }
string Thing::getName() const { return name; }
int Thing::getWeight() const { return weight; }


//----------------------------------------------------------------------
// Gun class implementation
//----------------------------------------------------------------------
Gun::Gun(unsigned int id, string& name, int weight,
		 int xloc, int yloc,
		 mapColor color, char look,
		 int a_range, int a_to_hit,
		 int a_dmgdice_num, int a_dmgdice_sides) :
  Thing(id, name, weight, xloc, yloc, color, look),
  range(a_range), dmgdice_num(a_dmgdice_num),
  dmgdice_sides(a_dmgdice_sides), to_hit(a_to_hit) {

  ostringstream oss;
  oss << "Creating new Gun object with id " << getId();
  string s = oss.str();
  shiplog(s, 10);
}
Gun::~Gun() {
  ostringstream oss;
  oss << "Destroying Gun object with id " << getId();
  string s = oss.str();
  shiplog(s, 10);
}

// Object initialisation: set up data for all potential game objects
// TODO: actually do this.  Perhaps use config files that are easily editable?
//       Perhaps store the main details in some data structure or other, then 
//       have an 'instantiate' type proc that creates the actual object?
void init_objects() {
  shiplog("Initialising objects...",1);
}
