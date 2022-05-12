#include "game.h"

#include <iostream>

Game::Game(const char* title, const int width, const int height)
    : title(title),
      width(width),
      height(height),
      running(false),
      window(nullptr),
      surface(nullptr) {}

Game::~Game() {
  std::cout << "Destroying Game...\n";

  // running should be false here
  if (running) std::cerr << "Something went wrong here!!!\n";

  // Deallocate SDL Related Memory
  SDL_FreeSurface(surface);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

bool Game::init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "SDL failed to initialize! ERROR: " << SDL_GetError() << '\n';
    return false;
  }

  // Initialize Game Window
  window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

  if (window == NULL) {
    std::cerr << "Window failed to initialize! ERROR: " << SDL_GetError()
              << '\n';
    return false;
  }

  // Get Window Surface
  surface = SDL_GetWindowSurface(window);

  // Get Image
  SDL_Surface* img = SDL_LoadBMP("assets/test.bmp");
  if (img == NULL) {
    std::cerr << "Image failed to load! ERROR: " << SDL_GetError() << '\n';
    return false;
  }
  SDL_BlitSurface(img, NULL, surface, NULL);

  // Update the surface
  SDL_UpdateWindowSurface(window);

  return true;
}

void Game::run() {
  running = init();
  if (!running) {
    std::cerr << "Game failed to start! Skipping run()...\n";
    return;
  }

  // Handle SDL Events
  SDL_Event e;
  while (running) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) running = false;
    }
    SDL_UpdateWindowSurface(window);
  }
}
