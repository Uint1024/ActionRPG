
#include "Projectile.h"
#include "Utils.h"
#include <cmath>
Projectile::Projectile() {};

Projectile::Projectile(int x_, int y_, bool can_hurt_player_, int speed_,
          float angle_, int damage_, eElement element_type_, Sizei size_) :
        PhysicalObject(x_, y_, eTexture::Projectile, size_),
        speed(speed_), angle(angle_), damage(damage_), 
        element_type(element_type_), can_hurt_player(can_hurt_player_),
        has_hit(false){
}

void Projectile::update(){
  float real_speed = speed * g_delta_t;
  Sizef movement = { std::cos(angle) * real_speed,
                    std::sin(angle) * real_speed };
  pos.x += movement.w;
  pos.y += movement.h;
  
  updateBoundingBox(bounding_box, movement);
}

bool Projectile::checkCollisionWithCharacter(Rect& bounding_box_, int& hp){
  if(checkCollisionBetweenBoxes(bounding_box, bounding_box_)){

    hp -= damage;
    has_hit = true;
    return true;
  }
  return false;
}

bool Projectile::hasHit(){ return has_hit; };