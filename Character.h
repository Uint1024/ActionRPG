/* 
 * File:   Character.h
 * Author: John
 *
 * Created on 23 janvier 2015, 02:32
 */

#ifndef CHARACTER_H
#define	CHARACTER_H
#include "Utils.h"
#include <string>
#include "PhysicalObject.h"

class Character : public PhysicalObject{
public:
  Character();
  Character(int x_, int y_, std::string name_);
private:
  std::string name;
  int hp;
  int mp;
  int speed;
};

#endif	/* CHARACTER_H */

