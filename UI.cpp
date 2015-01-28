#include "UI.h"
#include "Player.h"
#include <string>

UI::UI(){

}

UI::~UI() {}

void 
UI::initUI(Player* player_)
{
  std::cout << "initUI" << std::endl;
  player = player_;
  hp = std::to_string(player->getHp());
  
  font = TTF_OpenFont("LiberationSans-Regular.ttf", 22);
  if (font == NULL)
  {
    std::cout << TTF_GetError() << std::endl;
  }
}

void 
UI::render(SDL_Renderer* renderer_)
{
  SDL_Color black = {0, 0, 0};
  SDL_Surface* surface = TTF_RenderText_Solid(font, hp.c_str(), black);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
  int w, h;
  TTF_SizeText(font, hp.c_str(), &h, &w);
  SDL_Rect rect = {500, 50, h, w};
  
  SDL_RenderCopy(renderer_, texture, NULL, &rect);
  
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
  
}

