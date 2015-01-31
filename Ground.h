/* 
 * File:   Ground.h
 * Author: John
 *
 * Created on 31 janvier 2015, 13:22
 */

#ifndef GROUND_H
#define	GROUND_H

#include "PhysicalObject.h"


class Ground : public PhysicalObject
{
  Ground(Vec2df& position_);
};

#endif	/* GROUND_H */

