/* * Physical objects are objects that can be rendered
 */

#pragma once
#include "Utils.h"
#include <SDL.h>
#include <map>
#include <iostream>
class PhysicalObject{
public:
  void render(SDL_Renderer* renderer_,
          SDL_Texture* texture_,
          const std::map<eTexture, SDL_Rect>& texture_src_rect_,
          const std::map<eTexture, Sizei>& textures_render_size_,
          const Pointf& camera_,
          const float zoom_level_) const;
protected:
  //protected constructor ensures BaseObject can't be created alone
  PhysicalObject();
  PhysicalObject(int x_, int y_, eTexture texture_id_, Sizei size_);
  bool checkCollision(const PhysicalObject& other_) const;
  bool checkCollision(const Rect& bounding_box_) const;
  
  
  eTexture texture_id;
  Pointf pos; 
  Sizei size;
  Rect bounding_box;
};
