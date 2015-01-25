/*
* File: Character.h
* Author: John
*
* Created on 23 janvier 2015, 02:32
*/
#ifndef CHARACTER_H
#define	CHARACTER_H
#include "Utils.h"
#include "Projectile.h"

#include "PhysicalObject.h"
#include <string>
#include <chrono>

class Character : public PhysicalObject{
public:
  Character();
  Character(int x_, int y_, eTexture texture_id_,
          Vec2di size_, int hp_, int strength_);
  bool checkCollisionWithProjectile(Projectile& projectile_);
  bool isDead() const;
  const int getHp() const;
  const int getMp() const;
protected:
  std::string name;
  int hp;
  int mp;
  int speed;
  int strength;

};
#endif	/* CHARACTER_H */