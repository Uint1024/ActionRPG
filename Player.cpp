#include "Player.h"
#include "Utils.h"
#include <iostream>
#include <SDL.h>
#include <cmath>

Player::Player() : BaseObject(){

}

Player::Player(std::string name_, int x_, int y_, eTexture texture_id_) : 
BaseObject(x_, y_, texture_id_),
name(name_){
  std::cout << "Calling Player constructor" << std::endl;
}

void Player::move(Point movement) {

}

void Player::receiveInput(std::map<eKey, bool> keys_down_){
  Point movement{0,0};
  float speed = 1000 * g_delta_t;
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
  
}

void Player::render(SDL_Renderer* renderer_, SDL_Texture* texture_, 
        std::map<eTexture, SDL_Rect>& texture_src_rect_){
  SDL_Rect dest_rect = SDL_Rect{(int)pos.x, (int)pos.y, 128, 128};
  SDL_RenderCopy(renderer_, texture_, 
          &texture_src_rect_[texture_id], 
          &dest_rect);
}