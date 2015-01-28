#include "Character.h"
#include "Projectile.h"

Character::Character() : 
name(" "), hp(0), mp(0), speed(0), strength(0), 
shooting_direction(eDirection::None)
{
};

Character::Character(int x_, int y_, eTexture texture_id_,
            Vec2di size_, int hp_, int strength_) :
            PhysicalObject(x_, y_, texture_id_, size_), 
            hp(hp_), strength(strength_), shooting_direction(eDirection::None)
{
  for(int i = 0 ; i < (int)eWeapon::Weapon_count ; i++)
  {
    weapons_inventory[i] = std::unique_ptr<Weapon>();
  }
  std::cout << "Calling Character constructor" << std::endl;
}

bool 
Character::checkCollisionWithProjectile(Projectile* projectile_)
{
  return projectile_->checkCollisionWithCharacter(bounding_box, hp);
}

void 
Character::addWeaponToInventory(eWeapon type_, std::unique_ptr<Weapon> weapon_)
{
  weapons_inventory[(int)type_] = std::move(weapon_);
}


bool 
Character::isDead() const
{
  return (hp <= 0);
}

int 
Character::getHp() const
{
  return hp;
}

int 
Character::getMp() const
{
  return mp;
}