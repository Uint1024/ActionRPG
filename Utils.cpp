#include "Utils.h"
#include <iostream>

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