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
        last_shot(std::chrono::system_clock::now()){
  std::cout << "Calling Player constructor" << std::endl;
}


Vec2df Player::receiveInput(const std::map<eKey, bool>& keys_down_,
        const std::array<bool, 255>& mouse_buttons_down_,
        GameData* game_data_,
        const Vec2df& camera_, const Vec2di& mouse_position_in_world_,
        const std::vector<std::unique_ptr<Wall>>& walls_vector_){
  
  if(mouse_buttons_down_[SDL_BUTTON_LEFT] ){
    if(differenceTimes(currentTime(), last_shot) > 100){
      float angle = std::atan2(
              mouse_position_in_world_.y - (pos.y + size.y / 2.0f), 
              mouse_position_in_world_.x - (pos.x + size.x / 2.0f));
      game_data_->createProjectile(pos, angle);
      last_shot = currentTime();
    }
    
  }
  
  Vec2df movement{0,0};
  float speed = 500 * g_delta_t;
  float speed_diagonal = sqrt((speed * speed)/2);
  
  if( (keys_down_.at(eKey::Down) && keys_down_.at(eKey::Right) ) ||
      (keys_down_.at(eKey::Down) && keys_down_.at(eKey::Left) ) ||
      (keys_down_.at(eKey::Up) && keys_down_.at(eKey::Right) ) ||
      (keys_down_.at(eKey::Up) && keys_down_.at(eKey::Left) ) ){
    speed = speed_diagonal;
  }
 
  if(keys_down_.at(eKey::Down)){
    movement.y += speed;
  }
  if(keys_down_.at(eKey::Up)){
    movement.y -= speed;
  }
  if(keys_down_.at(eKey::Left)){
    movement.x -= speed;
  }
  if(keys_down_.at(eKey::Right)){
    movement.x += speed;
  }
  
  //checkCollisionWithStuff(walls_vector_, movement, bounding_box);
  
  pos.x += movement.x;
  pos.y += movement.y;
  
 
  updateBoundingBox(bounding_box, movement);
  return movement;
}