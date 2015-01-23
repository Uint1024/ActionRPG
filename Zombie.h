/* 
 * File:   Zombie.h
 * Author: John
 *
 * Created on 23 janvier 2015, 03:13
 */

#ifndef ZOMBIE_H
#define	ZOMBIE_H
#include "NPC.h"
#include <string>
#include <iostream>

class Zombie : public NPC{
  public:
    Zombie();
    Zombie(int x_, int y_, std::string name_);
    void runAI() override;
};


#endif	/* ZOMBIE_H */

