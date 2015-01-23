#ifndef NPC_H
#define	NPC_H
#include "Character.h"
#include <string>


class NPC : public Character{
public:
  NPC();
  NPC(int x_, int y_, std::string name_);
  virtual void runAI() = 0;
private:
  bool angry;
};

#endif	/* NPC_H */

