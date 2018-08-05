#ifndef __CONWAYSFIELD_H_INCLUDED__
#define __CONWAYSFIELD_H_INCLUDED__

#include "Cell.h"

class ConwaysField{
public:
  ConwaysField(unsigned width, unsigned height, unsigned size);
  void setField(bool empty);
  void setGridLine(unsigned i, bool dir);
  bool isAlive(unsigned i, unsigned j) { return grid[i][j].status; }
  Cell switchCellStatus(unsigned i, unsigned j);
  std::vector<Cell> updateFieldStatus();
  std::vector<std::vector<Cell> >& getGrid() { return grid; }
  std::vector<std::vector<sf::VertexArray> >& getGridLines() { return gridLines; }
private:
  unsigned width, height, size;
  std::vector<std::vector<Cell> > grid;
  std::vector<std::vector<sf::VertexArray> > gridLines;
};

#endif
