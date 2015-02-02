/* 
 * File:   UIElement.h
 * Author: John
 *
 * Created on 1 février 2015, 20:45
 */

#ifndef UIELEMENT_H
#define	UIELEMENT_H

class UIElement
{
protected:
  UIElement();
  UIElement(const Vec2di& position_, const Vec2di& size_);
  Rect bounding_box;
  Vec2di position;
  Vec2di size;
};

#endif	/* UIELEMENT_H */

