#include "Input.h"
#include "GameData.h"
#include <SDL.h>
#include <iostream>

Input::Input(){
  keymap.emplace(SDL_SCANCODE_Z, eKey::Up);
  keymap.emplace(SDL_SCANCODE_S, eKey::Down);
  keymap.emplace(SDL_SCANCODE_A, eKey::Left);
  keymap.emplace(SDL_SCANCODE_D, eKey::Right);
  
  /*keys_down.emplace(eKey::Up, false);
  keys_down.emplace(eKey::Down, false);
  keys_down.emplace(eKey::Left, false);
  keys_down.emplace(eKey::Up, false);*/
  
  for(int i = 0 ; i < (int)eKey::All_keys ; i++){
    keys_down.emplace((eKey)i, false);
    keys_up.emplace((eKey)i, false);
  }
  
  for(auto &i : mouse_buttons_down){
    i = false;
  }
}

/*Poll events and send them to the objects
 Return false if the user asks to quit the game
 Else return true*/
bool Input::pollEvents(GameData& game_data_){
  SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
  
  bool keydown = false;
  while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				return false;
			}

			if (e.type == SDL_KEYDOWN){
        keydown = true;
        keys_down[keymap[e.key.keysym.scancode]] = true;
			}
      
      if (e.type == SDL_KEYUP){
        keys_down[keymap[e.key.keysym.scancode]] = false;	
			}
      
      if (e.type == SDL_MOUSEBUTTONDOWN){
        mouse_buttons_down[e.button.button] = true;
      }
      
      if (e.type == SDL_MOUSEBUTTONUP){
        mouse_buttons_down[e.button.button] = false;
      }
		}
  
  game_data_.receiveInput(keys_down, mouse_buttons_down, mouse_position);
  
  return true;
}
