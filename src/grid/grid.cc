#include "grid.h"

#include <SDL2/SDL.h>

#include <iostream>
#include <memory>
#include <vector>

#include "cell.h"
#include "coordinates.h"

Grid::Grid(std::shared_ptr<SDL_Renderer> renderer, int width, int height,
           int cell_size, int border_size)
    : renderer(renderer),
      width(width),
      height(height),
      cell_size(cell_size),
      border_size(border_size),
      simulating(false) {
  num_cells_x = (width - border_size) / (cell_size + border_size) + 1;
  num_cells_y = (height - border_size) / (cell_size + border_size) + 1;

  cell_grid.resize(num_cells_x, std::vector<Cell>(num_cells_y, Cell()));

  // TODO: Figure out correct grid dimensions and/or how to centre grid
  for (int i = 0; i < num_cells_x; ++i) {
    for (int j = 0; j < num_cells_y; ++j) {
      cell_grid[i][j] = Cell(border_size + ((border_size + cell_size) * i),
                             border_size + ((border_size + cell_size) * j),
                             cell_size, renderer);

      cell_grid_indices[&cell_grid[i][j]] = {i, j};
    }
  }
}

Grid::~Grid() {
  // TODO: Implement Later
  std::cout << "Destroying grid...\n";
  simulating = false;
}

void Grid::handleEvents(const SDL_Event& e) {
  handleMouseClick(e);
  handleKeyboard(e);
}

void Grid::handleMouseClick(const SDL_Event& e) {
  if (e.type == SDL_MOUSEBUTTONDOWN) {
    // Get Mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);

    // Toggle cell
    Cell& cell = getCell(x, y);
    toggleCell(cell);

    // Count how many alive adjacent to it
    std::cout << "# of alive adjacent: " << countSurroundingAlive(cell) << '\n';
    std::cout << "# of alive TOTAL: " << alive_cells.size() << '\n';
  }
}

void Grid::handleKeyboard(const SDL_Event& e) {
  if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE) {
    simulating = !simulating;
    std::cout << "IS SIMULATING?: " << simulating << '\n';
  }
}

void Grid::update() {
  if (simulating) {
    std::unordered_set<Cell*> to_check;
    std::unordered_set<Cell*> to_update;

    // The only cells we need to check are living cells, and their neighbors
    for (auto& cell : alive_cells) {
      Coordinates grid_coords = cell_grid_indices[cell];
      for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
          int x = grid_coords.x + i;
          int y = grid_coords.y + j;
          if (x >= 0 && x < cell_grid.size() && y >= 0 &&
              y < cell_grid[x].size())
            to_check.insert(&cell_grid[x][y]);
        }
      }
    }

    // Check each of the cells to see if they need to be updated
    for (auto& cell : to_check) {
      int count = countSurroundingAlive(*cell);
      // A living cell dies if it has less than 2 or greater than 3 living
      // neighbors
      if (cell->getIsAlive() && (count < 2 || count > 3))
        to_update.insert(cell);
      // A dead cell lives if it has exactly 3 living neighbors
      else if (!cell->getIsAlive() && count == 3)
        to_update.insert(cell);
    }

    // Toggle the status of each cell that needs to be updated
    for (auto& cell : to_update) {
      toggleCell(*cell);
    }

    SDL_Delay(50);
  }
}

void Grid::render() const {
  for (const std::vector<Cell>& row : cell_grid) {
    for (const Cell& cell : row) {
      cell.render();
    }
  }
}

Coordinates Grid::getGridCoord(int x, int y) {
  return {x / (cell_size + border_size), y / (cell_size + border_size)};
}

Cell& Grid::getCell(int x, int y) {
  Coordinates grid_coords = getGridCoord(x, y);
  return cell_grid[grid_coords.x][grid_coords.y];
}

void Grid::toggleCell(Cell& cell) {
  if (cell.getIsAlive())
    alive_cells.erase(&cell);
  else
    alive_cells.insert(&cell);
  cell.toggleAlive();
}

int Grid::countSurroundingAlive(Cell& cell) {
  int count = 0;
  Coordinates grid_coords = cell_grid_indices[&cell];
  int grid_x = grid_coords.x;
  int grid_y = grid_coords.y;

  // Loop over offsets
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (i == 0 && j == 0) continue;  // Ignore centre
      int adj_x = grid_x + j;
      int adj_y = grid_y + i;
      if (adj_x >= 0 && adj_x < cell_grid.size() && adj_y >= 0 &&
          adj_y < cell_grid[grid_x].size() &&
          cell_grid[adj_x][adj_y].getIsAlive())
        ++count;
    }
  }
  return count;
}
