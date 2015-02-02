/* 
 * File:   UI.h
 * Author: John
 *
 * Created on 25 janvier 2015, 16:28
 */

#ifndef UI_H
#define	UI_H

#include "Utils.h"
#include "Window.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <map>

class Player;

class UI{
public:
  UI();
  ~UI();
  void initUI(Player* player_);
  void render(SDL_Renderer* renderer_, SDL_Texture** texture_sheets_,
              const std::map<eTexture, SDL_Rect>& static_texture_src_rect);
  void update(Player& player_);
  void receiveInput(const std::map<eKey, bool>& keys_down_,
              const std::array<bool, 255>& mouse_buttons_down_,
              const Vec2di& mouse_position_, 
              const Vec2di& mouse_position_in_world_);
private:
  std::string hp;
  std::string mp;
  std::string ammo_string;
 
  Player* player;
  TTF_Font* font;
  SDL_Texture* ui_texture;
  
  bool display_inventory_window;
  bool display_character_window;
  int timer_press_UI_key;
  int delay_between_UI_key_press;
  
  Window inventory_window;
  
};



#endif	/* UI_H */

