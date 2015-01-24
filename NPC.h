#ifndef NPC_H
#define	NPC_H
#include "Character.h"
#include "PhysicalObject.h"
#include "Projectile.h"
#include "Utils.h"
#include <string>


class NPC : public Character{
public:
  virtual void runAI() = 0;
protected:
  NPC();
  NPC(int x_, int y_, std::string name_, eTexture texture_id_, Sizei size_,
          int hp_);
  bool angry;
  int hp;
};

#endif	/* NPC_H */

