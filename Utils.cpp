#include "Utils.h"
#include <iostream>

bool checkCollisionBetweenBoxes(const Rect& first, const Rect& second){
  return !(second.left > first.right ||
        second.right < first.left ||
        second.top > first.bottom ||
        second.bottom < first.top);
}

void updateBoundingBox(Rect& bounding_box, const Sizef& movement){
  bounding_box.left += movement.w;
  bounding_box.right += movement.w;
  bounding_box.top += movement.h;
  bounding_box.bottom += movement.h;
}