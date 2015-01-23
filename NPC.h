#ifndef NPC_H
#define	NPC_H
#include "Character.h"
#include "Utils.h"
#include <string>


class NPC : public Character{
public:
  virtual void runAI() = 0;
protected:
  NPC();
  NPC(int x_, int y_, std::string name_, eTexture texture_id_);
  bool angry;
};

#endif	/* NPC_H */

