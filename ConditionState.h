/* 
 * File:   ConditionState.h
 * Author: John
 *
 * Created on 28 janvier 2015, 18:49
 */

#ifndef CONDITIONSTATE_H
#define	CONDITIONSTATE_H
#include <chrono>

enum eState 
{ 
  State_Burning,
  State_Freezing, 
  State_Healing, 
  State_Confused,
  State_Count
};

struct ConditionState{
  //std::chrono::system_clock::time_point time_end;
  int duration;
  int time_left;//in milliseconds
  int effect_power;
  int projectile_transmission_probability; //min 0, max 10000, so 1000 is 10%, 100 is 1%
  int contact_transmission_probability;
  
  ConditionState(int duration_, int effect_power_, 
  int projectile_transmission_probability_, 
  int contact_transmission_probability_) :
  duration(duration_), time_left(duration_), effect_power(effect_power_),
  projectile_transmission_probability(projectile_transmission_probability_),
  contact_transmission_probability(contact_transmission_probability_)
  {
    
  }
};

#endif	/* CONDITIONSTATE_H */

