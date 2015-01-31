#include "Character.h"
#include "Projectile.h"
#include "NPC.h"
#include "Wall.h"
#include <algorithm>
#include <random>

Character::Character() : 
name(" "), hp(0), mp(0), speed(0), strength(0), 
shooting_direction(eDirection::None)
{
};

Character::Character(const Vec2df& position_, const eTexture texture_id_,
            const Vec2di& size_, const int hp_, const int strength_) :
            PhysicalObject(position_, texture_id_, size_), 
            hp(hp_), strength(strength_), shooting_direction(eDirection::None)
{
  std::uniform_int_distribution<int> rand(300, 600);
  transmit_conditions_timer_default = transmit_conditions_timer = rand(g_mt19937);
  for(int i = 0 ; i < (int)eWeapon::Weapon_count ; i++)
  {
    weapons_inventory[i] = std::unique_ptr<Weapon>();
  }
  
  for(int i = 0 ; i < State_Count ; i++)
  {
    conditions_states[i] = nullptr;
  }
  
  std::cout << "Calling Character constructor" << std::endl;
}

Character::~Character()
{
  for(int i = 0 ; i < State_Count ; i++)
  {
    delete conditions_states[i];
  }
}

void 
Character::takeDamage(const int damage_, 
        const std::array<ConditionState*, State_Count>& conditions_states_) 
{
  std::cout << damage_ << " " << hp << std::endl;
  hp -= damage_;
  
  if(conditions_states_[State_Burning])
  {
    std::uniform_int_distribution<int> rand(1, 10000);
    if(rand(g_mt19937) <= 
        conditions_states_[State_Burning]->projectile_transmission_probability)
    {
      changeConditions(conditions_states_[State_Burning], State_Burning);
    }
  }
}

void Character::changeConditions(const ConditionState* condition_state_,
                                const eState state_id) 
{
  //TODO : compare current effect, don't replace if effect is weaker
  conditions_states[state_id] = new ConditionState(condition_state_->duration,
          condition_state_->effect_power, 
          condition_state_->projectile_transmission_probability,
          condition_state_->contact_transmission_probability);
}

void 
Character::addWeaponToInventory(eWeapon type_, std::unique_ptr<Weapon> weapon_)
{
  weapons_inventory[(int)type_] = std::move(weapon_);
}

void 
Character::updateConditionState() 
{
  if(conditions_states[State_Burning])
  {
    hp -= 1 * g_delta_t;
    conditions_states[State_Burning]->time_left -= (int)(g_delta_t);
    if(conditions_states[State_Burning]->time_left <= 0)
    {
      delete conditions_states[State_Burning];
      conditions_states[State_Burning] = nullptr;
    }
  }
}

void
Character::transmitConditionsToNearbyNPCs(const NPCUniquePtrVector& npc_vector_)
{
  Vec2df center1 = {pos.x + size.x/2.0f, pos.y + size.y/2.0f};
  for(auto &npc : npc_vector_)
  {
    if(npc)
    {
      if(distanceBetween2Points(center1, npc->getCenter()) < 100)
      {
          if(conditions_states[State_Burning])
          {
            std::uniform_int_distribution<int> rand(1, 10000);
            if(rand(g_mt19937) <= 
                conditions_states[State_Burning]->contact_transmission_probability)
            {
              npc->changeConditions(conditions_states[State_Burning], State_Burning);
            }
          }
      }
    }
  }
}


void 
Character::checkCollisionWithNPCs(const NPCUniquePtrVector& npc_vector_,
        Vec2df& movement_) 
{
  Rect future_bbox = bounding_box;
  updateBoundingBox(future_bbox, movement_);

  const Rect* collision_direction[4] = {nullptr};
  eDirection blocked_direction = eDirection::None;

  for(auto &npc : npc_vector_){ 
    if(npc){
      const Rect* blocked_by = checkCollisionWithBoundingBox(future_bbox, 
                                              npc->getBoundingBox(), 
                                              blocked_direction);

      if(blocked_direction != eDirection::None)
      {
        collision_direction[(int)blocked_direction] = blocked_by;
      }
    }
  }

  getBlockedByObstacle(collision_direction, movement_);
}

void 
Character::checkCollisionWithWalls(const WallUniquePtrVector& wall_vector_,
        Vec2df& movement_) 
{
  Rect future_bbox = bounding_box;
  updateBoundingBox(future_bbox, movement_);

  const Rect* collision_direction[4] = {nullptr};
  eDirection blocked_direction = eDirection::None;

  for(auto &wall : wall_vector_){ 
    if(wall){
      const Rect* blocked_by = checkCollisionWithBoundingBox(future_bbox, 
                                              wall->getBoundingBox(), 
                                              blocked_direction);

      if(blocked_direction != eDirection::None)
      {
        collision_direction[(int)blocked_direction] = blocked_by;
      }
    }
  }

  getBlockedByObstacle(collision_direction, movement_);
}

void
Character::getBlockedByObstacle(const Rect** obstacles_in_4_directions_,
        Vec2df& movement_)
{
  if(obstacles_in_4_directions_[(int)eDirection::Right])
  {
    movement_.x = obstacles_in_4_directions_[(int)eDirection::Right]->left -
            bounding_box.right;
  }
  if(obstacles_in_4_directions_[(int)eDirection::Left])
  {
    movement_.x = 
            obstacles_in_4_directions_[(int)eDirection::Left]->right -
            bounding_box.left; 
  }
  if(obstacles_in_4_directions_[(int)eDirection::Up])
  {
    movement_.y = 
            obstacles_in_4_directions_[(int)eDirection::Up]->bottom -
            bounding_box.top;
  }
  if(obstacles_in_4_directions_[(int)eDirection::Down])
  {
    movement_.y = obstacles_in_4_directions_[(int)eDirection::Down]->top -
            bounding_box.bottom;
  }
}

bool 
Character::isDead() const
{
  return (hp <= 0);
}

int 
Character::getHp() const
{
  return hp;
}

int 
Character::getMp() const
{
  return mp;
}

const std::array<ConditionState*, State_Count>&
Character::getConditionsStates() const 
{
  return conditions_states;
}
