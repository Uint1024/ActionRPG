/* 
 * File:   Shotgun.h
 * Author: John
 *
 * Created on 28 janvier 2015, 15:01
 */

#ifndef SHOTGUN_H
#define	SHOTGUN_H
#include "Weapon.h"

class Shotgun : public Weapon {
public:
  Shotgun();
  void shoot(GameData* game_data_, const Vec2df player_center_,
          float angle_) override;
private:
  int magazine_size;
  int current_magazine;
};

#endif	/* SHOTGUN_H */

