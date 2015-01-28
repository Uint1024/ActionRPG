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
  void addWeaponToInventory(eWeapon type_, std::unique_ptr<Weapon> weapon_);
  bool isDead() const;
  int getHp() const;
  int getMp() const;
protected:
  std::string name;
  int hp;
  int mp;
  int speed;
  int strength;
  eDirection shooting_direction;
  //std::map<eWeapon, std::unique_ptr<Weapon>> weapons_inventory;
  std::unique_ptr<Weapon> weapons_inventory[(int)eWeapon::Weapon_count];
  
};
#endif	/* CHARACTER_H */