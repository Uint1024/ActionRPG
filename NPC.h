#ifndef NPC_H
#define	NPC_H
#include "Character.h"
#include "PhysicalObject.h"
#include "Projectile.h"
#include "Utils.h"
#include <string>
#include <memory>

class Wall;
class Player;

class NPC : public Character{
public:
  virtual void update(const Player& player_, 
                      const std::vector<std::unique_ptr<Wall>>& walls_vector_,
                      const std::vector<std::unique_ptr<NPC>>& npcs_vector_) = 0;
  const Vec2df move(const float angle_, const float speed, 
                  const std::vector<std::unique_ptr<Wall>>& walls_vector_,
                  const std::vector<std::unique_ptr<NPC>>& npcs_vector_);
protected:
  NPC();
  NPC(int x_, int y_, std::string name_, eTexture texture_id_, Vec2di size_,
          int hp_, int strength_);
  bool angry;
  int hp;
};



#endif	/* NPC_H */

