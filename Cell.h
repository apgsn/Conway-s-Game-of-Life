#ifndef __CELL_H_INCLUDED__
#define __CELL_H_INCLUDED__

#include <vector>
#include <SFML/Graphics.hpp>

class Cell{
public:
  sf::VertexArray getTile() { return tile; }
private:
  bool status;
  unsigned neighbors;
  sf::VertexArray tile = sf::VertexArray(sf::Quads, 4);
  void toggle();

  friend class ConwaysField;
};

#endif
