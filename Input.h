/* 
 * File:   Input.h
 * Author: John
 *
 * Created on 21 janvier 2015, 23:21
 */

#ifndef INPUT_H
#define	INPUT_H
#include "Utils.h"

#include <SDL.h>
#include <map>

class GameData;

class Input{
public:
  Input();
  bool pollEvents(GameData& game_data_);
  
private:
	SDL_Event e;
  std::map<SDL_Scancode, eKey> keymap;
  std::array<bool, 255> mouse_buttons_down;
  std::map<eKey, bool> keys_down;
  std::map<eKey, bool> keys_up;
  Pointi mouse_position;
};

#endif	/* INPUT_H */

