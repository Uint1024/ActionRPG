#include "Utils.h"
#include <iostream>
#include "NPC.h"
#include "Wall.h"

bool 
checkCollisionBetweenBoxes(const Rect& first, const Rect& second)
{
  return !(second.left > first.right ||
        second.right < first.left ||
        second.top > first.bottom ||
        second.bottom < first.top);
}

void 
updateBoundingBox(Rect& bounding_box, const Vec2df& movement)
{
  bounding_box.left += movement.x;
  bounding_box.right += movement.x;
  bounding_box.top += movement.y;
  bounding_box.bottom += movement.y;
}

int 
differenceTimes(std::chrono::system_clock::time_point now, 
        std::chrono::system_clock::time_point before)
{
  std::chrono::milliseconds diff = 
          std::chrono::duration_cast<std::chrono::milliseconds>(now - before);
  
  return diff.count();
}

SDL_Rect 
getRectOfSprite(const Vec2df pos_, const Vec2df& camera_,
                const Vec2di& texture_size_)
{
  return SDL_Rect{(int)((pos_.x - camera_.x)), 
          (int)((pos_.y - camera_.y)), 
          (int)(texture_size_.x), 
          (int)(texture_size_.y)};
          
}

float distanceBetween2Points(Vec2df one_, Vec2df two_)
{
  float x_dist = two_.x - one_.x;
  float y_dist = two_.y - one_.y;
  
  return sqrt(x_dist * x_dist + y_dist * y_dist);
}