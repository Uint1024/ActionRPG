/*
* File: Character.h
* Author: John
*
* Created on 23 janvier 2015, 02:32
*/
#ifndef CHARACTER_H
#define	CHARACTER_H
#include "Utils.h"
#include "PhysicalObject.h"
#include "Weapon.h"
#include "ConditionState.h"

#include <map>
#include <string>
#include <chrono>
#include <memory>

class NPC;
class Projectile;

using ConditionStatesArray = std::array<ConditionState*, State_Count>;

class Character : public PhysicalObject{
public:
  Character();
  Character(int x_, int y_, eTexture texture_id_,
            Vec2di size_, int hp_, int strength_);
  ~Character();
  void takeDamage(const int damage_, 
          const ConditionStatesArray& conditions_states_);
  void changeConditions(const ConditionStatesArray& conditions_states_);
  void addWeaponToInventory(eWeapon type_, std::unique_ptr<Weapon> weapon_);
  void updateConditionState();
  void checkCollisionWithNPCs(const NPCUniquePtrVector& npc_vector_, 
                              Vec2df& movement_);
  void checkCollisionWithWalls(const WallUniquePtrVector& wall_vector_, 
                               Vec2df& movement_);
  void getBlockedByObstacle(const Rect** obstacles_in_4_directions_,
                            Vec2df& movement_);
  void transmitConditionsToNearbyNPCs(const NPCUniquePtrVector& npc_vector_);
  bool isDead() const;
  int getHp() const;
  int getMp() const;
  const ConditionStatesArray& getConditionsStates() const; 
  
  
protected:
  std::string name;
  int hp;
  int mp;
  int speed;
  int strength;
  eDirection shooting_direction;
  std::unique_ptr<Weapon> weapons_inventory[(int)eWeapon::Weapon_count];
  ConditionStatesArray conditions_states;
  
  int transmit_conditions_timer;
  int transmit_conditions_timer_default;
  bool reloading;
};
#endif	/* CHARACTER_H */