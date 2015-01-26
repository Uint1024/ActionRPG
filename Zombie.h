/* 
 * File:   Zombie.h
 * Author: John
 *
 * Created on 23 janvier 2015, 03:13
 */

#ifndef ZOMBIE_H
#define	ZOMBIE_H
#include "NPC.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <memory>


class Zombie : public NPC{
  public:
    Zombie();
    Zombie(int x_, int y_, std::string name_, Vec2di size_);
    void update(const Player& player, 
                const std::vector<std::unique_ptr<Wall>>& walls_vector_,
                const std::vector<std::unique_ptr<NPC>>& npcs_vector_) override;
};


#endif	/* ZOMBIE_H */

