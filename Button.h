/* 
 * File:   Button.h
 * Author: John
 *
 * Created on 1 février 2015, 19:54
 */

#ifndef BUTTON_H
#define	BUTTON_H

class Button : public UIElement
{
  friend class Window;
public:
  Button();
  Button(const Vec2di& position_, const Vec2di& size_);

};

#endif	/* BUTTON_H */

