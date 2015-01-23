/* 
 * File:   Player.h
 * Author: John
 *
 * Created on 22 janvier 2015, 14:23
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include "Character.h"
#include "Utils.h"
#include <string>
#include <SDL.h>
#include <map>
class GameData;
struct Point;

class Player : public Character{
public:
  Player();
  Player(std::string name_, int x_, int y_);
  void move(Point movement_);
  
  //return movement
  Point receiveInput(std::map<eKey, bool>& keys_down_,
            std::array<bool, 255>& mouse_buttons_down_, GameData* game_data_,
            Point& camera_);

private:
};

#endif	/* PLAYER_H */

