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
class Weapon;
class Wall;

class Projectile : public PhysicalObject{
public:
  Projectile();
   Projectile(bool dead_);
  void renew(int x_, int y_, bool can_hurt_player_, int speed_, float angle_, 
          int damage_, eElement element_type_, Vec2di size_, Weapon* shot_by_);
  void update(const std::vector<std::unique_ptr<Wall>>& walls_vector_,
        const std::vector<std::unique_ptr<NPC>>& npcs_vector_);
  bool checkCollisionWithCharacter(const Rect& bounding_box_, int& hp);
  const Vec2df move(const float angle_, const float speed, 
                  const std::vector<std::unique_ptr<Wall>>& walls_vector_,
                  const std::vector<std::unique_ptr<NPC>>& npcs_vector_);
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
  eTexture texture;
  eTexture explosion_texture;
  bool explode;
  Weapon* shot_by;
};


#endif	/* PROJECTILE_H */

