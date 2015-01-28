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
  int time_left;//in milliseconds
  int effect_power;
};

#endif	/* CONDITIONSTATE_H */

