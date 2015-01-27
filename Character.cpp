#include "Character.h"
#include "Projectile.h"

Character::Character(){};

Character::Character(int x_, int y_, eTexture texture_id_,
            Vec2di size_, int hp_, int strength_) :
            PhysicalObject(x_, y_, texture_id_, size_), 
            hp(hp_), strength(strength_), shooting_direction(eDirection::None){
  std::cout << "Calling Character constructor" << std::endl;
}

bool Character::checkCollisionWithProjectile(
              Projectile* projectile_){
  return projectile_->checkCollisionWithCharacter(bounding_box, hp);
}

void Character::addWeaponToInventory(eWeapon type_, Weapon weapon_) {
  weapons_inventory[type_] = weapon_;
}


bool Character::isDead() const{
  return (hp <= 0);
}

const int Character::getHp() const{
  return hp;
}

const int Character::getMp() const{
  return mp;
}