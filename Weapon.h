/* 
 * File:   Weapon.h
 * Author: John
 *
 * Created on 27 janvier 2015, 13:13
 */

#ifndef WEAPON_H
#define	WEAPON_H

class Weapon{
public:
  Weapon();
  Weapon(int shooting_delay_, int bullets_speed_, int damage_, float spread_);
  int shooting_delay;
  int bullets_speed;
  int damage;
  float spread;
};

#endif	/* WEAPON_H */

