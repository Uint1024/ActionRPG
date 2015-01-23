#include "BaseObject.h"
#include "Utils.h"
#include <iostream>

BaseObject::BaseObject(){}

BaseObject::BaseObject(int x_, int y_, eTexture texture_id_) : 
pos{(float)x_, (float)y_},
texture_id(texture_id_){
  std::cout << "Calling BaseObject constructor" << std::endl;
}
