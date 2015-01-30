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
  Fire(Player* player_);
  void shoot(GameData* game_data_, const Vec2df player_center_,
          float angle_) override;
  void update() override;
};

#endif	/* FIRE_H */

