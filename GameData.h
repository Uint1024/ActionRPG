/* 
 * File:   GameData.h
 * Author: John
 *
 * Created on 22 janvier 2015, 14:36
 */

#ifndef GAMEDATA_H
#define	GAMEDATA_H
#include "Player.h"
#include "Utils.h"
#include <SDL.h>
#include <map>
//class Player;

class GameData{
public:
  GameData();
  void render(SDL_Renderer* renderer_, SDL_Texture* texture_, 
              std::map<eTexture, SDL_Rect>& texture_src_rect_);
  Player& getPlayer();
  //void initializeGameData();
private:
  Player player;
  
};

#endif	/* GAMEDATA_H */

