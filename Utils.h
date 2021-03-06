/* 
 * File:   Utils.h
 * Author: John
 *
 * Created on 21 janvier 2015, 23:22
 */

#ifndef UTILS_H
#define	UTILS_H
//#include "UI.h"

#include <random>
#include <chrono>
#include <memory>
#include <SDL.h>
class NPC;
class Wall;
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

using Clock = std::chrono::system_clock;
using TimePoint = std::chrono::system_clock::time_point;
using Milliseconds = std::chrono::milliseconds;

enum class eEditorObject {
  GreyGround,
  Wall,
  None
};

enum class eTexture { 
  Player, 
  Zombie,
  FastOrange,
  Bomber,
  Projectile, 
  Wall,
  Burning,
  
  GroundGrey,
  GroundGrass,
  
  UI_Shotgun,
  UI_FireWeapon,
  UI_IceWeapon,
  None 
};
  
/*struct Texture{
  eTexture front;
  eTexture back;
};*/

enum class eKey { 
  Up, 
  Down, 
  Left, 
  Right, 
  Main_Menu, 
  WeaponShotgun,
                  
  WeaponFire, 
  WeaponIce, 
  GreyGround, 
  GreenGround,
                  
  Wall, 
  Quick_Save, 
  Quick_Load, 
  
  Inventory,
  Character_Sheet,
  All_keys 
};

enum class eDirection { 
  Up, 
  Down, 
  Left, 
  Right, 
  DownLeft, 
  DownRight,
  
  UpLeft,   
  UpRight, 
  Front, 
  Back, 
  None 
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

enum class eWeaponState {
  Overheating,
  Reloading
};

enum eTextureSheet {
  TextureSheet_Walls,
  TextureSheet_Characters,
  TextureSheet_Ground,
  TextureSheet_UI,
  TextureSheet_Count
};

enum class eElement { Fire, Water, Earth, Nature, Air, Life, Death };
                      


bool checkCollisionBetweenBoxes(const Rect& first, const Rect& second);
void updateBoundingBox(Rect& bounding_box, const Vec2df& movement);
float distanceBetween2Points(Vec2df one_, Vec2df two_);

int differenceTimes(std::chrono::system_clock::time_point now, 
        std::chrono::system_clock::time_point before);

SDL_Rect getRectOfSprite(const Vec2df pos_, const Vec2df& camera_,
        const Vec2di& texture_size_);
extern std::chrono::system_clock::time_point (&currentTime)();

using NPCUniquePtrVector = std::vector<std::unique_ptr<NPC>>;
using WallUniquePtrVector = std::vector<std::unique_ptr<Wall>>;

#endif	/* UTILS_H */

