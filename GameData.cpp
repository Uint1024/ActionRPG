#include "GameData.h"
#include "Player.h"
#include "Weapon.h"
#include "Utils.h"
#include "Shotgun.h"

#include "Zombie.h"
#include "NPC.h"
#include "UI.h"

#include <vector>
#include <algorithm>
#include <memory>
int p = 0;

GameData::GameData(int screen_width_, int screen_height_) :
camera{0,0}, wave(1){
  walls_size = 64;
  map_size = {32, 32};
  std::cout << "Starting GameData" << std::endl;
  
  textures_render_size.emplace(eTexture::Player, Vec2di{64, 64});
  textures_render_size.emplace(eTexture::Zombie, Vec2di{64, 64});
  textures_render_size.emplace(eTexture::Wall, Vec2di{64,64});
  textures_render_size.emplace(eTexture::Projectile, Vec2di{16, 16});
  
  player = Player("John", screen_width_/2 - 64/2, 
          screen_height_/2 - 64/2,
          textures_render_size[eTexture::Player]);

  npcs_vector.emplace_back(std::make_unique<Zombie>(200, 200, 
          "John John", textures_render_size[eTexture::Zombie]));
 npcs_vector.emplace_back(std::make_unique<Zombie>(300, 200, 
          "John John", textures_render_size[eTexture::Zombie]));
  npcs_vector.emplace_back(std::make_unique<Zombie>(400, 200, 
          "John John", textures_render_size[eTexture::Zombie]));
  
  walls_vector.reserve(map_size.x * map_size.y);
  for(int i = 0 ; i < map_size.x * map_size.y ; i++)
  {
    walls_vector.emplace_back(std::unique_ptr<Wall>());
  }  
  
  g_UI.initUI(&player);
  
 
  
  projectiles_vector.reserve(512);
  for(int i = 0 ; i < 512 ; i++){
    projectiles_vector.emplace_back(
              std::make_unique<Projectile>(true));
  }
}

void GameData::render(SDL_Renderer* renderer_, SDL_Texture* characters_texture_,
        SDL_Texture* walls_texture_,
        const std::map<eTexture, std::map<eDirection, SDL_Rect>>&
                  dynamic_texture_src_rect_,
        const std::map<eTexture, SDL_Rect>& static_texture_src_rect,
        float zoom_level_){
  
  player.render_dynamic(renderer_, characters_texture_, dynamic_texture_src_rect_, 
          textures_render_size, camera, zoom_level_);
  
  for(auto &npc : npcs_vector){
    npc->render_dynamic(renderer_, characters_texture_, dynamic_texture_src_rect_, 
          textures_render_size, camera, zoom_level_);
  }
  
  for (auto& i : projectiles_vector){
    i->render_dynamic(renderer_, characters_texture_, dynamic_texture_src_rect_, 
          textures_render_size, camera, zoom_level_);
  }
  
  for(auto &wall : walls_vector){
    if(wall){
      wall->render_static(renderer_, walls_texture_, static_texture_src_rect, 
            textures_render_size, camera, zoom_level_);
    }
  }
}

void GameData::receiveInput(const std::map<eKey, bool>& keys_down_,
        const std::array<bool, 255>& mouse_buttons_down_, 
        const Vec2di& mouse_position_, 
        const Vec2di& mouse_position_in_world_){
  Vec2df camera_movement = player.receiveInput(keys_down_, mouse_buttons_down_,
          this, camera, mouse_position_in_world_, walls_vector);
  
  if(mouse_buttons_down_[SDL_BUTTON_RIGHT]){
    createWall(mouse_position_in_world_);
  }
 
  camera.x += camera_movement.x;
  camera.y += camera_movement.y;
}

void GameData::createWall(const Vec2di& mouse_position_in_world_){
  Vec2di tile = {mouse_position_in_world_.x / walls_size,
                  mouse_position_in_world_.y / walls_size};
  
  
  if (tile.x > 0 && tile.x < map_size.x && tile.y > 0 && tile.y < map_size.y){
    int position_in_array = tile.y * map_size.x + tile.x;
    /*walls_vector.emplace_back(
            std::make_unique<Wall>(tile * ,
                                   mouse_position_in_world_.y ));*/
    std::cout << position_in_array << std::endl;
    Vec2di position_of_wall = {tile.x * walls_size, tile.y * walls_size};
    walls_vector[position_in_array] = std::make_unique<Wall>(position_of_wall);
  }
 }


void GameData::update(){
  for(auto projectile = projectiles_vector.begin() ; 
          projectile != projectiles_vector.end() ;
          ++projectile){
    if(!(*projectile)->isDead()){
      (*projectile)->update(walls_vector, npcs_vector);
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
      (*npc)->update(player, walls_vector, npcs_vector);
      ++npc;
    }
  }
   
  
  if(npcs_vector.empty()){
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

void GameData::createProjectile(const Vec2df origin_, const float angle_,
                                const int speed_, const int damage_){
  //float x = origin_.x + textures_render_size[eTexture::Player].x/2;
  //float y = origin_.y + textures_render_size[eTexture::Player].y/2;
  
  auto dead_projectile = std::find_if(projectiles_vector.begin(), 
                                projectiles_vector.end(), 
                                [](auto &projec) {
                                  return projec->isDead(); 
                                });
                                
                                
  if(dead_projectile != projectiles_vector.end()){
    (*dead_projectile)->renew(origin_.x, origin_.y, false, speed_, angle_, 
                              damage_, eElement::Fire,
                              textures_render_size[eTexture::Projectile]);
  }
  else{
    std::cout << "No dead projectile available!" << std::endl;
  }
}

const Vec2df& GameData::getCamera() const{
  return camera;
}