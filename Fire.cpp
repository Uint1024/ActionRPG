#include "Fire.h"
#include "GameData.h"

Fire::Fire() :
Weapon(1500, 40, 5, 0)
{
 
}

void
Fire::shoot(GameData* game_data_, const Vec2df player_center_, 
                   float angle_) 
{
  if(canShoot())
  {
    Vec2df origin = {player_center_.x + std::cos(angle_) * 22,
                     player_center_.y + std::sin(angle_) * 22};
    game_data_->createProjectile(origin, angle_, 
                                 bullets_speed,
                                 damage);
    
    last_shot = currentTime();
  }
}

