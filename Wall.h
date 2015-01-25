/* 
 * File:   Wall.h
 * Author: John
 *
 * Created on 25 janvier 2015, 19:08
 */

#ifndef WALL_H
#define	WALL_H

#include "PhysicalObject.h"
#include "Utils.h"


class Wall : public PhysicalObject{
  public:
  Wall();
  Wall(Vec2df position_);
};

#endif	/* WALL_H */

