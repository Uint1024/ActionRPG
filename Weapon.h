/* 
 * File:   Weapon.h
 * Author: John
 *
 * Created on 27 janvier 2015, 13:13
 */

#ifndef WEAPON_H
#define	WEAPON_H
#include "Utils.h"
#include "ConditionState.h"
#include <chrono>
#include <array>
class GameData;

class Weapon{
public:
  virtual void shoot(GameData* game_data_, const Vec2df player_center_,
                      float angle_) = 0;
  int getShootingDelay() const;
  const std::array<ConditionState*, State_Count>& getConditionsStates() const;
protected:
  Weapon();
  Weapon(int shooting_delay_, int bullets_speed_, int damage_, float spread_);
  bool canShoot() const;
  
  int shooting_delay;
  int bullets_speed;
  int damage;
  float spread;
  std::chrono::system_clock::time_point last_shot;
  std::array<ConditionState*, State_Count> conditions_states; 
  
};

#endif	/* WEAPON_H */

