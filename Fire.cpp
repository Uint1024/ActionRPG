#include "Fire.h"
#include "GameData.h"
#include "Utils.h"
#include "ConditionState.h"
#include <sstream>

Fire::Fire(Player* const player_) :
Weapon(50, 1.0f, 5, 0, player_, 800, 70, 500, false), temperature(0)
{
  conditions_states[State_Burning] = new ConditionState(10000, 10000, 300, 160);
}

void
Fire::shoot(GameData* game_data_, const Vec2df player_center_, 
                   const float angle_) 
{
  if(!overheating && ammo > 0 && canShoot())
  {
    --ammo;
    temperature += 30;
    Vec2df origin = {player_center_.x + std::cos(angle_) * 22,
                     player_center_.y + std::sin(angle_) * 22};
    game_data_->createProjectile(origin, angle_, 
                                 bullets_speed,
                                 damage, this);
    
    last_shot = currentTime();
  }
}

void Fire::update() 
{
  auto next_possible_shot = last_shot + shooting_delay;
  auto current_time = currentTime();
  if(current_time > next_possible_shot && temperature > 0)
  {
    temperature -= 0.2 * g_delta_t;
  }
  
  if(temperature < 0) temperature = 0;
  

  if(temperature >= 1000)
  {
    overheating = true;
  }
  
  if(overheating && temperature == 0)
  {
    overheating = false;
  }
}

std::string
Fire::getAmmoString() const 
{
  std::ostringstream oss;
  
  if(overheating)
  {
    oss << ammo << "/" << (int)temperature << " !OVERHEAT!";
    return oss.str();
  }
  else
  {
    oss << ammo << "/" << (int)temperature << "C";
    return oss.str();
  }
}


