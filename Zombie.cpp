#include "Zombie.h"
#include "PhysicalObject.h"

Zombie::Zombie(){};

Zombie::Zombie(int x_, int y_, std::string name_):
NPC(x_, y_, name_, eTexture::Zombie){
  std::cout << "calling Zombie constructor" << std::endl;
}

void Zombie::runAI(){
  
}