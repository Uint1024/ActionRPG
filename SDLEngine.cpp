#include "SDLEngine.h"
#include "GameData.h"
#include "Globals.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

SDLEngine::SDLEngine(){};

SDLEngine::SDLEngine(const char* window_name_, 
        const int window_width, 
        const int window_height) :
zoom_level(1)
{
  std::cout << "Starting Engine" << std::endl;
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    throw std::runtime_error (SDL_GetError());
  }

  if(IMG_Init(IMG_INIT_PNG) < 0)
  {
    throw std::runtime_error (SDL_GetError());
  }
  
  if(TTF_Init() < 0)
  {
    throw std::runtime_error (SDL_GetError());
  }
  else
  {
    std::cout << "TTF initialized" << std::endl;
  }
  
	window = SDL_CreateWindow(window_name_,
											SDL_WINDOWPOS_UNDEFINED,
											SDL_WINDOWPOS_UNDEFINED,
											window_width,
											window_height,
											SDL_WINDOW_SHOWN);
  if(window == NULL)
  {
    throw std::runtime_error (SDL_GetError());
  }        

  pixel_format = SDL_GetWindowPixelFormat(window);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(renderer == NULL)
  {
      throw std::runtime_error (SDL_GetError());
  }  
  
  texture_sheets[TextureSheet_Characters] = 
          IMG_LoadTexture(renderer, "images/characters.png");
  if(texture_sheets[TextureSheet_Characters] == NULL)
  {
     throw std::runtime_error (SDL_GetError());
  }
  
  texture_sheets[TextureSheet_Walls] = 
          IMG_LoadTexture(renderer, "images/walls.png");
  if(texture_sheets[TextureSheet_Walls] == NULL)
  {
     throw std::runtime_error (SDL_GetError());
  }
  
  texture_sheets[TextureSheet_Ground] = 
          IMG_LoadTexture(renderer, "images/ground.png");
  if(texture_sheets[TextureSheet_Ground] == NULL)
  {
     throw std::runtime_error (SDL_GetError());
  }
  
  texture_sheets[TextureSheet_UI] = 
          IMG_LoadTexture(renderer, "images/ui.png");
  if(texture_sheets[TextureSheet_UI] == NULL)
  {
     throw std::runtime_error (SDL_GetError());
  }
  
  //walls.png
  static_texture_src_rect.emplace(eTexture::Wall, SDL_Rect{0, 0, 128, 128});
  
  //characters.png
  dynamic_texture_src_rect[eTexture::Player][eDirection::Front] = 
          SDL_Rect{0, 0, 128, 128};
  dynamic_texture_src_rect[eTexture::Player][eDirection::Back] = 
          SDL_Rect{0, 128, 128, 128};
  dynamic_texture_src_rect[eTexture::Zombie][eDirection::Front] = 
          SDL_Rect{128, 0, 128, 128};
  dynamic_texture_src_rect[eTexture::Zombie][eDirection::Back] = 
          SDL_Rect{128, 128, 128, 128};
  dynamic_texture_src_rect[eTexture::FastOrange][eDirection::Front] = 
          SDL_Rect{768, 0, 128, 128};
  dynamic_texture_src_rect[eTexture::FastOrange][eDirection::Back] = 
          SDL_Rect{768, 128, 128, 128};
  dynamic_texture_src_rect[eTexture::Bomber][eDirection::Front] = 
          SDL_Rect{512, 256, 128, 128};
  dynamic_texture_src_rect[eTexture::Bomber][eDirection::Back] = 
          SDL_Rect{512, 384, 128, 128};
  dynamic_texture_src_rect[eTexture::Burning][eDirection::Front] = 
          SDL_Rect{256, 128, 128, 128};
  dynamic_texture_src_rect[eTexture::Burning][eDirection::Back] = 
          SDL_Rect{256, 128, 128, 128};
  dynamic_texture_src_rect[eTexture::Projectile][eDirection::Front] = 
          SDL_Rect{256, 0, 32, 32};
  dynamic_texture_src_rect[eTexture::Projectile][eDirection::Back] = 
          SDL_Rect{256, 0, 32, 32};
          
  //ground.png
  static_texture_src_rect[eTexture::GroundGrey] = SDL_Rect{0, 0, 256, 256};        
  static_texture_src_rect[eTexture::GroundGrass] = SDL_Rect{0, 256, 256, 256};  
  
  //ui.png
  static_texture_src_rect[eTexture::UI_Shotgun] = SDL_Rect{0, 0, 256, 128};       
  static_texture_src_rect[eTexture::UI_FireWeapon] = SDL_Rect{0, 128, 256, 128};       
}
        
SDLEngine::~SDLEngine()
{
  std::cout << "Deleting engine." << std::endl;
  SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

  TTF_Quit();
  IMG_Quit();
	SDL_Quit();
}

void 
SDLEngine::render(GameData& game_data_)
{
  SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 110, 233, 0, 255);
  game_data_.render(renderer, texture_sheets, dynamic_texture_src_rect, static_texture_src_rect,
          zoom_level);
  g_UI.render(renderer, texture_sheets, static_texture_src_rect);
  SDL_RenderDrawLine(renderer, 50, 100, 100, 200);

  SDL_RenderPresent(renderer);
}