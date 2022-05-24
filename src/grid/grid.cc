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

  srand(time(NULL));

  // TODO: Figure out correct grid dimensions and/or how to centre grid
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
    cell.toggleAlive();

    // Count how many alive adjacent to it
    std::cout << "# of alive adjacent: " << countSurroundingAlive(x, y) << '\n';
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
    // TODO: Implement Conway's Game of Life logic here
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

int Grid::countSurroundingAlive(int x, int y) {
  int count = 0;
  Coordinates grid_coords = getGridCoord(x, y);
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
