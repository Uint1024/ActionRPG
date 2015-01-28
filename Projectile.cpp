
#include "Projectile.h"
#include "Utils.h"
#include "NPC.h"
#include <cmath>
Projectile::Projectile() {};

Projectile::Projectile(int x_, int y_, bool can_hurt_player_, int speed_,
          float angle_, int damage_, eElement element_type_, Vec2di size_) :
        PhysicalObject(x_, y_, eTexture::Projectile, size_),
        speed(speed_), angle(angle_), damage(damage_), 
        element_type(element_type_), can_hurt_player(can_hurt_player_),
        has_hit(false), distance_travelled(0.0f), dead(false)
{
  
}

Projectile::Projectile(bool dead_) : 
        PhysicalObject(0, 0, eTexture::Projectile, Vec2di{0,0}),
        speed(0), angle(0), damage(0), 
        element_type(eElement::Life), can_hurt_player(false),
        has_hit(false), distance_travelled(0.0f), dead(dead_)
{
}

void 
Projectile::update(const std::vector<std::unique_ptr<Wall>>& walls_vector_,
        const std::vector<std::unique_ptr<NPC>>& npcs_vector_)
{
  float real_speed = speed * g_delta_t;
  Vec2df movement = move(angle, real_speed, walls_vector_, npcs_vector_);
  for(auto& npc : npcs_vector_){
        npc->checkCollisionWithProjectile(this);
  }
  
  distance_travelled += std::sqrt((movement.x * movement.x) + 
          (movement.y * movement.y));
  if (distance_travelled > 600){
    dead = true;
  }
}

void 
Projectile::renew(int x_, int y_, bool can_hurt_player_, int speed_, 
        float angle_, int damage_, eElement element_type_, Vec2di size_)
{
  pos = {(float)x_, (float)y_};
  can_hurt_player = can_hurt_player_;
  speed = speed_;
  angle = angle_;
  damage = damage_;
  element_type = element_type_;
  size = size_;
  
  dead = false;
  distance_travelled = 0;
  has_hit = false;
  bounding_box = Rect{(float)x_, (float)y_, 
          (float)(x_ + size_.x), (float)(y_ + size_.y)};
}

bool 
Projectile::checkCollisionWithCharacter(const Rect& bounding_box_, 
        int& hp)
{
  if(checkCollisionBetweenBoxes(bounding_box, bounding_box_))
  {
    hp -= damage;
    dead = true;
    return true;
  }
  return false;
}

bool 
Projectile::hasHit() const
{ 
  return has_hit; 
};

bool 
Projectile::isDead() const 
{ 
  return dead; 
};