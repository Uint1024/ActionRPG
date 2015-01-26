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
#include <memory>

class Projectile : public PhysicalObject{
public:
  Projectile();
  Projectile(int x_, int y_, bool can_hurt_player_, int speed_, float angle_, 
          int damage_, eElement element_type_, Vec2di size_);
  void update(const std::vector<std::unique_ptr<Wall>>& walls_vector_,
        const std::vector<std::unique_ptr<NPC>>& npcs_vector_);
  bool checkCollisionWithCharacter(const Rect& bounding_box_, int& hp);
  bool hasHit() const;
  bool isDead() const;
  private:
  bool can_hurt_player;
  int speed;
  float angle;
  int damage;
  eElement element_type;
  bool has_hit;
  float distance_travelled;
  bool dead;
};


#endif	/* PROJECTILE_H */

