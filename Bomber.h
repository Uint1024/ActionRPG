/* 
 * File:   Bomber.h
 * Author: John
 *
 * Created on 1 février 2015, 01:30
 */

#ifndef BOMBER_H
#define	BOMBER_H

#include "NPC.h"

class Bomber : public NPC
{
public:
  Bomber(const Vec2df& position_, const Vec2di& size_);
  void update(const Player& player, 
                const std::vector<std::unique_ptr<Wall>>& walls_vector_,
                const std::vector<std::unique_ptr<NPC>>& npcs_vector_) override;
};


#endif	/* BOMBER_H */

