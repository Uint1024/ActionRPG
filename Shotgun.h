/* 
 * File:   Shotgun.h
 * Author: John
 *
 * Created on 28 janvier 2015, 15:01
 */

#ifndef SHOTGUN_H
#define	SHOTGUN_H
#include "Weapon.h"

class Player;

class Shotgun : public Weapon {
public:
  Shotgun(Player* const player_);
  void shoot(GameData* game_data_, const Vec2df player_center_,
          const float angle_) override;
  void update() override;
  void reload() override;
private:

};

#endif	/* SHOTGUN_H */

