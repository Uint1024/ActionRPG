#include "Zombie.h"
#include "PhysicalObject.h"
#include "Wall.h"
#include "Globals.h"
Zombie::Zombie(){};

Zombie::Zombie(const Vec2df& position_, const std::string& name_,
        const Vec2di& size_):
NPC(position_, name_, eTexture::Zombie, size_, 5000, 5)
{
}

void 
Zombie::update(const Player& player, 
        const std::vector<std::unique_ptr<Wall>>& walls_vector_,
        const std::vector<std::unique_ptr<NPC>>& npcs_vector_)
{
  
  float angle_to_player = std::atan2(
              player.getPos().y + player.getSize().y / 2.0f - 
              (pos.y + size.y / 2.0f), 
              player.getPos().x + player.getSize().x / 2.0f - 
              (pos.x + size.x / 2.0f));
  
  float speed = 0.2f * g_delta_t;
  move(angle_to_player, speed, walls_vector_, npcs_vector_);
  
  transmit_conditions_timer += g_delta_t;
  /*25% chance of transmitting conditions every 500 ms*/
  if(transmit_conditions_timer > transmit_conditions_timer_default)
  {
    transmitConditionsToNearbyNPCs(npcs_vector_);
    
    transmit_conditions_timer = 0;
  }
}