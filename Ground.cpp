#include "Ground.h"

Ground::Ground(const Vec2df& position_) :
PhysicalObject(position_, eTexture::GroundGrey, Vec2di{128, 128})
{
  
}

