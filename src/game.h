#ifndef CONWAYGOL_GAME_H_
#define CONWAYGOL_GAME_H_

#include <SDL2/SDL.h>

#include <memory>

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
   * @brief Handle's SDL events (user inputs)
   *
   */
  void handleEvents();

  /**
   * @brief Updates game logic
   *
   */
  void update();

  /**
   * @brief Renders the game to the screen
   *
   */
  void render();

  /**
   * @brief Run's the game loop
   *
   */
  void run();

 private:
  const char* title;
  const int width, height;
  bool running;

  SDL_Event e;

  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
  std::shared_ptr<SDL_Renderer> renderer;
  std::unique_ptr<TestTexture> testTexture;
};

#endif
