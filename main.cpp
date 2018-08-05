/* Conway's Game of Life (on toroidal field)
The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells,
each of which is in one of two possible states, alive or dead, (or populated and unpopulated, respectively).
At each step, every cell interacts with its neighbours (horizontally, vertically, or diagonally adjacent cells):
1 - Any live cell with fewer than two live neighbors dies, as if by under population;
2 - Any live cell with two or three live neighbors lives on to the next generation;
3 - Any live cell with more than three live neighbors dies, as if by overpopulation;
4 - Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
The initial pattern constitutes the seed. The rules continue to be applied repeatedly to create further generations.
Bonus! "God's Touch": on every step, the game toggles one random cell's status, it ends up never reaching a stable configuration.
*/

#include <vector>
#include <SFML/Graphics.hpp>
#include "ConwaysField.h"

int main(){
  srand(time(NULL));
  const unsigned WIDTH = 120, HEIGHT = 80, SIZE = 8;
  sf::RenderWindow window(sf::VideoMode(WIDTH * SIZE, HEIGHT * SIZE), "Conway's Game of Life", sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(60);
  sf::Clock clock;
  float elapsedTime, deltaTime = 150;
  bool reset = true, empty = false, godsTouch;
  std::vector<Cell> buffer;
  ConwaysField field(WIDTH, HEIGHT, SIZE);
  while (window.isOpen()){

    if(reset){
      window.clear();
      field.setField(empty);
      reset = empty = godsTouch = false;
      for(auto &i : field.getGrid())
        for(auto &c : i)
          buffer.push_back(c);
    }

    sf::Event event;
  	while(window.pollEvent(event)){
      switch (event.type){
        case sf::Event::MouseWheelScrolled :
          if(event.mouseWheelScroll.delta < 0 && deltaTime < 500) deltaTime += 25;
          if(event.mouseWheelScroll.delta > 0 && deltaTime > 0) deltaTime -= 25;
        break;
        case sf::Event::KeyPressed :
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)) godsTouch = !godsTouch;
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) reset = empty = true;
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) reset = true;
        break;
        case sf::Event::Closed :
					window.close();
				break;
      }
    }

    sf::Vector2i mPos = sf::Mouse::getPosition(window);
    mPos /= (int)SIZE;
    if((mPos.x >= 0 && mPos.y >= 0 && mPos.x < WIDTH && mPos.y < HEIGHT) &&
      ((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !field.isAlive(mPos.x, mPos.y)) ||
      (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && field.isAlive(mPos.x, mPos.y))))
      buffer.push_back(field.switchCellStatus(mPos.x, mPos.y));

    elapsedTime = clock.getElapsedTime().asMilliseconds();
    if(elapsedTime > deltaTime && deltaTime < 500){
      elapsedTime = clock.restart().asMilliseconds();
      if(godsTouch) buffer.push_back(field.switchCellStatus(rand()%WIDTH, rand()%HEIGHT));
      std::vector<Cell> updatedCellsBuffer = field.updateFieldStatus();
      buffer.insert(buffer.end(), updatedCellsBuffer.begin(), updatedCellsBuffer.end());
    }

    if(buffer.size()){
      for(auto &c : buffer)
        window.draw(c.getTile());
      for(auto &i : field.getGridLines())
        for(auto &l : i)
          window.draw(l);
      window.display();
      buffer.clear();
    }
  }
  return 0;
}
