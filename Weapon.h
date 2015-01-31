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
                      const float angle_) = 0;
  Milliseconds getShootingDelay() const;
  virtual void update() = 0;
  const std::array<ConditionState*, State_Count>& getConditionsStates() const;
  virtual void reload();
  std::pair<int, int> getAmmo() const;
  
  
  //some weapon have magazines, some don't, some can overheat etc.
  virtual std::string getAmmoString() const = 0;
  
protected:
  Weapon(const int shooting_delay_, const int bullets_speed_, 
          const int damage_, const float spread_,
          Player* const player_, const int ammo_, const  int magazine_size_, 
          const int reload_time_ms_, const bool currently_equipped_);
  bool canShoot() const;
  
  Milliseconds shooting_delay;
  int bullets_speed;
  int damage;
  float spread;
  std::chrono::system_clock::time_point last_shot;
  std::array<ConditionState*, State_Count> conditions_states; 
  Player* const player;
  
  int ammo;
  int magazine_size;
  int current_magazine;
  int reload_time_ms;//reload time per ammo
  int reload_timer;
  bool currently_equipped;
  
};

#endif	/* WEAPON_H */

