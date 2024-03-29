#include "game.h"

#include <iostream>
#include <memory>

#include "grid/grid.h"

Game::Game(const char* title, const int width, const int height)
    : title(title),
      width(width),
      height(height),
      running(false),
      grid(nullptr),
      window(nullptr, SDL_DestroyWindow),
      renderer(nullptr, SDL_DestroyRenderer) {}

Game::~Game() {
  std::cout << "Destroying Game...\n";

  // running should be false here
  if (running) std::cerr << "Something went wrong here!!!\n";

  SDL_Quit();
}

bool Game::init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "SDL failed to initialize! ERROR: " << SDL_GetError() << '\n';
    return false;
  }

  // Initialize Window
  window.reset(SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, width, height,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN));
  if (window == NULL) {
    std::cerr << "Window failed to initialize! ERROR: " << SDL_GetError()
              << '\n';
    return false;
  }

  // Initialize Renderer
  renderer.reset(
      SDL_CreateRenderer(window.get(), -1,
                         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
      SDL_DestroyRenderer);
  if (renderer == NULL) {
    std::cerr << "Renderer failed to initialize! ERROR: " << SDL_GetError()
              << '\n';
    return false;
  }

  // Initialize Grid
  grid = std::make_unique<Grid>(renderer, width, height, 25, 2);

  return true;
}

void Game::handleEvents() {
  while (SDL_PollEvent(&e)) {
    const Uint8* key_state = SDL_GetKeyboardState(NULL);
    if (e.type == SDL_QUIT || key_state[SDL_SCANCODE_ESCAPE]) running = false;
    grid->handleEvents(e);
  }
}

void Game::update() {
  grid->update();
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer.get(), 25, 25, 25, SDL_ALPHA_OPAQUE);

  SDL_RenderClear(renderer.get());

  grid->render();

  SDL_RenderPresent(renderer.get());
}

void Game::run() {
  running = init();
  if (!running) {
    std::cerr << "Game failed to start! Skipping run()...\n";
    return;
  }

  // Game Loop
  while (running) {
    handleEvents();
    update();
    render();
  }
}
