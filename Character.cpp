#include "Character.h"

Character::Character(){};

Character::Character(int x_, int y_, std::string name_) :
PhysicalObject(x_, y_),
name(name_){
  std::cout << "Calling Character constructor" << std::endl;
}