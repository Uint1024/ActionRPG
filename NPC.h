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
  NPC(const Vec2df& position_, const std::string& name_, 
      const eTexture texture_id_, const Vec2di& size_, 
      const int hp_, const int strength_);
  bool angry;
  int hp;
};



#endif	/* NPC_H */

