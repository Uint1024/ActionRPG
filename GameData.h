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
#include "Wall.h"
#include <SDL.h>
#include <map>
#include <vector>
#include <memory>
#include <random>

class GameData{
public:
  GameData(int screen_width_, int screen_height_);
  void render(SDL_Renderer* renderer_, SDL_Texture* characters_texture_,
              SDL_Texture* walls_texture_,
              const std::map<eTexture, SDL_Rect>& texture_src_rect_,
              float zoom_level_);
  void receiveInput(const std::map<eKey, bool>& keys_down_,
              const std::array<bool, 255>& mouse_buttons_down_,
              const Vec2di& mouse_position_, 
              const Vec2di& mouse_position_in_world_);
  void createWall(const Vec2di& mouse_position_in_world_);
  
  void update();
  void createProjectile(const Vec2df origin_, const float angle_);
  const Vec2df& getCamera() const;
private:
  Player player;
  std::map<eTexture, Vec2di> textures_render_size;
  std::vector<std::unique_ptr<NPC>> npcs_vector;
  std::vector<std::unique_ptr<Wall>> walls_vector;
  Vec2df camera;
  std::vector<std::unique_ptr<Projectile>> projectiles_vector;
  uint wave;
  std::mt19937* mt19937_rng;
  int walls_size;
  Vec2di map_size;
};

#endif	/* GAMEDATA_H */

