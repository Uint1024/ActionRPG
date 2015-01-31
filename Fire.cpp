#include "Fire.h"
#include "GameData.h"
#include "Utils.h"
#include "ConditionState.h"

Fire::Fire(Player* const player_) :
Weapon(50, 1.0f, 5, 0, player_, 80, 70, 500), temperature(0)
{
  conditions_states[State_Burning] = new ConditionState(10000, 10000, 300, 160);
}

void
Fire::shoot(GameData* game_data_, const Vec2df player_center_, 
                   const float angle_) 
{
  if(temperature < 1000 && ammo > 0 && canShoot())
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

void Fire::update() {
  if(temperature > 0)
  {
    --temperature;
  }
}


