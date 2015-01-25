#include "Wall.h"
#include "Character.h"

Wall::Wall(){
  
}

Wall::Wall(Vec2df position_) : 
PhysicalObject(position_.x, position_.y, eTexture::Wall, Vec2di{64, 64}){
  std::cout << "Creating wall" << std::endl;
}