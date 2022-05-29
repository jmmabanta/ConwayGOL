#ifndef CONWAYGOL_GRID_GRID_H_
#define CONWAYGOL_GRID_GRID_H_

#include <SDL2/SDL.h>

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "cell.h"
#include "coordinates.h"

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
   * @brief Returns a cell's grid index at a given screen (x, y)
   *
   * @param x x coordinate from screen
   * @param y y coordinate from screen
   * @returns Coordinates {grid_x, grid_y} corresponding to a cell's index in
   * grid
   */
  Coordinates getGridCoord(int x, int y);

  /**
   * @brief Returns a reference to the cell object at these coordinates
   *
   * @param x x coordinate from screen
   * @param y y coordinate from screen
   * @return A reference to the cell at index [grid_x][grid_y]
   */
  Cell& getCell(int x, int y);

  /**
   * @brief Toggles a cell's status, updating alive_cells
   *
   * @param cell A reference to the cell being toggled
   */
  void toggleCell(Cell& cell);

  /**
   * @brief Counts the number of alive cells adjacent to a cell
   *
   * @param cell A reference to the centre cell
   * @return The number of alive cells adjacent to index [grid_x][grid_y]
   */
  int countSurroundingAlive(Cell& cell);

  int width, height, cell_size, border_size;

  bool simulating;

  int num_cells_x, num_cells_y;
  std::vector<std::vector<Cell>> cell_grid;

  // A reverse mapping that maps a cell to its grid indices
  std::unordered_map<Cell*, Coordinates> cell_grid_indices;

  // Set of all alive_cells, used for optimizing which cells are checked
  std::unordered_set<Cell*> alive_cells;

  std::shared_ptr<SDL_Renderer> renderer;
};

#endif
