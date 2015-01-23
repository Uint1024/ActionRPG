#include "NPC.h"
#include "Character.h"

NPC::NPC(){};

NPC::NPC(int x_, int y_, std::string name_, eTexture texture_id_) : 
Character(x_, y_, name_, texture_id_){
};

void NPC::runAI(){
  
}