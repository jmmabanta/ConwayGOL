#include "cell.h"

#include <SDL2/SDL.h>

#include <memory>

#include "coordinates.h"

Cell::Cell()
    : is_alive(false),
      coordinates({0, 0}),
      size(0),
      renderer(nullptr),
      rect({0, 0, 0, 0}) {}

Cell::Cell(bool is_alive, int x, int y, int size,
           std::shared_ptr<SDL_Renderer> renderer)
    : is_alive(is_alive),
      coordinates({x, y}),
      size(size),
      renderer(renderer),
      rect({x, y, size, size}) {}

Cell::Cell(int x, int y, int size, std::shared_ptr<SDL_Renderer> renderer)
    : is_alive(false),
      coordinates({x, y}),
      size(size),
      renderer(renderer),
      rect({x, y, size, size}) {}

Cell::Cell(const Cell& other)
    : is_alive(other.is_alive),
      coordinates(other.coordinates),
      size(other.size),
      renderer(other.renderer),
      rect(other.rect) {}

Cell::~Cell() {
  // TODO: Implement Later
}

const Coordinates Cell::getCoordinates() const { return coordinates; }

const bool Cell::getIsAlive() const { return is_alive; }

void Cell::toggleAlive() { is_alive = !is_alive; }

void Cell::render() const {
  if (is_alive)
    SDL_SetRenderDrawColor(renderer.get(), ALIVE_COL, ALIVE_COL, ALIVE_COL,
                           255);
  else
    SDL_SetRenderDrawColor(renderer.get(), DEAD_COL, DEAD_COL, DEAD_COL, 255);
  SDL_RenderFillRect(renderer.get(), &rect);
}
