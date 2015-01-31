#include "Player.h"
#include "Utils.h"
#include "Shotgun.h"
#include "Fire.h"
#include "GameData.h"
#include <iostream>
#include <SDL.h>
#include <cmath>
#include <chrono>

Player::Player() : Character()
{

}

Player::Player(const std::string& name_, const Vec2df& position_, 
        const Vec2di& size_) : 
        Character(position_, eTexture::Player, size_, 100, 0),
        last_shot(std::chrono::system_clock::now()), 
        current_weapon(nullptr), reloading(false)
{
  std::cout << "Calling Player constructor" << std::endl;
  weapons_inventory[(int)eWeapon::Shotgun] = std::make_unique<Shotgun>(this);
  weapons_inventory[(int)eWeapon::Fire] = std::make_unique<Fire>(this);
  
  current_weapon = &*weapons_inventory[(int)eWeapon::Shotgun];
  
 // conditions_states[State_Burning] = new ConditionState{5000, 5000};
}

void 
Player::update() 
{
  updateConditionState();
  current_weapon->update();
  if(reloading)
  {
    reload();
  }
  
  //cool down weapons that can overheat
  weapons_inventory[(int)eWeapon::Fire]->update();
}

void
Player::reload()
{
  if(!reloading)
  {
    reloading = true;
  }
  else
  {
    current_weapon->reload();
  }
}

void
Player::stopReloading()
{
  reloading = false;
}


Vec2df 
Player::receiveInput(const std::map<eKey, bool>& keys_down_,
        const std::array<bool, 255>& mouse_buttons_down_,
        GameData* game_data_,
        const Vec2df& camera_, const Vec2di& mouse_position_in_world_,
        const std::vector<std::unique_ptr<Wall>>& walls_vector_)
{ 
  Vec2df movement{0,0};
  float speed = 0.5f * g_delta_t;
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
  
  checkCollisionWithWalls(walls_vector_, movement);
  
  pos.x += movement.x;
  pos.y += movement.y;
 
  updateBoundingBox(bounding_box, movement);
   
  if(mouse_buttons_down_[SDL_BUTTON_LEFT])
  {
    shoot(game_data_, mouse_position_in_world_);
  }
  else
  {
    setDirectionFacing(movement);
  }
  
 
  return movement;
}

void 
Player::shoot(GameData* game_data_, const Vec2di& mouse_position_in_world_)
{
  stopReloading();
  
  float angle = std::atan2(
              mouse_position_in_world_.y - (pos.y + size.y / 2.0f), 
              mouse_position_in_world_.x - (pos.x + size.x / 2.0f));
  
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

std::pair<int, int> 
Player::getAmmo() const 
{
  return current_weapon->getAmmo();
}

Weapon* Player::getCurrentWeapon() const 
{
  return current_weapon;
}
