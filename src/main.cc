#include <iostream>

#include "game.h"

const char* TITLE = "Conway's Game of Life";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char const** argv) {
  Game* game = new Game(TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
  game->run();
  delete game;
  return 0;
}
