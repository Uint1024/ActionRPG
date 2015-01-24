#include "NPC.h"

NPC::NPC(){};

NPC::NPC(int x_, int y_, std::string name_, eTexture texture_id_, Vec2di size_,
        int hp_) : 
Character(x_, y_, texture_id_, size_, hp_){
};

void NPC::runAI(){
  
}
