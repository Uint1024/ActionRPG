#include "Character.h"

Character::Character(){};

Character::Character(int x_, int y_, std::string name_, eTexture texture_id_) :
PhysicalObject(x_, y_, texture_id_),
name(name_){
  std::cout << "Calling Character constructor" << std::endl;
}