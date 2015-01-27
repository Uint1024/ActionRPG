/*
* File: Character.h
* Author: John
*
* Created on 23 janvier 2015, 02:32
*/
#ifndef CHARACTER_H
#define	CHARACTER_H
#include "Utils.h"


#include "PhysicalObject.h"
#include "Weapon.h"

#include <map>
#include <string>
#include <chrono>
#include <memory>

class Projectile;

class Character : public PhysicalObject{
public:
  Character();
  Character(int x_, int y_, eTexture texture_id_,
            Vec2di size_, int hp_, int strength_);
  bool checkCollisionWithProjectile(Projectile* projectile_);
  void addWeaponToInventory(eWeapon type_, Weapon weapon_);
  bool isDead() const;
  const int getHp() const;
  const int getMp() const;
protected:
  std::string name;
  int hp;
  int mp;
  int speed;
  int strength;
  eDirection shooting_direction;
  std::map<eWeapon, Weapon> weapons_inventory;
};
#endif	/* CHARACTER_H */