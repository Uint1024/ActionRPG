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

class Character : public PhysicalObject{
public:
  Character();
  Character(int x_, int y_, eTexture texture_id_,
          Sizei size_);
  bool checkCollisionWithProjectile(Projectile& projectile_);

protected:
  std::string name;
  int hp;
  int mp;
  int speed;
};
#endif	/* CHARACTER_H */