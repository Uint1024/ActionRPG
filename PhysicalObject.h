/* * Physical objects are objects that can be rendered
 */

#pragma once
#include "Utils.h"

class NPC;


#include <SDL.h>
#include <map>
#include <iostream>
#include <memory>

class PhysicalObject{
public:
  void renderDynamic(SDL_Renderer* renderer_,
          SDL_Texture* texture_,
          const std::map<eTexture, std::map<eDirection, SDL_Rect>>& 
                  dynamic_texture_src_rect_,
          const std::map<eTexture, Vec2di>& textures_render_size_,
          const Vec2df& camera_,
          const float zoom_level_) const;
  
  void renderStatic(SDL_Renderer* renderer_,
          SDL_Texture* texture_,
          const std::map<eTexture, SDL_Rect>& static_texture_src_rect,
          const std::map<eTexture, Vec2di>& textures_render_size_,
          const Vec2df& camera_,
          const float zoom_level_) const;
  
  void renderBurningFlames(SDL_Renderer* renderer_,
          SDL_Texture* texture_,
          const std::map<eTexture, std::map<eDirection, SDL_Rect>>& 
                          dynamic_texture_src_rect_,
          const std::map<eTexture, Vec2di>& textures_render_size_,
          const Vec2df& camera_) const;
  
//#include "PhysicalObjectTemplates.hpp"
  
  
  const Rect* checkCollisionWithBoundingBox(const Rect& future_bbox_, 
                          const Rect& other_bbox, eDirection& direction_);
  
  const Vec2df& getPos() const;
  const Vec2di& getSize() const;
  Vec2df getCenter() const;
  const Rect& getBoundingBox() const;
  void setDirectionFacing(const Vec2df& movement_);
  
protected:
  //protected constructor ensures BaseObject can't be created alone
  PhysicalObject();
  PhysicalObject(const Vec2df& position_, const eTexture texture_id_, 
                  const Vec2di size_);
  bool checkCollision(const PhysicalObject& other_) const;
  bool checkCollision(const Rect& bounding_box_) const;
  
  eDirection direction_facing;
  eTexture texture_id;
  eTexture texture_front;
  eTexture texture_back;
  Vec2df pos; 
  Vec2df center;
  Vec2di size;
  Rect bounding_box;
};
