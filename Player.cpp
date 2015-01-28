#include "Player.h"
#include "Utils.h"
#include "Shotgun.h"
#include "Fire.h"
#include "GameData.h"
#include <iostream>
#include <SDL.h>
#include <cmath>

std::chrono::system_clock::time_point (&currentTime)() = 
        std::chrono::system_clock::now;

Player::Player() : Character()
{

}

Player::Player(std::string name_, int x_, int y_, Vec2di size_) : 
        Character(x_, y_, eTexture::Player, size_, 100, 0),
        last_shot(std::chrono::system_clock::now()), 
        current_weapon(nullptr)
{
  std::cout << "Calling Player constructor" << std::endl;
  weapons_inventory[(int)eWeapon::Shotgun] = std::make_unique<Shotgun>();
  weapons_inventory[(int)eWeapon::Fire] = std::make_unique<Fire>();
  
  current_weapon = &*weapons_inventory[(int)eWeapon::Shotgun];
}

Vec2df 
Player::receiveInput(const std::map<eKey, bool>& keys_down_,
        const std::array<bool, 255>& mouse_buttons_down_,
        GameData* game_data_,
        const Vec2df& camera_, const Vec2di& mouse_position_in_world_,
        const std::vector<std::unique_ptr<Wall>>& walls_vector_)
{ 
  Vec2df movement{0,0};
  float speed = 500 * g_delta_t;
  float speed_diagonal = sqrt((speed * speed)/2);
  
  if( (keys_down_.at(eKey::Down) && keys_down_.at(eKey::Right) ) ||
      (keys_down_.at(eKey::Down) && keys_down_.at(eKey::Left) ) ||
      (keys_down_.at(eKey::Up) && keys_down_.at(eKey::Right) ) ||
      (keys_down_.at(eKey::Up) && keys_down_.at(eKey::Left) ) )
  {
    speed = speed_diagonal;
  }
 
  if(keys_down_.at(eKey::Down))
  {
    movement.y += speed;
  }
  if(keys_down_.at(eKey::Up))
  {
    movement.y -= speed;
  }
  if(keys_down_.at(eKey::Left))
  {
    movement.x -= speed;
  }
  if(keys_down_.at(eKey::Right))
  {
    movement.x += speed;
  }
  
  if(keys_down_.at(eKey::WeaponShotgun))
  {
    if(weapons_inventory[(int)eWeapon::Shotgun])
    {
      current_weapon = &*weapons_inventory[(int)eWeapon::Shotgun];
    }
  }
  if(keys_down_.at(eKey::WeaponFire))
  {
    if(weapons_inventory[(int)eWeapon::Fire])
    {
      current_weapon = &*weapons_inventory[(int)eWeapon::Fire];
    }
  }
  
  checkCollisionWithStuff(walls_vector_, movement, bounding_box);
  
  pos.x += movement.x;
  pos.y += movement.y;
 
  updateBoundingBox(bounding_box, movement);
  
  
  int difference_now_and_last_shot = differenceTimes(currentTime(), last_shot);
  
  bool enough_time_passed_to_shoot = difference_now_and_last_shot > 
                          current_weapon->getShootingDelay();
  
  if(enough_time_passed_to_shoot)
  {  
    if(mouse_buttons_down_[SDL_BUTTON_LEFT])
    {
      shoot(game_data_, mouse_position_in_world_);
    }
    else
    {
      setDirectionFacing(movement);
    }
  }
 
  return movement;
}

void 
Player::shoot(GameData* game_data_, const Vec2di& mouse_position_in_world_)
{
  float angle = std::atan2(
              mouse_position_in_world_.y - (pos.y + size.y / 2.0f), 
              mouse_position_in_world_.x - (pos.x + size.x / 2.0f));
  
  last_shot = currentTime();

  Vec2df player_center = {bounding_box.left + size.x/2.0f,
                          bounding_box.top +  size.y/2.0f};
  
  current_weapon->shoot(game_data_, player_center, angle);
  if(mouse_position_in_world_.y >= player_center.y)
  {
    if(mouse_position_in_world_.x > player_center.x){
      direction_facing = eDirection::DownRight;
    }
    if(mouse_position_in_world_.x < player_center.x){
      direction_facing = eDirection::DownLeft;
    }
  }
  else
  {
    if(mouse_position_in_world_.x > player_center.x)
    {
      direction_facing = eDirection::UpRight;
    }
    if(mouse_position_in_world_.x < player_center.x)
    {
      direction_facing = eDirection::UpLeft;
    }
  }
}