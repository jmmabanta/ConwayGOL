#include <iostream>
#include <memory>

#include "game.h"

const char* WINDOW_TITLE = "Conway's Game of Life";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char const** argv) {
  auto game = std::make_unique<Game>(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
  game->run();
  return 0;
}
