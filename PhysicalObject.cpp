#include "PhysicalObject.h"
#include "Utils.h"
#include <iostream>

PhysicalObject::PhysicalObject(){}

PhysicalObject::PhysicalObject(int x_, int y_) : 
pos{(float)x_, (float)y_}{
  std::cout << "Calling BaseObject constructor" << std::endl;
}

void PhysicalObject::render(SDL_Renderer* renderer_, SDL_Texture* texture_, 
        std::map<eTexture, SDL_Rect>& texture_src_rect_, 
        std::map<eTexture, Size>& textures_render_size_,
        Point& camera_,
        float zoom_level_){
  SDL_Rect dest_rect = SDL_Rect{(int)((pos.x - camera_.x) * zoom_level_), 
          (int)((pos.y - camera_.y) * zoom_level_), 
          (int)(textures_render_size_[texture_id].x * zoom_level_), 
          (int)(textures_render_size_[texture_id].y * zoom_level_)};
          
  SDL_RenderCopy(renderer_, texture_, 
          &texture_src_rect_[texture_id], 
          &dest_rect);
}