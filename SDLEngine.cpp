#include "SDLEngine.h"
#include "GameData.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdexcept>
#include <iostream>

SDLEngine::SDLEngine(){};

SDLEngine::SDLEngine(const char* window_name_, 
        const int window_width, 
        const int window_height){
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    throw std::runtime_error (SDL_GetError());
  }
  
  IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow(window_name_,
											SDL_WINDOWPOS_UNDEFINED,
											SDL_WINDOWPOS_UNDEFINED,
											window_width,
											window_height,
											SDL_WINDOW_SHOWN);
  if(window == NULL){
    throw std::runtime_error (SDL_GetError());
  }        

  pixel_format = SDL_GetWindowPixelFormat(window);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(renderer == NULL){
      throw std::runtime_error (SDL_GetError());
  }  
  
  characters_texture = IMG_LoadTexture(renderer, "images/characters.png");
  if(characters_texture == NULL){
     throw std::runtime_error (SDL_GetError());
  }
  
  
  texture_src_rect.emplace(eTexture::PLAYER, SDL_Rect{0, 0, 128, 128});
}
        
SDLEngine::~SDLEngine(){
  std::cout << "Deleting engine." << std::endl;
  SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

  IMG_Quit();
	SDL_Quit();
}

void SDLEngine::render(GameData& game_data_){
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 222, 0, 0, 255);
  
  //SDL_Rect src_rect{0, 0, 128, 128};
  /*SDL_Rect dest_rect{game_data_.getPlayer().getX(), 
          game_data.getPlayer().getPlayer().getY(), 
          128, 
          128};
   * */
  //SDL_RenderCopy(renderer, tex, &src_rect, &dest_rect);
  game_data_.render(renderer, characters_texture, texture_src_rect);
  
  
  SDL_RenderDrawLine(renderer, 50, 100, 100, 200);

  SDL_RenderPresent(renderer);
}