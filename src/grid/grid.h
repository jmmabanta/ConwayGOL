#ifndef CONWAYGOL_GRID_GRID_H_
#define CONWAYGOL_GRID_GRID_H_

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "cell.h"

class Grid {
 public:
  Grid(std::shared_ptr<SDL_Renderer> renderer, int width, int height,
       int cell_size, int border_size);

  ~Grid();

  /**
   * @brief Returns a const reference to the cell grid
   *
   */
  const std::vector<std::vector<Cell>>& getCellGrid() const;

  /**
   * @brief Renders the cell grid to the screen
   *
   */
  void render();

 private:
  /**
   * @brief Returns a reference to the cell object at these coordinates
   *
   * @param x x coordinate
   * @param y y coordinate
   * @return A reference to the cell at {x, y}
   */
  Cell& getCell(int x, int y);

  int width, height, cell_size, border_size;

  int num_cells_x, num_cells_y;
  std::vector<std::vector<Cell>> cell_grid;

  std::shared_ptr<SDL_Renderer> renderer;
};

#endif
