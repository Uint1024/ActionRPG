#include "Character.h"

Character::Character(){};

Character::Character(int x_, int y_, eTexture texture_id_,
        Vec2di size_, int hp_) :
PhysicalObject(x_, y_, texture_id_, size_), hp(hp_){
  std::cout << "Calling Character constructor" << std::endl;
}

bool Character::checkCollisionWithProjectile(Projectile& projectile_){
  return projectile_.checkCollisionWithCharacter(bounding_box, hp);
}

bool Character::isDead() const{
  return (hp <= 0);
}