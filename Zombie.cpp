#include "Zombie.h"
#include "PhysicalObject.h"
#include "Wall.h"
Zombie::Zombie(){};

Zombie::Zombie(int x_, int y_, std::string name_, Vec2di size_):
NPC(x_, y_, name_, eTexture::Zombie, size_, 10, 5)
{
  std::cout << "calling Zombie constructor" << std::endl;
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
}