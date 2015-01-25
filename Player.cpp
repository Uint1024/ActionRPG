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
        const std::vector<Wall> walls_vector_){
  
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
  
  Rect future_bbox = bounding_box;
  updateBoundingBox(future_bbox, movement);
  
  const Rect* wall_direction[4] = {nullptr, nullptr, nullptr, nullptr};
  
  eDirection blocked_direction = eDirection::None;
  
  for(auto &wall : walls_vector_){
    const Rect* blocked_by = checkCollisionWithObject(future_bbox, 
                                            wall.getBoundingBox(), 
                                            blocked_direction);
    if(blocked_direction != eDirection::None){
      wall_direction[(int)blocked_direction] = blocked_by;
    }
  }
  
  if(wall_direction[(int)eDirection::Right]){
    movement.x = wall_direction[(int)eDirection::Right]->left -
            bounding_box.right;
  }
  if(wall_direction[(int)eDirection::Left]){
    movement.x = 
            wall_direction[(int)eDirection::Left]->right -
            bounding_box.left; 
  }
  if(wall_direction[(int)eDirection::Up]){
    movement.y = 
            wall_direction[(int)eDirection::Up]->bottom -
            bounding_box.top;
            
  }
  if(wall_direction[(int)eDirection::Down]){
    movement.y = wall_direction[(int)eDirection::Down]->top -
            bounding_box.bottom;
  }
  
  pos.x += movement.x;
  pos.y += movement.y;
  
 
  updateBoundingBox(bounding_box, movement);
  return movement;
}