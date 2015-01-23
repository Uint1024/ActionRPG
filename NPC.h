#ifndef NPC_H
#define	NPC_H
#include "Character.h"
#include <string>


class NPC : public Character{
public:
  virtual void runAI() = 0;
protected:
  NPC();
  NPC(int x_, int y_, std::string name_);
  bool angry;
};

#endif	/* NPC_H */

