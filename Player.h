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
#include "Wall.h"
#include <string>
#include <SDL.h>
#include <map>
class GameData;
struct Vec2df;

class Player : public Character{
public:
  Player();
  Player(std::string name_, int x_, int y_, Vec2di size_);
  //return movement
  Vec2df receiveInput(const std::map<eKey, bool>& keys_down_,
            const std::array<bool, 255>& mouse_buttons_down_, 
            GameData* game_data_,
            const Vec2df& camera_, const Vec2di& mouse_position_in_world_,
            const std::vector<Wall> walls_vector_);
  
private:
    std::chrono::system_clock::time_point last_shot;
};

#endif	/* PLAYER_H */

