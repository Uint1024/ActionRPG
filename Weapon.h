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

class Player;

class Weapon{
public:
  virtual void shoot(GameData* game_data_, const Vec2df player_center_,
                      float angle_) = 0;
  Milliseconds getShootingDelay() const;
  virtual void update() = 0;
  const std::array<ConditionState*, State_Count>& getConditionsStates() const;
  virtual void reload();
  std::pair<int, int> getAmmo() const;
  
protected:
  Weapon();
  Weapon(int shooting_delay_, int bullets_speed_, int damage_, float spread_,
  Player* player_, int ammo_, int magazine_size_, int reload_time_ms_);
  bool canShoot() const;
  
  Milliseconds shooting_delay;
  int bullets_speed;
  int damage;
  float spread;
  std::chrono::system_clock::time_point last_shot;
  std::array<ConditionState*, State_Count> conditions_states; 
  Player* player;
  
  int ammo;
  int magazine_size;
  int current_magazine;
  int reload_time_ms;//reload time per ammo
  int reload_timer;
};

#endif	/* WEAPON_H */

