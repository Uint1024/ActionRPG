#include "UI.h"
#include "Player.h"
#include "Globals.h"
#include <string>

UI::UI() : timer_press_UI_key(0), delay_between_UI_key_press(100),
        inventory_window(Vec2di{200, 200}, Vec2di{500, 500})
{
  
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

void UI::receiveInput(const std::map<eKey, bool>& keys_down_, 
        const std::array<bool, 255 > & mouse_buttons_down_, 
        const Vec2di& mouse_position_, const Vec2di& mouse_position_in_world_) 
{
  timer_press_UI_key += g_delta_t;
  
  if(timer_press_UI_key > delay_between_UI_key_press)
  {
    if(keys_down_.at(eKey::Inventory))
    {  
      display_inventory_window = !display_inventory_window;
      timer_press_UI_key = 0;
    }
    if(keys_down_.at(eKey::Character_Sheet))
    {
      display_character_window = !display_character_window;
      timer_press_UI_key = 0;
    }
  }
  
  if(display_inventory_window)
  {
    
  }
}

void 
UI::render(SDL_Renderer* renderer_, SDL_Texture** texture_sheets_, 
        const std::map<eTexture, SDL_Rect>& static_texture_src_rect)
{
  SDL_Color black = {0, 0, 0};
  SDL_Surface* surface = TTF_RenderText_Solid(font, hp.c_str(), black);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
  int w, h;
  TTF_SizeText(font, hp.c_str(), &h, &w);
  SDL_Rect rect = {500, 50, h, w};
  
  SDL_RenderCopy(renderer_, texture, NULL, &rect);
  
  
  
  surface = TTF_RenderText_Solid(font, ammo_string.c_str(), black);

  texture = SDL_CreateTextureFromSurface(renderer_, surface);
  TTF_SizeText(font, ammo_string.c_str(), &h, &w);
  rect = {700, 600, h, w};
  
  SDL_RenderCopy(renderer_, texture, NULL, &rect);
  
  
  if(display_inventory_window)
  {
    SDL_SetRenderDrawColor(renderer_, 255, 145, 34, 255);

    SDL_Rect inventory{static_cast<int>(inventory_window.bounding_box.left), 
            static_cast<int>(inventory_window.bounding_box.top), 
            inventory_window.size.x, 
            inventory_window.size.y};

    SDL_RenderFillRect(renderer_, &inventory);
    
    const SDL_Rect& src_rect_shotgun = 
            static_texture_src_rect.at(eTexture::UI_Shotgun);
    SDL_Rect dest_rect = {210, 210, 
              src_rect_shotgun.w, src_rect_shotgun.h};
    SDL_RenderCopy(renderer_, texture_sheets_[TextureSheet_UI], 
            &src_rect_shotgun, &dest_rect);
    
    dest_rect = {210, 210 + src_rect_shotgun.h, 
                  src_rect_shotgun.w, src_rect_shotgun.h};
    
    const SDL_Rect& src_rect_fire = 
                        static_texture_src_rect.at(eTexture::UI_FireWeapon);
    SDL_RenderCopy(renderer_, texture_sheets_[TextureSheet_UI],
            &src_rect_fire, &dest_rect);
    
  }
  
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
  
}

void
UI::update(Player& player_)
{
  hp = std::to_string(player_.getHp());
  
  //std::pair<int, int> ammo = player_.getAmmo();
  
  ammo_string = player_.getCurrentWeapon()->getAmmoString();  
  
}

