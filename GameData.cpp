#include "GameData.h"
#include "Player.h"
#include "Utils.h"

GameData::GameData(){
  player = Player("John", 50, 43);
}

void GameData::render(SDL_Renderer* renderer_, SDL_Texture* texture_,
        std::map<eTexture, SDL_Rect>& texture_src_rect_){
  player.render(renderer_, texture_, texture_src_rect_);
}

Player& GameData::getPlayer() { return player; }
