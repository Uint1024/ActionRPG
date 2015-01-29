#include "PhysicalObject.h"
#include "Utils.h"
#include "Wall.h"
#include "NPC.h"
#include <iostream>

PhysicalObject::PhysicalObject(){}

PhysicalObject::PhysicalObject(int x_, int y_, 
        eTexture texture_id_, Vec2di size_) : 
        pos{(float)x_, (float)y_}, texture_id(texture_id_), size(size_),
        direction_facing(eDirection::DownLeft)
{  
  bounding_box = Rect{(float)x_, (float)y_, 
          (float)(x_ + size_.x), (float)(y_ + size_.y)};
  center = {x_ + size_.x/2.0f, y_ + size_.y/2.0f};
}


void 
PhysicalObject::renderDynamic(SDL_Renderer* renderer_, SDL_Texture* texture_, 
                      const std::map<eTexture, std::map<eDirection, SDL_Rect>>& 
                          dynamic_texture_src_rect_,
                      const std::map<eTexture,Vec2di>& textures_render_size_, 
                      const Vec2df& camera_, const float zoom_level_) const
{
  SDL_Rect dest_rect = getRectOfSprite(pos, camera_, 
                    textures_render_size_.at(texture_id));
         
  
  if(direction_facing == eDirection::DownLeft)
  {
    SDL_RenderCopy(renderer_, texture_, 
            &dynamic_texture_src_rect_.at(texture_id).at(eDirection::Front), 
            &dest_rect);
  }
  else if(direction_facing == eDirection::DownRight)
  {
    SDL_RenderCopyEx(renderer_, texture_, 
          &dynamic_texture_src_rect_.at(texture_id).at(eDirection::Front), 
          &dest_rect, 0, NULL, SDL_FLIP_HORIZONTAL);
  }
  else if(direction_facing == eDirection::UpLeft)
  {
    SDL_RenderCopy(renderer_, texture_, 
            &dynamic_texture_src_rect_.at(texture_id).at(eDirection::Back), 
            &dest_rect);
  }
  else if(direction_facing == eDirection::UpRight)
  {
    SDL_RenderCopyEx(renderer_, texture_, 
          &dynamic_texture_src_rect_.at(texture_id).at(eDirection::Back), 
          &dest_rect, 0, NULL, SDL_FLIP_HORIZONTAL);
  }
         
         
  
  SDL_Rect bbox = {(int)(bounding_box.left - camera_.x), 
                    (int)(bounding_box.top - camera_.y), 
                    size.x, size.y};
  SDL_RenderDrawRect(renderer_, &bbox);

  
}

void 
PhysicalObject::renderStatic(SDL_Renderer* renderer_, 
        SDL_Texture* texture_, 
        const std::map<eTexture, SDL_Rect>& static_texture_src_rect, 
        const std::map<eTexture, Vec2di>& textures_render_size_, 
        const Vec2df& camera_, const float zoom_level_) const 
{
  SDL_Rect dest_rect = getRectOfSprite(pos, camera_, 
                    textures_render_size_.at(texture_id));
          
  SDL_RenderCopy(renderer_, texture_, 
            &static_texture_src_rect.at(texture_id), 
            &dest_rect);
}

void
PhysicalObject::renderBurningFlames(SDL_Renderer* renderer_, 
        SDL_Texture* texture_, 
        const std::map<eTexture, std::map<eDirection, SDL_Rect>>& 
                          dynamic_texture_src_rect_,
        const std::map<eTexture,Vec2di>& textures_render_size_, 
        const Vec2df& camera_) const
{
  SDL_Rect dest_rect = getRectOfSprite(pos, camera_, 
                    textures_render_size_.at(texture_id));
          
  SDL_RenderCopy(renderer_, texture_, 
            &dynamic_texture_src_rect_.at(eTexture::Burning).at(eDirection::Front), 
            &dest_rect);
}


bool 
PhysicalObject::checkCollision(const PhysicalObject& other_) const
{
  return other_.checkCollision(bounding_box);
}


bool 
PhysicalObject::checkCollision(const Rect& bounding_box_) const
{
  return !(bounding_box_.left > bounding_box.right ||
          bounding_box_.right < bounding_box.left ||
          bounding_box_.top > bounding_box.bottom ||
          bounding_box_.bottom < bounding_box.top);
}

const Rect* 
PhysicalObject::checkCollisionWithBoundingBox(
        const Rect& future_bbox_, 
        const Rect& other_bbox_, eDirection& direction_)
{
  eDirection current_position = eDirection::None;
  
  if(bounding_box.right <= other_bbox_.left)
  {
    current_position = eDirection::Left;
  }
  else if(bounding_box.left >= other_bbox_.right)
  {
    current_position = eDirection::Right;
  }
  else if(bounding_box.bottom <= other_bbox_.top)
  {
    current_position = eDirection::Up;
  }
  else if(bounding_box.top >= other_bbox_.bottom)
  {
    current_position = eDirection::Down;
  }
  
  
  if(current_position == eDirection::Up &&
          future_bbox_.bottom > other_bbox_.top &&
          future_bbox_.top < other_bbox_.top &&
          future_bbox_.right > other_bbox_.left &&
          future_bbox_.left < other_bbox_.right)
  {
    direction_ = eDirection::Down;
    return &other_bbox_;
  }
  else if(current_position == eDirection::Down &&
          future_bbox_.top < other_bbox_.bottom &&
          future_bbox_.bottom > other_bbox_.bottom &&
          future_bbox_.right > other_bbox_.left &&
          future_bbox_.left < other_bbox_.right)
  {
    direction_ = eDirection::Up;
    return &other_bbox_;
  }
  else if(current_position == eDirection::Left &&
          future_bbox_.right > other_bbox_.left &&
          future_bbox_.left < other_bbox_.left &&
          future_bbox_.bottom > other_bbox_.top &&
          future_bbox_.top < other_bbox_.bottom)
  {
    direction_ = eDirection::Right;
    return &other_bbox_;
  }
  else if(current_position == eDirection::Right &&
          future_bbox_.left < other_bbox_.right &&
          future_bbox_.right > other_bbox_.right &&
          future_bbox_.bottom > other_bbox_.top &&
          future_bbox_.top < other_bbox_.bottom)
  {
    direction_ = eDirection::Left;
    return &other_bbox_;
  }
  direction_ = eDirection::None;
  return nullptr;
}

void 
PhysicalObject::setDirectionFacing(const Vec2df& movement_)
{ 
  bool left, right, up, down = false;
  
  if(movement_.x < 0)
    left = true;
  if(movement_.x > 0)
    right = true;
  if(movement_.y < 0)
    up = true;
  if(movement_.y > 0)
    down = true;
  
  
  if(direction_facing == eDirection::UpLeft ||
                direction_facing == eDirection::UpRight)
  {
    if(right)
    {
      if(down)
      {
        direction_facing = eDirection::DownRight;
        return;
      }
      direction_facing = eDirection::UpRight;
      return;
    }

    if(left)
    {
      if(down)
      {
        direction_facing = eDirection::DownLeft;
        return;
      }
      direction_facing = eDirection::UpLeft;
      return;  
    }
    
    if(down)
    {
      direction_facing = eDirection::DownLeft;
      return;
    }
  }
  
  if(direction_facing == eDirection::DownLeft ||
                direction_facing == eDirection::DownRight){
    if(right)
    {
      if(up)
      {
        direction_facing = eDirection::UpRight;
        return;
      }
      else
      {
        direction_facing = eDirection::DownRight;
        return;
      } 
    }

    if(left)
    {
      if(up)
      {
        direction_facing = eDirection::UpLeft;
        return;
      }
      else
      {
        direction_facing = eDirection::DownLeft;
        return;
      }
    }
    
    if(up){
      direction_facing = eDirection::UpLeft;
      return;
    }
  }
 
}

const Vec2df& 
PhysicalObject::getPos() const
{
  return pos;
}

const Vec2di& 
PhysicalObject::getSize() const
{
  return size;
}

const Rect& 
PhysicalObject::getBoundingBox() const
{
  return bounding_box;
}

Vec2df 
PhysicalObject::getCenter() const
{
  return {pos.x + size.x/2.0f, pos.y + size.y/2.0f};
}

