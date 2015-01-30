#include "Fire.h"
#include "GameData.h"
#include "Utils.h"
#include "ConditionState.h"

Fire::Fire(Player* player_) :
Weapon(1500, 1.0f, 5, 0, player_)
{
  conditions_states[State_Burning] = new ConditionState{10000, 10000, 30};
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
                                 damage, this);
    
    last_shot = currentTime();
  }
}

void Fire::update() {

}


