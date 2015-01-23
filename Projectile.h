/* 
 * File:   Projectile.h
 * Author: John
 *
 * Created on 23 janvier 2015, 17:46
 */

#ifndef PROJECTILE_H
#define	PROJECTILE_H

#include "PhysicalObject.h"
#include "Utils.h"

class Projectile : public PhysicalObject{
public:
  Projectile();
  Projectile(int x_, int y_, bool can_hurt_player_, int speed_, float angle_, 
          int damage_, eElement element_type_);
  void update();
  private:
  bool can_hurt_player;
  int speed;
  float angle;
  int damage;
  eElement element_type;
};


#endif	/* PROJECTILE_H */

