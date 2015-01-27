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
//#include "Wall.h"
#include <string>
#include <SDL.h>
#include <map>
#include <memory>
class GameData;
struct Vec2df;
class Wall;

class Player : public Character{
public:
  Player();
  Player(std::string name_, int x_, int y_, Vec2di size_);
  //return movement
  Vec2df receiveInput(const std::map<eKey, bool>& keys_down_,
            const std::array<bool, 255>& mouse_buttons_down_, 
            GameData* game_data_,
            const Vec2df& camera_, const Vec2di& mouse_position_in_world_,
            const std::vector<std::unique_ptr<Wall>>& walls_vector_);
  void shoot(GameData* game_data_, const Vec2di& mouse_position_in_world_);
  void shootShotgun(GameData* game_data_, const Vec2df& player_center_, 
        const float angle_);
  void shootFire(GameData* game_data_, const Vec2df& player_center_, 
        const float angle_);
private:
    std::chrono::system_clock::time_point last_shot;
    eWeapon current_weapon;
};

#endif	/* PLAYER_H */

