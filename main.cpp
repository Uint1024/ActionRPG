#include "SDLEngine.h"
#include "Input.h"
#include "GameData.h"
#include <SDL.h>

#include <iostream>
#include <memory>
#include <chrono>

float g_delta_t = 0.1f;

//TODO: global delta_t
int main(int argc, char **argv)
{
  int screen_width = 800;
  int screen_height = 600;
  
  //the engine contains the SDL stuff, the textures, and is in charge of
  //printing objects and UI on the screen
  auto engine = std::unique_ptr<SDLEngine>();
  
  //game_data contains all the objects of the game
  //and the objects templates loaded from the config files
  auto game_data = GameData(screen_width, screen_height);
  
  //input_manager receive input events and send them to the game objects
  auto input_manager = Input();
   
  auto running = true;
   
  try{
    engine = std::make_unique<SDLEngine>("ActionRPG", 
            screen_width, screen_height);
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
 
  /*Used to calculate delta_t*/
  auto current =  std::chrono::high_resolution_clock::now();
  auto last =  std::chrono::high_resolution_clock::now();
  std::chrono::nanoseconds diff;
  std::chrono::milliseconds diff_ms;
  
  float fps = 0.0f;
	while (running)
	{
    current = std::chrono::high_resolution_clock::now();
    diff = current - last;
    diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    g_delta_t = diff_ms.count() / 1000.0f;
    
    
    running = input_manager.pollEvents(game_data);
    game_data.update();
    engine->render(game_data);
  
    diff_ms = std::chrono::milliseconds(0);
    last = current;
	}
  
 
  
  
	

	return 0;
}
