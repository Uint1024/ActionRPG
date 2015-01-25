#include "GameData.h"
#include "Player.h"
#include "Utils.h"
#include "Zombie.h"
#include "NPC.h"
#include "UI.h"

#include <vector>
#include <algorithm>

GameData::GameData(int screen_width_, int screen_height_) :
camera{0,0}, wave(1){
  std::cout << "Starting GameData" << std::endl;
  
  textures_render_size.emplace(eTexture::Player, Vec2di{64, 64});
  textures_render_size.emplace(eTexture::Zombie, Vec2di{64, 64});
  textures_render_size.emplace(eTexture::Wall, Vec2di{64,64});
  textures_render_size.emplace(eTexture::Projectile, Vec2di{16, 16});
  
  player = Player("John", screen_width_/2 - 64/2, 
          screen_height_/2 - 64/2,
          textures_render_size[eTexture::Player]);
    
  npcs_vector.push_back(std::make_unique<Zombie>(200, 200, 
          "John John", textures_render_size[eTexture::Zombie]));
  npcs_vector.push_back(std::make_unique<Zombie>(230, 280, 
          "John John", textures_render_size[eTexture::Zombie]));
  
  walls_vector.emplace_back(Wall(Vec2df{500.0f, 500.0f}));
  g_UI.initUI(&player);
 
}

void GameData::render(SDL_Renderer* renderer_, SDL_Texture* characters_texture_,
        SDL_Texture* walls_texture_,
        const std::map<eTexture, SDL_Rect>& texture_src_rect_,
        float zoom_level_){
  player.render(renderer_, characters_texture_, texture_src_rect_, 
          textures_render_size, camera, zoom_level_);
  
  for(auto &npc : npcs_vector){
    npc->render(renderer_, characters_texture_, texture_src_rect_, 
          textures_render_size, camera, zoom_level_);
  }
  
  for (auto& i : projectiles_vector){
    i.render(renderer_, characters_texture_, texture_src_rect_, 
          textures_render_size, camera, zoom_level_);
  }
  
  for(auto &wall : walls_vector){
    wall.render(renderer_, walls_texture_, texture_src_rect_, 
          textures_render_size, camera, zoom_level_);
  }
}

void GameData::receiveInput(const std::map<eKey, bool>& keys_down_,
        const std::array<bool, 255>& mouse_buttons_down_, 
        const Vec2di& mouse_position_, 
        const Vec2di& mouse_position_in_world_){
Vec2df camera_movement = player.receiveInput(keys_down_, mouse_buttons_down_,
          this, camera, mouse_position_in_world_, walls_vector);
  camera.x += camera_movement.x;
  camera.y += camera_movement.y;
}

void GameData::update(){
  for(auto projectile = projectiles_vector.begin() ; 
          projectile != projectiles_vector.end() ;){
    if(projectile->isDead()){
       projectiles_vector.erase(projectile);
    }
    else{
      projectile->update(walls_vector);
      
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
      (*npc)->update(player, walls_vector);
      ++npc;
    }
  }
   
  
  if(npcs_vector.empty()){
    //++wave;
    std::uniform_int_distribution<int> y_top(-300, 0);
    std::uniform_int_distribution<int> x_top_bottom(-100, 900);
    std::uniform_int_distribution<int> x_left(-300, -100);
    std::uniform_int_distribution<int> x_right(900, 1100);
    std::uniform_int_distribution<int> y_bottom(900, 1100);
    std::uniform_int_distribution<int> y_left_right(0, 900);
    std::uniform_int_distribution<int> which_side(0, 3);
    int p = x_right(g_mt19937);
    
    switch(wave){
      case 1:
        for(int i = 0 ; i < 100 ; ++i){
          int side = which_side(g_mt19937);
          int x = 0;
          int y = 0;
          switch(side){
            case 0://left
              x = x_left(g_mt19937);
              y = y_left_right(g_mt19937);
              break;
            case 1:
              x = x_top_bottom(g_mt19937);
              y = y_top(g_mt19937);
              break;
            case 2:
              x = x_right(g_mt19937);
              y = y_left_right(g_mt19937);
              break;
            case 3:
              x = x_top_bottom(g_mt19937);
              y = y_bottom(g_mt19937);
              break;
            default:
              std::cout << "Wrong position" << std::endl;
              break;  
          }
          
          npcs_vector.emplace_back(std::make_unique<Zombie>(x, y, 
                    "John John", textures_render_size[eTexture::Zombie]));
        }
        break;
      default:
        std::cout << "Out of waves, game over!" << std::endl;
        break;
    }
  }
}

void GameData::createProjectile(const Vec2df origin_, const float angle_){
    projectiles_vector.emplace_back(
            Projectile(origin_.x + textures_render_size[eTexture::Player].x/2, 
            origin_.y + textures_render_size[eTexture::Player].y/2, 
            false, 1500, angle_, 5, eElement::Fire, 
            textures_render_size[eTexture::Projectile]));
}

const Vec2df& GameData::getCamera() const{
  return camera;
}