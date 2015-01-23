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
          std::map<eTexture, SDL_Rect>& texture_src_rect_);
protected:
  //protected constructor ensure BaseObject can't be created alone
  PhysicalObject();
  PhysicalObject(int x_, int y_);
  eTexture texture_id;
  Point pos;
  Point tex_pos;
  Point tex_size;
  
};
