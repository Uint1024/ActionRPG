#include "GameData.h"
#include "Player.h"
#include "Weapon.h"
#include "Utils.h"
#include "Shotgun.h"
#include "Ground.h"
#include "FastOrange.h"
#include "Zombie.h"
#include "Bomber.h"
#include "NPC.h"
#include "UI.h"

#include <vector>
#include <algorithm>
#include <memory>
#include <fstream>
int p = 0;

GameData::GameData(int screen_width_, int screen_height_) :
camera{0,0}, wave(1),
player(std::string("John"), Vec2df{screen_width_/2.0f - 64/2, 
          screen_height_/2.0f - 64/2},
          Vec2di{64,64}) , map_size{32, 32}       
{
  walls_size = 64;
  
  //TODO: move to SDLEngine... maybe
  textures_render_size.emplace(eTexture::Player, Vec2di{64, 64});
  textures_render_size.emplace(eTexture::Zombie, Vec2di{64, 64});
  textures_render_size.emplace(eTexture::FastOrange, Vec2di{64, 64});
  textures_render_size.emplace(eTexture::Bomber, Vec2di{64, 64});
  textures_render_size.emplace(eTexture::Wall, Vec2di{64,64});
  textures_render_size.emplace(eTexture::Projectile, Vec2di{32, 32});
  textures_render_size.emplace(eTexture::GroundGrey, Vec2di{64, 64});
  
  walls_vector.reserve(map_size.x * map_size.y);
  for(int i = 0 ; i < map_size.x * map_size.y ; i++)
  {
    walls_vector.emplace_back(std::unique_ptr<Wall>());
  } 
  
  ground_vector.reserve(map_size.x * map_size.y);
  for(int i = 0 ; i < map_size.x * map_size.y ; i++)
  {
    ground_vector.emplace_back(std::unique_ptr<Ground>());
  }  
  
  g_UI.initUI(&player);
  
  //filling projectiles vector with "dead" projectiles that will be used later
  projectiles_vector.reserve(512);
  for(int i = 0 ; i < 512 ; i++)
  {
    projectiles_vector.emplace_back(
              std::make_unique<Projectile>(true));
  }  
}

void 
GameData::render(SDL_Renderer* renderer_, SDL_Texture** texture_sheets_,
        const std::map<eTexture, std::map<eDirection, SDL_Rect>>&
                  dynamic_texture_src_rect_,
        const std::map<eTexture, SDL_Rect>& static_texture_src_rect,
        float zoom_level_)
{
     
  for(auto &ground : ground_vector)
  {
    if(ground)
    {
      ground->renderStatic(renderer_, texture_sheets_[TextureSheet_Ground], 
              static_texture_src_rect, 
            textures_render_size, camera, zoom_level_);
    }
  }
    
  player.renderDynamic(renderer_, texture_sheets_[TextureSheet_Characters], 
          dynamic_texture_src_rect_, 
          textures_render_size, camera, zoom_level_);
  if(player.getConditionsStates()[State_Burning])
  {
    player.renderBurningFlames(renderer_, texture_sheets_[TextureSheet_Characters],
            dynamic_texture_src_rect_, textures_render_size, camera);
  }
  
  for(auto &npc : npcs_vector)
  {
    npc->renderDynamic(renderer_, texture_sheets_[TextureSheet_Characters], 
            dynamic_texture_src_rect_, 
          textures_render_size, camera, zoom_level_);
    if(npc->getConditionsStates()[State_Burning])
    {
      npc->renderBurningFlames(renderer_, texture_sheets_[TextureSheet_Characters], 
              dynamic_texture_src_rect_, textures_render_size, camera);
    }
  }
  
  for (auto& i : projectiles_vector)
  {
    i->renderDynamic(renderer_, texture_sheets_[TextureSheet_Characters], 
            dynamic_texture_src_rect_, 
          textures_render_size, camera, zoom_level_);
  }
  
  for(auto &wall : walls_vector)
  {
    if(wall)
    {
      wall->renderStatic(renderer_, texture_sheets_[TextureSheet_Walls], 
              static_texture_src_rect, 
            textures_render_size, camera, zoom_level_);
    }
  }

}

void 
GameData::receiveInput(const std::map<eKey, bool>& keys_down_,
        const std::array<bool, 255>& mouse_buttons_down_, 
        const Vec2di& mouse_position_, 
        const Vec2di& mouse_position_in_world_)
{
  Vec2df camera_movement = player.receiveInput(keys_down_, mouse_buttons_down_,
          this, camera, mouse_position_in_world_, walls_vector);
  
  if(mouse_buttons_down_[SDL_BUTTON_RIGHT])
  {
    createObject(mouse_position_in_world_, eEditorObject::GreyGround);
  }
  if(mouse_buttons_down_[SDL_BUTTON_MIDDLE])
  {
    createObject(mouse_position_in_world_, eEditorObject::Wall);
  }
 
  camera.x += camera_movement.x;
  camera.y += camera_movement.y;
  
  /*
   * Saving map
   */
  if(keys_down_.at(eKey::Quick_Save))
  {
    std::cout <<"saving" << std::endl;
    std::ofstream out("quickSave.sav", std::ios::binary | std::ios::out);
    
    if(out.is_open())
    {
      out.write(reinterpret_cast<char *>(&map_size.x), sizeof(map_size.x));
      out.write(reinterpret_cast<char *>(&map_size.y), sizeof(map_size.y));
      
      for(auto &ground : ground_vector)
      {
        if(!ground)
        {
          bool is_ground = false;
          out.write(reinterpret_cast<char *>(&is_ground), sizeof(is_ground));
        }
        else
        {
          bool is_ground = true;
          Vec2df position = ground->getPos();
          Vec2di size = ground->getSize();
          eTexture texture_id = ground->getTextureId();
          
          out.write(reinterpret_cast<char *>(&is_ground), sizeof(is_ground));
          out.write(reinterpret_cast<char *>(&position.x), sizeof(position.x));
          out.write(reinterpret_cast<char *>(&position.y), sizeof(position.y));
          out.write(reinterpret_cast<char *>(&size.x), sizeof(size.x));
          out.write(reinterpret_cast<char *>(&size.y), sizeof(size.y));
          out.write(reinterpret_cast<char *>(&texture_id), sizeof(texture_id));
        }
      }
      
      for(auto &wall : walls_vector)
      {
        if(!wall)
        {
          bool is_wall = false;
          out.write(reinterpret_cast<char *>(&is_wall), sizeof(is_wall));
        }
        else
        {
          bool is_wall = true;
          Vec2df position = wall->getPos();
          Vec2di size = wall->getSize();
          eTexture texture_id = wall->getTextureId();
          
          out.write(reinterpret_cast<char *>(&is_wall), sizeof(is_wall));
          out.write(reinterpret_cast<char *>(&position.x), sizeof(position.x));
          out.write(reinterpret_cast<char *>(&position.y), sizeof(position.y));
          out.write(reinterpret_cast<char *>(&size.x), sizeof(size.x));
          out.write(reinterpret_cast<char *>(&size.y), sizeof(size.y));
          out.write(reinterpret_cast<char *>(&texture_id), sizeof(texture_id));
        }
      }
      
      /*for(auto &npc : npcs_vector)
      {
        if(!npc)
        {
          int no_npc = 0;
          out.write(reinterpret_cast<char *>(&no_npc), sizeof(no_npc));
        }
        else
        {
          int yes_wall = 1;
          float position_x = wall->getPos().x;
          float position_y = wall->getPos().y;
          int size_x = wall->getSize().x;
          int size_y = wall->getSize().y;
          eTexture texture_id = wall->getTextureId();
          
          out.write(reinterpret_cast<char *>(&yes_wall), sizeof(yes_wall));
          out.write(reinterpret_cast<char *>(&position_x), sizeof(position_x));
          out.write(reinterpret_cast<char *>(&position_y), sizeof(position_y));
          out.write(reinterpret_cast<char *>(&size_x), sizeof(size_x));
          out.write(reinterpret_cast<char *>(&size_y), sizeof(size_y));
          out.write(reinterpret_cast<char *>(&texture_id), sizeof(texture_id));
        }
      }*/
    } 
  }
  
  /*
   * Loading map
   */
  if(keys_down_.at(eKey::Quick_Load))
  {
    std::cout <<  "loading" << std::endl;
    std::ifstream in("quickSave.sav", std::ios::binary | std::ios::in);
    
    if(in.is_open())
    {
      in.read(reinterpret_cast<char *>(&map_size.x), sizeof(map_size.x));
      in.read(reinterpret_cast<char *>(&map_size.y), sizeof(map_size.y));
      ground_vector.clear();
      ground_vector.reserve(map_size.x * map_size.y);
      for(int i = 0 ; i < map_size.x * map_size.y ; i++)
      {
        ground_vector.emplace_back(std::unique_ptr<Ground>());
      }
      
      for(int i = 0 ; i < map_size.x * map_size.y ; i++)
      {  
        bool is_ground = false;
        in.read((char*)&is_ground, sizeof(is_ground));
        if(is_ground)
        {
          Vec2df position = {0.0f, 0.0f};
          Vec2di size = {0, 0};
          eTexture texture_id = eTexture::None;
          
          in.read(reinterpret_cast<char *>(&position.x), sizeof(position.x));
          in.read(reinterpret_cast<char *>(&position.y), sizeof(position.y));
          
          in.read(reinterpret_cast<char *>(&size.x), sizeof(size.x));
          in.read(reinterpret_cast<char *>(&size.y), sizeof(size.y));
          in.read(reinterpret_cast<char *>(&texture_id), sizeof(texture_id)); 
          ground_vector[i] = std::make_unique<Ground>(position);
        }
      }
      
      walls_vector.clear();
      walls_vector.reserve(map_size.x * map_size.y);
      for(int i = 0 ; i < map_size.x * map_size.y ; i++)
      {
        walls_vector.emplace_back(std::unique_ptr<Wall>());
      }
      
      for(int i = 0 ; i < map_size.x * map_size.y ; i++)
      {  
        bool is_wall = false;
        in.read((char*)&is_wall, sizeof(is_wall));
        
        if(is_wall)
        {
          Vec2df position = {0.0f, 0.0f};
          Vec2di size = {0, 0};
          eTexture texture_id = eTexture::None;
          in.read(reinterpret_cast<char *>(&position.x), sizeof(position.x));
          in.read(reinterpret_cast<char *>(&position.y), sizeof(position.y));
          
          in.read(reinterpret_cast<char *>(&size.x), sizeof(size.x));
          in.read(reinterpret_cast<char *>(&size.y), sizeof(size.y));
          in.read(reinterpret_cast<char *>(&texture_id), sizeof(texture_id)); 
          walls_vector[i] = std::make_unique<Wall>(position);
        }
      }
    }
  }
}

void 
GameData::createObject(const Vec2di& mouse_position_in_world_,
                        const eEditorObject type_)
{
  Vec2di tile = {mouse_position_in_world_.x / walls_size,
                  mouse_position_in_world_.y / walls_size};
  
  std::cout << tile.x << " " << tile.y << " " << map_size.x << " " << map_size.y << std::endl;
  
  if (tile.x > 0 && tile.x < map_size.x && tile.y > 0 && tile.y < map_size.y)
  {
    
    int position_in_array = tile.y * map_size.x + tile.x;
    Vec2df position_of_wall = {static_cast<float>(tile.x * walls_size), 
                              static_cast<float>(tile.y * walls_size)};
    if(type_ == eEditorObject::Wall)
    {
      walls_vector[position_in_array] = std::make_unique<Wall>(position_of_wall);
    }
    if(type_ == eEditorObject::GreyGround)
    {
      
      ground_vector[position_in_array] = std::make_unique<Ground>(position_of_wall);
    }
  }
 }


void 
GameData::update()
{

  g_UI.update(player);
  
  player.update();
  
  for(auto projectile = projectiles_vector.begin() ; 
          projectile != projectiles_vector.end() ;
          ++projectile)
  {
    if(!(*projectile)->isDead())
    {
      (*projectile)->update(walls_vector, npcs_vector);
    }
  }
  
  for(auto npc = npcs_vector.begin() ; npc != npcs_vector.end() ;)
  {
    if((*npc)->isDead())
    {
      npcs_vector.erase(npc);
    }
    else
    {
      (*npc)->update(player, walls_vector, npcs_vector);
      (*npc)->updateConditionState();
      ++npc;
    }
  }
   
  
  if(npcs_vector.size() < 10)
  {
    std::uniform_int_distribution<int> y_top(-300, 0);
    std::uniform_int_distribution<int> x_top_bottom(-100, 900);
    std::uniform_int_distribution<int> x_left(-300, -100);
    std::uniform_int_distribution<int> x_right(900, 1100);
    std::uniform_int_distribution<int> y_bottom(900, 1100);
    std::uniform_int_distribution<int> y_left_right(0, 900);
    std::uniform_int_distribution<int> which_side(0, 1);
    int p = x_right(g_mt19937);
    
    switch(wave)
    {
      case 1:
        for(int i = 0 ; i < 300 ; ++i){
          int side = which_side(g_mt19937);
          int x = 0;
          int y = 0;
          switch(side)
          {
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
          
          npcs_vector.emplace_back(std::make_unique<Bomber>(
                    Vec2df{(float)x, (float)y}, textures_render_size[eTexture::FastOrange]));
        }
        break;
      default:
        std::cout << "Out of waves, game over!" << std::endl;
        break;
    }
  }
}

void 
GameData::createProjectile(const Vec2df origin_, const float angle_,
                           const int speed_, const int damage_,
                           Weapon* shot_by_)
{
  auto dead_projectile = std::find_if(projectiles_vector.begin(), 
                                projectiles_vector.end(), 
                                [](auto &projec) {
                                  return projec->isDead(); 
                                });
                                
                                
  if(dead_projectile != projectiles_vector.end()){
    (*dead_projectile)->renew(origin_, false, speed_, angle_, 
                              damage_, eElement::Fire,
                              textures_render_size[eTexture::Projectile],
                              shot_by_);
  }
  else
  {
    std::cout << "Error, no dead projectile available!" << std::endl;
  }
}

const Vec2df& 
GameData::getCamera() const
{
  return camera;
}