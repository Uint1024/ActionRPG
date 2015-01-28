/* 
 * File:   Utils.h
 * Author: John
 *
 * Created on 21 janvier 2015, 23:22
 */

#ifndef UTILS_H
#define	UTILS_H
#include "UI.h"
#include <random>
#include <chrono>
using uint = unsigned int;

struct Vec2df{
  float x;
  float y;
};

struct Vec2di{
  int x;
  int y;
  operator Vec2df() const { return Vec2df{(float)x, (float)y}; }
};

struct Rect{
  float left;
  float top;
  float right;
  float bottom;
};



enum class eTexture { 
  Player, 
  Zombie,
  Projectile, 
  Wall,
  None 
};
  
/*struct Texture{
  eTexture front;
  eTexture back;
};*/

enum class eKey { Up, Down, Left, Right, Main_Menu, WeaponShotgun,
                  WeaponFire, WeaponIce, All_keys };

enum class eDirection { Up, Down, Left, Right, DownLeft, DownRight,
                        UpLeft, UpRight, Front, Back, None };

enum class eState { Burning, Freezing, Healing, Confused };

struct ObjectState{
  eState type;
  int time_left;
  int effect_power;
};

enum class eWeapon { 
  Shotgun = 0,
  Fire, 
  Ice, 
  Electricity,
  Poison, 
  Earth,
  Weapon_count
};

//ultra original set of elemental powers
enum class eElement { Fire, Water, Earth, Nature, Air, Life, Death };
                      
extern float g_delta_t;
extern std::random_device g_random_device;
extern std::mt19937 g_mt19937;
extern UI g_UI;

bool checkCollisionBetweenBoxes(const Rect& first, const Rect& second);
void updateBoundingBox(Rect& bounding_box, const Vec2df& movement);

/*std::chrono::system_clock::time_point getTimeNow() {
  return std::chrono::system_clock::now();
};*/

//const auto& getTimeNow = std::chrono::system_clock::now;

int differenceTimes(std::chrono::system_clock::time_point now, 
        std::chrono::system_clock::time_point before);

extern std::chrono::system_clock::time_point (&currentTime)();
#endif	/* UTILS_H */

