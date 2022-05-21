#ifndef CONWAYGOL_GRID_CELL_H_
#define CONWAYGOL_GRID_CELL_H_

#include <SDL2/SDL.h>

#include <memory>

#include "coordinates.h"

const Uint8 ALIVE_COL = 50;
const Uint8 DEAD_COL = 255;

class Cell {
 public:
  Cell(bool is_alive, int x, int y, int size,
       std::shared_ptr<SDL_Renderer> renderer);
  Cell(int x, int y, int size, std::shared_ptr<SDL_Renderer> renderer);
  Cell(const Cell& other);

  ~Cell();

  /**
   * @brief Returns an immutable struct of a cell's top-left coordinate
   *
   */
  const Coordinates getCoordinates() const;

  /**
   * @brief Returns the status of a cell (true = alive)
   *
   */
  const bool getIsAlive() const;

  /**
   * @brief Toggles whether or not a cell is alive
   *
   */
  void toggleAlive();

  /**
   * @brief Renders the grid cell to the screen
   *
   */
  void render() const;

 private:
  Coordinates coordinates;
  int size;
  bool is_alive;

  std::shared_ptr<SDL_Renderer> renderer;
  SDL_Rect rect;
};

#endif
