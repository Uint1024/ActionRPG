/* 
 * File:   Player.h
 * Author: John
 *
 * Created on 22 janvier 2015, 14:23
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include "BaseObject.h"
#include "Utils.h"
#include <string>
#include <SDL.h>
#include <map>

struct Point;
class BaseObject;

class Player : public BaseObject{
public:
  Player();
  Player(std::string name_, int x_, int y_, eTexture texture_id_);
  void move(Point movement_);
  void receiveInput(std::map<eKey, bool> keys_down_);
  void render(SDL_Renderer* renderer_,
              SDL_Texture* texture_,
              std::map<eTexture, SDL_Rect>& texture_src_rect_);
private:
  std::string name;
};

#endif	/* PLAYER_H */

