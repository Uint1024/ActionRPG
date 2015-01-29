#include "NPC.h"
#include <memory>

NPC::NPC(){};

NPC::NPC(int x_, int y_, std::string name_, eTexture texture_id_,
        Vec2di size_,
        int hp_, int strength_) : 
Character(x_, y_, texture_id_, size_, hp_, strength_)
{
};

  const Vec2df 
  NPC::move(const float angle_, const float speed, 
                    const std::vector<std::unique_ptr<Wall>>& walls_vector_,
                    const std::vector<std::unique_ptr<NPC>>& npcs_vector_)
  {
    Vec2df movement = { std::cos(angle_) * speed,
                    std::sin(angle_) * speed };
    setDirectionFacing(movement);

    checkCollisionWithNPCs(npcs_vector_, movement);
    checkCollisionWithWalls(walls_vector_, movement);

    pos.x += movement.x;
    pos.y += movement.y;

    updateBoundingBox(bounding_box, movement);

    return movement;
  }