#include "GameData.h"
#include "Player.h"
#include "Utils.h"
#include "Zombie.h"
#include "NPC.h"
#include <vector>
#include <algorithm>
GameData::GameData(int screen_width_, int screen_height_) :
camera{0,0}{

    
  textures_render_size.emplace(eTexture::Player, Sizei{64, 64});
  textures_render_size.emplace(eTexture::Zombie, Sizei{64, 64});
  textures_render_size.emplace(eTexture::Projectile, Sizei{16, 16});
  
  player = Player("John", screen_width_/2 - 64/2, 
          screen_height_/2 - 64/2,
          textures_render_size[eTexture::Player]);
    
  npcs_vector.push_back(std::make_unique<Zombie>(200, 200, 
          "John John", textures_render_size[eTexture::Zombie]));
  npcs_vector.push_back(std::make_unique<Zombie>(230, 280, 
          "John John", textures_render_size[eTexture::Zombie]));
}

void GameData::render(SDL_Renderer* renderer_, SDL_Texture* texture_,
        const std::map<eTexture, SDL_Rect>& texture_src_rect_,
        float zoom_level_){
  player.render(renderer_, texture_, texture_src_rect_, 
          textures_render_size, camera, zoom_level_);
  
  for(auto &npc : npcs_vector){
    npc->render(renderer_, texture_, texture_src_rect_, 
          textures_render_size, camera, zoom_level_);
  }
  
  for (auto& i : projectiles_vector){
    i.render(renderer_, texture_, texture_src_rect_, 
          textures_render_size, camera, zoom_level_);
  }
}

void GameData::receiveInput(const std::map<eKey, bool>& keys_down_,
        const std::array<bool, 255>& mouse_buttons_down_, 
        const Pointi& mouse_position_){
  Sizef camera_movement = player.receiveInput(keys_down_, mouse_buttons_down_,
          this, camera, mouse_position_);
  camera.x += camera_movement.w;
  camera.y += camera_movement.h;
}

void GameData::update(){
  for(auto projectile = projectiles_vector.begin() ; 
          projectile != projectiles_vector.end() ;){
    if(projectile->isDead()){
       projectiles_vector.erase(projectile);
    }
    else{
      projectile->update();
      
      for(auto& npc : npcs_vector){
        npc->checkCollisionWithProjectile(*projectile);
      }
      ++projectile;
    }
  }
  
  /*npcs_vector.erase(
        std::remove_if(npcs_vector.begin(), npcs_vector.end(),
                  [](auto& c){ 
                    return c->isDead();
                    //return false;
                  }),
        npcs_vector.end());*/
  for(auto npc = npcs_vector.begin() ; npc != npcs_vector.end() ;){
    if((*npc)->isDead()){
      npcs_vector.erase(npc);
    }
    else{
      ++npc;
    }
  }
}

void GameData::createProjectile(Pointf origin_, float angle_){
    projectiles_vector.emplace_back(
            Projectile(origin_.x + textures_render_size[eTexture::Player].w/2, 
            origin_.y + textures_render_size[eTexture::Player].h/2, 
            false, 100, angle_, 5, eElement::Fire, 
            textures_render_size[eTexture::Projectile]));
}