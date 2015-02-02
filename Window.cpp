#include "Window.h"

Window::Window()
{
}

Window::Window(const Vec2di& position_, const Vec2di& size_) : 
position(position), size(size_), 
        bounding_box{position_.x, position_.y, size_.x, size_.y}
{
  
}
