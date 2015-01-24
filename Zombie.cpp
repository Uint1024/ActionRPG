#include "Zombie.h"
#include "PhysicalObject.h"

Zombie::Zombie(){};

Zombie::Zombie(int x_, int y_, std::string name_, Sizei size_):
NPC(x_, y_, name_, eTexture::Zombie, size_){
  std::cout << "calling Zombie constructor" << std::endl;
}

void Zombie::runAI(){
  
}