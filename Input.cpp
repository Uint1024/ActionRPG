#include "Input.h"
#include "GameData.h"
#include <SDL.h>
#include <iostream>

Input::Input(){
  keymap.emplace(SDL_SCANCODE_Z, eKey::Up);
  keymap.emplace(SDL_SCANCODE_S, eKey::Down);
  keymap.emplace(SDL_SCANCODE_A, eKey::Left);
  keymap.emplace(SDL_SCANCODE_D, eKey::Right);
}

/*Poll events and send them to the objects
 Return false if the user asks to quit the game
 Else return true*/
bool Input::pollEvents(GameData& game_data_){
  //keys_down.clear();
  
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
        std::cout << e.key.keysym.scancode << std::endl;
			}
      
      if (e.type == SDL_KEYUP){
        keys_down[keymap[e.key.keysym.scancode]] = false;	
			}
		}
  
  
  game_data_.getPlayer().receiveInput(keys_down);
  
  return true;
}
