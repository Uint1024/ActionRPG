/* 
 * File:   Utils.h
 * Author: John
 *
 * Created on 21 janvier 2015, 23:22
 */

#ifndef UTILS_H
#define	UTILS_H

using uint = unsigned int;

struct Pointf{
  float x;
  float y;
};

struct Pointi{
  int x;
  int y;
};

struct Sizei{
  int w;
  int h;
};

struct Sizef{
  float w;
  float h;
};

struct Rect{
  float left;
  float top;
  float right;
  float bottom;
};

enum class eTexture { Player, Zombie, Projectile };

enum class eKey { Up, Down, Left, Right, Main_Menu };

//ultra original set of elemental powers
enum class eElement { Fire, Water, Earth, Nature, Air, Life, Death };
                      
extern float g_delta_t;

bool checkCollisionBetweenBoxes(const Rect& first, const Rect& second);
void updateBoundingBox(Rect& bounding_box, const Sizef& movement);
#endif	/* UTILS_H */

