#include "Shotgun.h"
#include "GameData.h"


Shotgun::Shotgun(Player* player_) :
Weapon(600, 1.0f, 2500, 400, player_, 80, 8, 200)
{
  
}

void
Shotgun::shoot(GameData* game_data_, const Vec2df player_center_, 
                   float angle_) 
{
  
  if(current_magazine > 0 && canShoot())
  {
    --current_magazine;
    
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

void
Shotgun::update()
{
  auto k = last_shot + shooting_delay + Milliseconds{500};
  auto current_time = currentTime();
  if(current_time > k && current_magazine < magazine_size)
  {
    player->reload();
  }
  
  //std::cout << current_time.time_since_epoch().count() << " " << k.time_since_epoch().count() << std::endl;
}

void
Shotgun::reload()
{
  reload_timer -= g_delta_t;
      
  if(reload_timer <= 0)
  {
    if(ammo > 0 && magazine_size > current_magazine)
    {
      current_magazine += 1;
      ammo -= 1;
      reload_timer = reload_time_ms;
    }
    else
    {
      player->stopReloading();
    }
  }
}