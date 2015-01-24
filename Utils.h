/* 
 * File:   Utils.h
 * Author: John
 *
 * Created on 21 janvier 2015, 23:22
 */

#ifndef UTILS_H
#define	UTILS_H
#include <random>

using uint = unsigned int;

struct Vec2df{
  float x;
  float y;
};

struct Vec2di{
  int x;
  int y;
};

struct Rect{
  float left;
  float top;
  float right;
  float bottom;
};

enum class eTexture { Player, Zombie, Projectile };

enum class eKey { Up, Down, Left, Right, Main_Menu, All_keys };

//ultra original set of elemental powers
enum class eElement { Fire, Water, Earth, Nature, Air, Life, Death };
                      
extern float g_delta_t;
extern std::random_device g_random_device;
extern std::mt19937 g_mt19937;

bool checkCollisionBetweenBoxes(const Rect& first, const Rect& second);
void updateBoundingBox(Rect& bounding_box, const Vec2df& movement);
#endif	/* UTILS_H */

