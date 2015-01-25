#include "Zombie.h"
#include "PhysicalObject.h"

Zombie::Zombie(){};

Zombie::Zombie(int x_, int y_, std::string name_, Vec2di size_):
NPC(x_, y_, name_, eTexture::Zombie, size_, 10){
  std::cout << "calling Zombie constructor" << std::endl;
}

void Zombie::runAI(){
  
}

void Zombie::update(const Player& player){
  float angle_to_player = std::atan2(
              player.getPos().y + player.getSize().y / 2.0f - 
              (pos.y + size.y / 2.0f), 
              player.getPos().x + player.getSize().x / 2.0f - 
              (pos.x + size.x / 2.0f));
  
  float speed = 200 * g_delta_t;
  
  Vec2df movement = { std::cos(angle_to_player) * speed,
                    std::sin(angle_to_player) * speed };
  pos.x += movement.x;
  pos.y += movement.y;
 
  updateBoundingBox(bounding_box, movement);
}