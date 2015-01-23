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
#include "NPC.h"
#include <SDL.h>
#include <map>
#include <vector>
#include <memory>
//class Player;

class GameData{
public:
  GameData(int screen_width_, int screen_height_);
  void render(SDL_Renderer* renderer_, SDL_Texture* texture_, 
              std::map<eTexture, SDL_Rect>& texture_src_rect_,
              std::map<eTexture, Size>& textures_render_size_,
              float zoom_level_);
  Player& getPlayer();
  void receiveInput(std::map<eKey, bool>& keys_down_);
private:
  Player player;
  std::map<eTexture, Size> textures_render_size;
  std::vector<std::unique_ptr<NPC>> npcs_vector;
  Point camera;
};

#endif	/* GAMEDATA_H */

