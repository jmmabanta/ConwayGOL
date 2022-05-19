#ifndef CONWAYGOL_GAME_H_
#define CONWAYGOL_GAME_H_

#include <SDL2/SDL.h>
#include "experiments/test_texture.h"

class Game {
 public:
  Game(const char* title, int width, int height);
  ~Game();

  /**
   * @brief Initializes the game window
   *
   * @return True when initialization succeeds
   */
  bool init();

  /**
   * @brief Run's the game loop
   *
   */
  void run();

 private:
  const char* title;
  const int width, height;
  bool running;

  SDL_Window* window;
  SDL_Renderer* renderer;
  TestTexture* testTexture;
};

#endif
