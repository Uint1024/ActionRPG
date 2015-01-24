#include "Character.h"

Character::Character(){};

Character::Character(int x_, int y_, eTexture texture_id_,
        Sizei size_) :
PhysicalObject(x_, y_, texture_id_, size_){
  std::cout << "Calling Character constructor" << std::endl;
}

bool Character::checkCollisionWithProjectile(Projectile& projectile_){
  return projectile_.checkCollisionWithCharacter(bounding_box, hp);
}