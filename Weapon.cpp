#include "Weapon.h"
#include <iostream>


Weapon::Weapon():
shooting_delay(0), bullets_speed(0),
damage(0), spread(0.0f)
{
  
}

Weapon::Weapon(int shooting_delay_, int bullets_speed_, 
        int damage_, float spread_) : 
shooting_delay(shooting_delay_), bullets_speed(bullets_speed_),
damage(damage_), spread(spread_)
{
  for(int i = 0 ; i < State_Count ; i++)
  {
    conditions_states[i] = nullptr;
  }
}

int 
Weapon::getShootingDelay() const 
{
  return shooting_delay;
}

bool
Weapon::canShoot() const
{
  return differenceTimes(currentTime(), last_shot) > shooting_delay;
}

const std::array<ConditionState*, State_Count>&
Weapon::getConditionsStates() const 
{
  return conditions_states;
}
