/* 
 * File:   Fire.h
 * Author: John
 *
 * Created on 28 janvier 2015, 17:06
 */

#ifndef FIRE_H
#define	FIRE_H
#include "Weapon.h"

class Fire : public Weapon
{
public:
  Fire();
  void shoot(GameData* game_data_, const Vec2df player_center_,
          float angle_) override;
};

#endif	/* FIRE_H */

