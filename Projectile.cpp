
#include "Projectile.h"
#include "Character.h"
#include <cmath>
Projectile::Projectile() {};

Projectile::Projectile(int x_, int y_, bool can_hurt_player_, int speed_,
          float angle_, int damage_, eElement element_type_) :
        PhysicalObject(x_, y_, eTexture::Projectile),
        speed(speed_), angle(angle_), damage(damage_), 
        element_type(element_type_), can_hurt_player(can_hurt_player_){
}

void Projectile::update(){
  pos.x += std::cos(angle) * speed * g_delta_t;
  pos.y += std::sin(angle) * speed * g_delta_t;
}