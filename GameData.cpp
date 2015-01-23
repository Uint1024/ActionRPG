#include "GameData.h"
#include "Player.h"
#include "Utils.h"
#include "Zombie.h"
#include "NPC.h"
#include <vector>

GameData::GameData(int screen_width_, int screen_height_) :
camera{0,0}{
  player = Player("John", screen_width_/2 - 64/2, screen_height_/2 - 64/2);
  textures_render_size.emplace(eTexture::Player, Size{64, 64});
  npcs_vector.push_back(std::make_unique<Zombie>(200, 200, "John John"));
  npcs_vector.push_back(std::make_unique<Zombie>(230, 280, "John John"));
  

}

void GameData::render(SDL_Renderer* renderer_, SDL_Texture* texture_,
        std::map<eTexture, SDL_Rect>& texture_src_rect_,
        std::map<eTexture, Size>& textures_render_size_,
        float zoom_level_){
  player.render(renderer_, texture_, texture_src_rect_, 
          textures_render_size, camera, zoom_level_);
  
  for(auto &npc : npcs_vector){
    npc->render(renderer_, texture_, texture_src_rect_, 
          textures_render_size_, camera, zoom_level_);
  }
  
  for (auto& i : projectiles_vector){
    i.render(renderer_, texture_, texture_src_rect_, 
          textures_render_size_, camera, zoom_level_);
  }
}

void GameData::receiveInput(std::map<eKey, bool>& keys_down_,
        std::array<bool, 255>& mouse_buttons_down_){
  Point camera_movement = player.receiveInput(keys_down_, mouse_buttons_down_,
          this, camera);
  camera.x += camera_movement.x;
  camera.y += camera_movement.y;
  
  
}

void GameData::update(){
  for(auto& i : projectiles_vector){
    i.update();
  }
}

void GameData::createProjectile(Point origin_, float angle_){
    projectiles_vector.emplace_back(
            Projectile(origin_.x, origin_.y, false, 300, angle_, 0, eElement::Fire));
}