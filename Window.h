/* 
 * File:   Window.h
 * Author: John
 *
 * Created on 1 février 2015, 18:58
 */

#ifndef WINDOW_H
#define	WINDOW_H
#include "Utils.h"

class UI;

class Window : UIElement
{
  friend class UI;
public:
  Window();
  Window(const Vec2di& position_, const Vec2di& size_);
  
private:
  std::vector<Button> buttons;
};

#endif	/* WINDOW_H */

