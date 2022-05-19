#include "game.h"

#include <iostream>

#include "experiments/test_texture.h"

Game::Game(const char* title, const int width, const int height)
    : title(title),
      width(width),
      height(height),
      running(false),
      window(nullptr),
      renderer(nullptr),
      testTexture(nullptr) {}

Game::~Game() {
  std::cout << "Destroying Game...\n";
  delete testTexture;

  // running should be false here
  if (running) std::cerr << "Something went wrong here!!!\n";

  // Deallocate SDL Related Memory
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

bool Game::init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "SDL failed to initialize! ERROR: " << SDL_GetError() << '\n';
    return false;
  }

  // Initialize Window
  window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (window == NULL) {
    std::cerr << "Window failed to initialize! ERROR: " << SDL_GetError()
              << '\n';
    return false;
  }

  // Initialize Renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    std::cerr << "Renderer failed to initialize! ERROR: " << SDL_GetError()
              << '\n';
    return false;
  }

  SDL_SetRenderDrawColor(renderer, 25, 25, 25, SDL_ALPHA_OPAQUE);

  // Initialize Test Texture
  testTexture = new TestTexture(renderer, "assets/test.png");

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
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, testTexture->getTexture(), NULL, NULL);
    SDL_RenderPresent(renderer);
  }
}
