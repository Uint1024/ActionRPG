#include "Player.h"
#include "Utils.h"
#include "GameData.h"
#include <iostream>
#include <SDL.h>
#include <cmath>

Player::Player() : Character(){

}

Player::Player(std::string name_, int x_, int y_, Sizei size_) : 
        Character(x_, y_, eTexture::Player, size_, 100){
  std::cout << "Calling Player constructor" << std::endl;
}

void Player::move(Pointf movement) {

}

Sizef Player::receiveInput(const std::map<eKey, bool>& keys_down_,
        const std::array<bool, 255>& mouse_buttons_down_,
        GameData* game_data_,
        const Pointf& camera_, const Pointi& mouse_position_){
  
  if(mouse_buttons_down_[SDL_BUTTON_LEFT]){
    
    //TODO center angle
    float angle = std::atan2(mouse_position_.y - pos.y + camera_.y, 
            mouse_position_.x - pos.x + camera_.x);
    game_data_->createProjectile(pos, angle);
  }
  
  Sizef movement{0,0};
  float speed = 500 * g_delta_t;
  float speed_diagonal = sqrt((speed * speed)/2);
  
  if( (keys_down_.at(eKey::Down) && keys_down_.at(eKey::Right) ) ||
      (keys_down_.at(eKey::Down) && keys_down_.at(eKey::Left) ) ||
      (keys_down_.at(eKey::Up) && keys_down_.at(eKey::Right) ) ||
      (keys_down_.at(eKey::Up) && keys_down_.at(eKey::Left) ) ){
    speed = speed_diagonal;
  }
 
  if(keys_down_.at(eKey::Down)){
    movement.h += speed;
  }
  if(keys_down_.at(eKey::Up)){
    movement.h -= speed;
  }
  if(keys_down_.at(eKey::Left)){
    movement.w -= speed;
  }
  if(keys_down_.at(eKey::Right)){
    movement.w += speed;
  }
  
  pos.x += movement.w;
  pos.y += movement.h;
  
  updateBoundingBox(bounding_box, movement);
  return movement;
}

