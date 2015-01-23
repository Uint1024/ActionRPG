#include "Player.h"
#include "Utils.h"
#include <iostream>
#include <SDL.h>
#include <cmath>

Player::Player() : Character(){

}

Player::Player(std::string name_, int x_, int y_) : 
        Character(x_, y_, name_){
  std::cout << "Calling Player constructor" << std::endl;
  texture_id = eTexture::Player;
}

void Player::move(Point movement) {

}

Point Player::receiveInput(std::map<eKey, bool>& keys_down_){
  Point movement{0,0};
  float speed = 500 * g_delta_t;
  float speed_diagonal = sqrt((speed * speed)/2);
  
  if(( keys_down_[eKey::Down] && keys_down_[eKey::Right]) ||
      (keys_down_[eKey::Down] && keys_down_[eKey::Left]) ||
      (keys_down_[eKey::Up] && keys_down_[eKey::Right]) ||
      (keys_down_[eKey::Up] && keys_down_[eKey::Left])){
    speed = speed_diagonal;
  }
 
  if(keys_down_[eKey::Down]){
    movement.y += speed;
  }
  if(keys_down_[eKey::Up]){
    movement.y -= speed;
  }
  if(keys_down_[eKey::Left]){
    movement.x -= speed;
  }
  if(keys_down_[eKey::Right]){
    movement.x += speed;
  }
  
  pos.x += movement.x;
  pos.y += movement.y;
  
  return movement;
}

