/* 
 * File:   BaseObject.h
 * Author: John
 *
 * Created on 22 janvier 2015, 14:21
 */

#ifndef BASEOBJECT_H
#define	BASEOBJECT_H
#include "Utils.h"

class BaseObject{
protected:
  //protected constructor ensure BaseObject can't be created alone
  BaseObject();
  BaseObject(int x_, int y_, eTexture texture_id_);
  eTexture texture_id;
  Point pos;
  Point tex_pos;
  Point tex_size;
};

#endif	/* BASEOBJECT_H */

