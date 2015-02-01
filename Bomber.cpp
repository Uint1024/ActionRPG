#include "Bomber.h"
#include "Player.h"

Bomber::Bomber(const Vec2df& position_, const Vec2di& size_):
NPC(position_, " ", eTexture::Bomber, size_, 5000, 5) 
{

}

void Bomber::update(const Player& player, 
        const WallUniquePtrVector& walls_vector_, 
        const NPCUniquePtrVector& npcs_vector_) 
{
  float angle_to_player = std::atan2(
              player.getPos().y + player.getSize().y / 2.0f - 
              (pos.y + size.y / 2.0f), 
              player.getPos().x + player.getSize().x / 2.0f - 
              (pos.x + size.x / 2.0f));
  
  float speed = 0.1f * g_delta_t;
  move(angle_to_player, speed, walls_vector_, npcs_vector_);
  
  transmit_conditions_timer += g_delta_t;
  /*25% chance of transmitting conditions every 500 ms*/
  if(transmit_conditions_timer > transmit_conditions_timer_default)
  {
    transmitConditionsToNearbyNPCs(npcs_vector_);
    
    transmit_conditions_timer = 0;
  }
}

