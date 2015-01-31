/* 
 * File:   SDLEngine.h
 * Author: John
 *
 * Created on 21 janvier 2015, 22:04
 */

#ifndef SDLENGINE_H
#define	SDLENGINE_H
#include "GameData.h"
#include "Utils.h"
#include <SDL.h>
#include <map>
#include <string>

class SDLEngine{
public:
  SDLEngine();
  SDLEngine(const char* window_name_, 
            const int window_width_,
            const int window_height_);
  ~SDLEngine();
  void render(GameData& game_data_);
  
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  Uint32 pixel_format; //pixel format of the window, used with SDL_RenderCopy
  
  //sprite that can be rendered in multiple directions
  std::map<eTexture, std::map<eDirection, SDL_Rect>> dynamic_texture_src_rect;
  
  //sprite that have only 1 possible direction (walls)
  std::map<eTexture, SDL_Rect> static_texture_src_rect;
  
  SDL_Texture* texture_sheets[TextureSheet_Count];
  float zoom_level;
};


#endif	/* SDLENGINE_H */

