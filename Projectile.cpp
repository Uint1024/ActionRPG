
#include "Projectile.h"
#include "Utils.h"
#include <cmath>
Projectile::Projectile() {};

Projectile::Projectile(int x_, int y_, bool can_hurt_player_, int speed_,
          float angle_, int damage_, eElement element_type_, Vec2di size_) :
        PhysicalObject(x_, y_, eTexture::Projectile, size_),
        speed(speed_), angle(angle_), damage(damage_), 
        element_type(element_type_), can_hurt_player(can_hurt_player_),
        has_hit(false), distance_travelled(0.0f), dead(false){
}

void Projectile::update(){
  float real_speed = speed * g_delta_t;
  Vec2df movement = { std::cos(angle) * real_speed,
                    std::sin(angle) * real_speed };
  pos.x += movement.x;
  pos.y += movement.y;
  
  updateBoundingBox(bounding_box, movement);
  
  distance_travelled += std::sqrt((movement.x * movement.x) + 
          (movement.y * movement.y));
  if (distance_travelled > 600){
    dead = true;
  }
}

bool Projectile::checkCollisionWithCharacter(const Rect& bounding_box_, int& hp){
  if(checkCollisionBetweenBoxes(bounding_box, bounding_box_)){

    hp -= damage;
    dead = true;
    return true;
  }
  return false;
}

bool Projectile::hasHit() const{ return has_hit; };

bool Projectile::isDead() const { return dead; };