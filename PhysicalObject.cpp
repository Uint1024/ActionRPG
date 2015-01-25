#include "PhysicalObject.h"
#include "Utils.h"
#include "Wall.h"
#include <iostream>

PhysicalObject::PhysicalObject(){}

PhysicalObject::PhysicalObject(int x_, int y_, 
        eTexture texture_id_, Vec2di size_) : 
        pos{(float)x_, (float)y_}, texture_id(texture_id_), size(size_){
  bounding_box = Rect{(float)x_, (float)y_, 
          (float)(x_ + size_.x), (float)(y_ + size_.y)};
}

void PhysicalObject::render(SDL_Renderer* renderer_, SDL_Texture* texture_, 
        const std::map<eTexture,SDL_Rect>& texture_src_rect_, 
        const std::map<eTexture,Vec2di>& textures_render_size_, 
        const Vec2df& camera_, const float zoom_level_) const{
  
  SDL_Rect dest_rect = SDL_Rect{(int)((pos.x - camera_.x) * zoom_level_), 
          (int)((pos.y - camera_.y) * zoom_level_), 
          (int)(textures_render_size_.at(texture_id).x * zoom_level_), 
          (int)(textures_render_size_.at(texture_id).y * zoom_level_)};
          
  SDL_RenderCopy(renderer_, texture_, 
          &texture_src_rect_.at(texture_id), 
          &dest_rect);
  
  SDL_Rect bbox = {(int)(bounding_box.left - camera_.x), 
                    (int)(bounding_box.top - camera_.y), 
                    size.x, size.y};
  SDL_RenderDrawRect(renderer_, &bbox);
  
}


bool PhysicalObject::checkCollision(const PhysicalObject& other_) const{
  return other_.checkCollision(bounding_box);
}


bool PhysicalObject::checkCollision(const Rect& bounding_box_) const{
  return !(bounding_box_.left > bounding_box.right ||
          bounding_box_.right < bounding_box.left ||
          bounding_box_.top > bounding_box.bottom ||
          bounding_box_.bottom < bounding_box.top);
}

/*Move PhysicalObject and update its bounding box
 return the movement*/
const Vec2df PhysicalObject::move(const float angle_, const int speed, 
        const std::vector<Wall>& walls_vector_) {
  Vec2df movement = { std::cos(angle_) * speed,
                    std::sin(angle_) * speed };
  
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


const Rect* PhysicalObject::checkCollisionWithObject(const Rect& future_bbox_, 
        const Rect& other_bbox_, eDirection& direction_){
  eDirection current_position = eDirection::None;
  
  if(bounding_box.right <= other_bbox_.left){
    current_position = eDirection::Left;
  }
  else if(bounding_box.left >= other_bbox_.right){
    current_position = eDirection::Right;
  }
  else if(bounding_box.bottom <= other_bbox_.top){
    current_position = eDirection::Up;
  }
  else if(bounding_box.top >= other_bbox_.bottom){
    current_position = eDirection::Down;
  }
  
  
  if(current_position == eDirection::Up &&
          future_bbox_.bottom > other_bbox_.top &&
          future_bbox_.top < other_bbox_.top &&
          future_bbox_.right > other_bbox_.left &&
          future_bbox_.left < other_bbox_.right){
    direction_ = eDirection::Down;
    return &other_bbox_;
  }
  else if(current_position == eDirection::Down &&
          future_bbox_.top < other_bbox_.bottom &&
          future_bbox_.bottom > other_bbox_.bottom &&
          future_bbox_.right > other_bbox_.left &&
          future_bbox_.left < other_bbox_.right){
    direction_ = eDirection::Up;
    return &other_bbox_;
  }
  else if(current_position == eDirection::Left &&
          future_bbox_.right > other_bbox_.left &&
          future_bbox_.left < other_bbox_.left &&
          future_bbox_.bottom > other_bbox_.top &&
          future_bbox_.top < other_bbox_.bottom){
    direction_ = eDirection::Right;
    return &other_bbox_;
  }
  else if(current_position == eDirection::Right &&
          future_bbox_.left < other_bbox_.right &&
          future_bbox_.right > other_bbox_.right &&
          future_bbox_.bottom > other_bbox_.top &&
          future_bbox_.top < other_bbox_.bottom){
    direction_ = eDirection::Left;
    return &other_bbox_;
  }
  direction_ = eDirection::None;
  return nullptr;
}


const Vec2df& PhysicalObject::getPos() const{
  return pos;
}

const Vec2di& PhysicalObject::getSize() const{
  return size;
}

const Rect& PhysicalObject::getBoundingBox() const{
  return bounding_box;
}

