#include "PhysicalObject.h"
#include "Utils.h"
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
const Vec2df PhysicalObject::move(const float angle_, const int speed) {
  Vec2df movement = { std::cos(angle_) * speed,
                    std::sin(angle_) * speed };
  pos.x += movement.x;
  pos.y += movement.y;
 
  updateBoundingBox(bounding_box, movement);
  
  return movement;
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