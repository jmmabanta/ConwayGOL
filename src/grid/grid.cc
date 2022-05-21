#include "grid.h"

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "cell.h"

Grid::Grid(std::shared_ptr<SDL_Renderer> renderer, int width, int height,
           int cell_size, int border_size)
    : renderer(renderer),
      width(width),
      height(height),
      cell_size(cell_size),
      border_size(border_size) {
  num_cells_x = (width - border_size) / (cell_size + border_size) + 1;
  num_cells_y = (height - border_size) / (cell_size + border_size) + 1;

  srand(time(NULL));

  for (int i = 0; i < num_cells_x; ++i) {
    std::vector<Cell> row;
    for (int j = 0; j < num_cells_y; ++j) {
      // FIXME: Currently, a cell's status is randomized
      // Later on, make all cells start dead
      Cell cell(rand() % 2, border_size + ((border_size + cell_size) * i),
                border_size + ((border_size + cell_size) * j), cell_size,
                renderer);
      row.push_back(cell);
    }
    cell_grid.push_back(row);
  }
}

Grid::~Grid() {
  // TODO: Implement Later
}

const std::vector<std::vector<Cell>>& Grid::getCellGrid() const {
  return cell_grid;
}

void Grid::render() {
  for (const std::vector<Cell>& row : cell_grid) {
    for (const Cell& cell : row) {
      cell.render();
    }
  }
}

Cell& Grid::getCell(int x, int y) {
  // TODO: Implement later
  // Make sure to account for clicking on a cell border
}
