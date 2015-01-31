/* 
 * File:   Fire.h
 * Author: John
 *
 * Created on 28 janvier 2015, 17:06
 */

#ifndef FIRE_H
#define	FIRE_H
#include "Weapon.h"

class Player;

class Fire : public Weapon
{
public:
  Fire(Player* const  player_);
  void shoot(GameData* game_data_, const Vec2df player_center_,
          const float angle_) override;
  void update() override;
  virtual std::string getAmmoString() const;

  
private:
  float temperature;
  bool overheating;
};

#endif	/* FIRE_H */

