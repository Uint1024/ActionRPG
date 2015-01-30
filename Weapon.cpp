#include "Weapon.h"
#include <iostream>


Weapon::Weapon():
shooting_delay(0), bullets_speed(0),
damage(0), spread(0.0f)
{
  
}

Weapon::Weapon(int shooting_delay_, int bullets_speed_, int damage_, 
        float spread_, Player* player_, int ammo_, int magazine_size_, 
        int reload_time_ms_): 
shooting_delay(Milliseconds(shooting_delay_)), bullets_speed(bullets_speed_),
        damage(damage_), spread(spread_), player(player_),
        magazine_size(magazine_size_), current_magazine(magazine_size_),
        ammo(ammo_), reload_time_ms(reload_time_ms_), 
        reload_timer(reload_time_ms_)
{
  for(int i = 0 ; i < State_Count ; i++)
  {
    conditions_states[i] = nullptr;
  }
}

Milliseconds 
Weapon::getShootingDelay() const 
{
  return shooting_delay;
}

bool
Weapon::canShoot() const
{
  //return differenceTimes(currentTime(), last_shot) > shooting_delay;
  return currentTime() - last_shot > shooting_delay;
}

const std::array<ConditionState*, State_Count>&
Weapon::getConditionsStates() const 
{
  return conditions_states;
}

void
Weapon::reload()
{
  //do nothing?
}

std::pair<int, int> 
Weapon::getAmmo() const 
{
  return {current_magazine, ammo};
}
