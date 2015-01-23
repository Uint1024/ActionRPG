#include "PhysicalObject.h"
#include "Utils.h"
#include <iostream>

PhysicalObject::PhysicalObject(){}

PhysicalObject::PhysicalObject(int x_, int y_) : 
pos{(float)x_, (float)y_}{
  std::cout << "Calling BaseObject constructor" << std::endl;
}

void PhysicalObject::render(SDL_Renderer* renderer_, SDL_Texture* texture_, 
        std::map<eTexture, SDL_Rect>& texture_src_rect_){
  SDL_Rect dest_rect = SDL_Rect{(int)pos.x, (int)pos.y, 128, 128};
  SDL_RenderCopy(renderer_, texture_, 
          &texture_src_rect_[texture_id], 
          &dest_rect);
}