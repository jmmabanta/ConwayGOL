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
   * @brief Handle all the grid's events
   *
   * @param e An SDL event to process
   */
  void handleEvents(const SDL_Event& e);

  /**
   * @brief Updates grid state
   *
   */
  void update();

  /**
   * @brief Renders the cell grid to the screen
   *
   */
  void render() const;

 private:
  /**
   * @brief Toggles a cell's state on mouse click
   *
   * @param e An SDL Event to process
   */
  void handleMouseClick(const SDL_Event& e);

  /**
   * @brief Toggles whether or not the simulation is running with space bar
   *
   * @param e An SDL Event to check on space bar up
   */
  void handleKeyboard(const SDL_Event& e);

  /**
   * @brief Returns a reference to the cell object at these coordinates
   *
   * @param x x coordinate
   * @param y y coordinate
   * @return A reference to the cell at {x, y}
   */
  Cell& getCell(int x, int y);

  int width, height, cell_size, border_size;

  bool simulating;

  int num_cells_x, num_cells_y;
  std::vector<std::vector<Cell>> cell_grid;

  std::shared_ptr<SDL_Renderer> renderer;
};

#endif
