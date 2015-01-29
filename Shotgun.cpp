#include "Shotgun.h"
#include "GameData.h"


Shotgun::Shotgun() :
Weapon(600, 1.0f, 2500, 400)
{
  
}

void
Shotgun::shoot(GameData* game_data_, const Vec2df player_center_, 
                   float angle_) 
{
  if(canShoot())
  {
    Vec2df origin = {player_center_.x + std::cos(angle_) * 32,
                     player_center_.y + std::sin(angle_) * 32};
    std::uniform_int_distribution<int> rand(-spread, spread);

    for(int i = 0 ; i < 5 ; i++)
    {
      float x = rand(g_mt19937) / 1000.0f;
      game_data_->createProjectile(origin, angle_ + x, 
                                   bullets_speed,
                                   damage, this);
    }
    
    last_shot = currentTime();
  }
}
