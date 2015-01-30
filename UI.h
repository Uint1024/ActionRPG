/* 
 * File:   UI.h
 * Author: John
 *
 * Created on 25 janvier 2015, 16:28
 */

#ifndef UI_H
#define	UI_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
class Player;

class UI{
public:
  UI();
  ~UI();
  void initUI(Player* player_);
  void render(SDL_Renderer* renderer_);
  void update(Player& player_);
private:
  std::string hp;
  std::string mp;
  std::string ammo_string;
 
  Player* player;
  TTF_Font* font;
};



#endif	/* UI_H */

