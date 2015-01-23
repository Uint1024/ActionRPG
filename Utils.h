/* 
 * File:   Utils.h
 * Author: John
 *
 * Created on 21 janvier 2015, 23:22
 */

#ifndef UTILS_H
#define	UTILS_H

struct Point{
  float x;
  float y;
};

struct Rect{
  int x;
  int y;
  int w;
  int h;
};

enum class eTexture { Player, Zombie };

enum class eKey { Up, Down, Left, Right, Main_Menu };

extern float g_delta_t;
#endif	/* UTILS_H */

