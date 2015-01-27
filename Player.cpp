#include "Player.h"
#include "Utils.h"
#include "GameData.h"
#include <iostream>
#include <SDL.h>
#include <cmath>

std::chrono::system_clock::time_point (&currentTime)() = 
        std::chrono::system_clock::now;

Player::Player() : Character(){

}

Player::Player(std::string name_, int x_, int y_, Vec2di size_) : 
        Character(x_, y_, eTexture::Player, size_, 100, 0),
        last_shot(std::chrono::system_clock::now()), 
        current_weapon(eWeapon::Shotgun){
  std::cout << "Calling Player constructor" << std::endl;
}

Vec2df Player::receiveInput(const std::map<eKey, bool>& keys_down_,
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
    current_weapon = eWeapon::Shotgun;
  }
  if(keys_down_.at(eKey::WeaponFire))
  {
    current_weapon = eWeapon::Fire;
  }
  
  checkCollisionWithStuff(walls_vector_, movement, bounding_box);
  
  pos.x += movement.x;
  pos.y += movement.y;
 
  updateBoundingBox(bounding_box, movement);
  
  
  int difference_now_and_last_shot = differenceTimes(currentTime(), last_shot);
  if(difference_now_and_last_shot > weapons_inventory[current_weapon].shooting_delay)
  {
    setDirectionFacing(movement);
  }
  
  if(mouse_buttons_down_[SDL_BUTTON_LEFT] )
  {
    if(difference_now_and_last_shot > 
            weapons_inventory.at(current_weapon).shooting_delay)
    {
      shoot(game_data_, mouse_position_in_world_);
    }  
  }
  
  return movement;
}

void Player::shoot(GameData* game_data_, const Vec2di& mouse_position_in_world_)
{
  float angle = std::atan2(
              mouse_position_in_world_.y - (pos.y + size.y / 2.0f), 
              mouse_position_in_world_.x - (pos.x + size.x / 2.0f));
  
  last_shot = currentTime();

  Vec2df player_center = {bounding_box.left + size.x/2.0f,
                          bounding_box.top +  size.y/2.0f};
  
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
  

  switch(current_weapon)
  {
    case eWeapon::Shotgun:
      shootShotgun(game_data_, player_center, angle);
      break;
    case eWeapon::Fire:
      shootFire(game_data_, player_center, angle);
      break;
    default:
      std::cout << "Unknown weapon!" << std::endl;
  }
}

void Player::shootShotgun(GameData* game_data_, const Vec2df& player_center_, 
        const float angle_)
{
  Vec2df origin = {player_center_.x + std::cos(angle_) * 32,
                   player_center_.y + std::sin(angle_) * 32};
  std::uniform_int_distribution<int> rand(
                                -weapons_inventory[current_weapon].spread,
                                weapons_inventory[current_weapon].spread);
  
  for(int i = 0 ; i < 5 ; i++)
  {
    
    float x = rand(g_mt19937) / 1000.0f;
    game_data_->createProjectile(origin, angle_ + x, 
                                 weapons_inventory[current_weapon].bullets_speed,
                                 weapons_inventory[current_weapon].damage);
  }
}

void Player::shootFire(GameData* game_data_, const Vec2df& player_center_, 
        const float angle_)
{
  Vec2df origin = {player_center_.x + std::cos(angle_) * 32,
                   player_center_.y + std::sin(angle_) * 32};
  std::uniform_int_distribution<int> rand(-400, 400);

    game_data_->createProjectile(origin, angle_, 
                                 weapons_inventory[current_weapon].bullets_speed,
                                 weapons_inventory[current_weapon].damage);
}