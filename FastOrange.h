/* 
 * File:   FastOrange.h
 * Author: John
 *
 * Created on 1 février 2015, 00:56
 */

#ifndef FASTORANGE_H
#define	FASTORANGE_H
#include "NPC.h"

class FastOrange : public NPC
{
public:
  FastOrange(const Vec2df& position_, const Vec2di& size_);
  void update(const Player& player, 
                const WallUniquePtrVector& walls_vector_,
                const NPCUniquePtrVector& npcs_vector_) override;
};

#endif	/* FASTORANGE_H */

