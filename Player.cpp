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
  
  const Wall* wall_direction[4] = {nullptr, nullptr, nullptr, nullptr};
  
  Wall* wall_down = nullptr;
  Wall* wall_up = nullptr;
  Wall* wall_left = nullptr;
  Wall* wall_right = nullptr;
  
  eDirection blocked_direction = eDirection::None;
  
  for(auto &wall : walls_vector_){
    //blocked_direction = eDirection::None;
    const Wall* blocked_by = checkCollisionWithWall(future_bbox, wall, blocked_direction);
    if(blocked_direction != eDirection::None){
      wall_direction[(int)blocked_direction] = blocked_by;
    }
  }
  
  if(wall_direction[(int)eDirection::Right]){
    movement.x = wall_direction[(int)eDirection::Right]->getBoundingBox().left -
            bounding_box.right;
  }
  if(wall_direction[(int)eDirection::Left]){
    movement.x = 
            wall_direction[(int)eDirection::Left]->getBoundingBox().right -
            bounding_box.left; 
  }
  if(wall_direction[(int)eDirection::Up]){
    movement.y = 
            wall_direction[(int)eDirection::Up]->getBoundingBox().bottom -
            bounding_box.top;
            
  }
  if(wall_direction[(int)eDirection::Down]){
    movement.y = wall_direction[(int)eDirection::Down]->getBoundingBox().top -
            bounding_box.bottom;
  }
  
  pos.x += movement.x;
  pos.y += movement.y;
  
  
  /*if( (movement.x > 0 && !wall_direction[(int)eDirection::Right]) ||
      (movement.x < 0 && !wall_direction[(int)eDirection::Left]) ){
    pos.x += movement.x;
  }
  else{
    if(wall_direction[(int)eDirection::Right])){
      
    }
    movement.x = 0;
  }
  
  if( (movement.y > 0 && !wall_direction[(int)eDirection::Down]) ||
      (movement.y < 0 && !wall_direction[(int)eDirection::Up]) ){
    pos.y += movement.y;
  }
  else{
    movement.y = 0;
  }*/
  
  updateBoundingBox(bounding_box, movement);
  return movement;
}

const Wall* Player::checkCollisionWithWall(const Rect& future_bbox, 
        const Wall& wall_, eDirection& direction_){
  eDirection current_position = eDirection::None;
  
  const Rect* wall_bbox = &wall_.getBoundingBox();
  
  if(bounding_box.right <= wall_bbox->left){
    current_position = eDirection::Left;
  }
  else if(bounding_box.left >= wall_bbox->right){
    current_position = eDirection::Right;
  }
  else if(bounding_box.bottom <= wall_bbox->top){
    current_position = eDirection::Up;
  }
  else if(bounding_box.top >= wall_bbox->bottom){
    current_position = eDirection::Down;
  }
  
  
  if(current_position == eDirection::Up &&
          future_bbox.bottom > wall_bbox->top &&
          future_bbox.top < wall_bbox->top &&
          future_bbox.right > wall_bbox->left &&
          future_bbox.left < wall_bbox->right){
    direction_ = eDirection::Down;
    return &wall_;
  }
  else if(current_position == eDirection::Down &&
          future_bbox.top < wall_bbox->bottom &&
          future_bbox.bottom > wall_bbox->bottom &&
          future_bbox.right > wall_bbox->left &&
          future_bbox.left < wall_bbox->right){
    direction_ = eDirection::Up;
    return &wall_;
  }
  else if(current_position == eDirection::Left &&
          future_bbox.right > wall_bbox->left &&
          future_bbox.left < wall_bbox->left &&
          future_bbox.bottom > wall_bbox->top &&
          future_bbox.top < wall_bbox->bottom){
    direction_ = eDirection::Right;
    return &wall_;
  }
  else if(current_position == eDirection::Right &&
          future_bbox.left < wall_bbox->right &&
          future_bbox.right > wall_bbox->right &&
          future_bbox.bottom > wall_bbox->top &&
          future_bbox.top < wall_bbox->bottom){
    direction_ = eDirection::Left;
    return &wall_;
  }
  direction_ = eDirection::None;
  return nullptr;
}