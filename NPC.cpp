#include "NPC.h"

NPC::NPC(){};

NPC::NPC(int x_, int y_, std::string name_, eTexture texture_id_, Sizei size_) : 
Character(x_, y_, texture_id_, size_){
  hp = 10;
};

void NPC::runAI(){
  
}
