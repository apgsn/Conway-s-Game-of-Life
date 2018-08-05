#include "ConwaysField.h"

ConwaysField::ConwaysField(unsigned width, unsigned height, unsigned size){
  this->width = width;
  this->height = height;
  this->size = size;
  grid.resize(width);
  for(auto &i : grid)
    i.resize(height);
  gridLines.resize(2);
  for(unsigned i = 0; i < grid.size(); i++)
    setGridLine(i, 0);
  for(unsigned i = 0; i < grid[0].size(); i++)
    setGridLine(i, 1);
}

void ConwaysField::setField(bool empty){
  for(unsigned i = 0; i < grid.size(); i++){
    for(unsigned j = 0; j < grid[0].size(); j++){
      grid[i][j].status = 0;
      grid[i][j].neighbors = 0;
      for(unsigned k = 0; k < 4; k++){
        grid[i][j].tile[k].color = sf::Color(30, 30, 30);
        grid[i][j].tile[k].position = sf::Vector2f(((k % 2 == k / 2) + i) * size, (k / 2 + j) * size);
      }
    }
  }
  if(!empty) for(unsigned i = 0; i < grid.size(); i++)
    for(unsigned j = 0; j < grid[0].size(); j++)
      if(!(rand() % 5)) switchCellStatus(i, j);
}

void ConwaysField::setGridLine(unsigned n, bool dir){
  gridLines[dir].push_back(sf::VertexArray(sf::Lines, 2));
  for(unsigned k = 0; k < 2; k++){
    gridLines[dir][n][k].position = sf::Vector2f((dir ? k * width : n) * size, (dir ? n : k * height) * size);
    gridLines[dir][n][k].color = sf::Color(60, 60, 30 + 100.0 * n / (dir ? height : width));
    if(!(n%10)) gridLines[dir][n][k].color += sf::Color(60, 60, 60);
  }
}

Cell ConwaysField::switchCellStatus(unsigned i, unsigned j){
  grid[i][j].toggle();
  for(int k = -1; k <= 1; k++){
    for(int l = -1; l <= 1; l++){
      if(!(k || l)) continue;
      grid[(width + i + k) % width][(height + j + l) % height].neighbors += grid[i][j].status * 2 - 1;
    }
  }
  return grid[i][j];
}

std::vector<Cell> ConwaysField::updateFieldStatus(){
  std::vector<Cell> buffer;
  ConwaysField updatedGrid = *this;
  for(unsigned i = 0; i < grid.size(); i++)
    for(unsigned j = 0; j < grid[0].size(); j++)
      if((grid[i][j].status && (grid[i][j].neighbors < 2 || grid[i][j].neighbors > 3)) ||
        (!grid[i][j].status && grid[i][j].neighbors == 3))
        buffer.push_back(updatedGrid.switchCellStatus(i, j));
  *this = updatedGrid;
  return buffer;
}
