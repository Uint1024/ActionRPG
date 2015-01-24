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
#include "Projectile.h"
#include "NPC.h"
#include <SDL.h>
#include <map>
#include <vector>
#include <memory>

class GameData{
public:
  GameData(int screen_width_, int screen_height_);
  void render(SDL_Renderer* renderer_, SDL_Texture* texture_, 
              const std::map<eTexture, SDL_Rect>& texture_src_rect_,
              float zoom_level_);
  void receiveInput(const std::map<eKey, bool>& keys_down_,
              const std::array<bool, 255>& mouse_buttons_down_,
              const Pointi& mouse_position_);
  
  void update();
  void createProjectile(Pointf origin_, float angle_);
private:
  Player player;
  std::map<eTexture, Sizei> textures_render_size;
  std::vector<std::unique_ptr<NPC>> npcs_vector;
  Pointf camera;
  std::vector<Projectile> projectiles_vector;
};

#endif	/* GAMEDATA_H */

