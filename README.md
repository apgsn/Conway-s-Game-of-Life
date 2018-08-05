# Conway-s-Game-of-Life

Implementation of classic [Conway's game of life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) on toroidal field.  
Dependency: [SFML](https://github.com/SFML/SFML)

<img src="screen.png">

### Rules
The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, alive or dead, (or populated and unpopulated, respectively).  
At each step, every cell interacts with its neighbours (horizontally, vertically, or diagonally adjacent cells):  
1 - Any live cell with fewer than two live neighbors dies, as if by under population;  
2 - Any live cell with two or three live neighbors lives on to the next generation;  
3 - Any live cell with more than three live neighbors dies, as if by overpopulation;  
4 - Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.  
The initial pattern constitutes the seed. The rules continue to be applied repeatedly to create further generations. 

### Controls  

#### Mouse  
Scroll up/down: change simulation speed, slowing it down enough will stop execution  
Left click: activate selected cell(s)  
Right click: deactivate selected cell(s)  

#### Keyboard  
'E' key: empty field (no active cells)  
'R' key: random field (random live cells)  
'G' key: toggle "God's touch" mode - on each step, a single random cell is selected and its status switched. It allows to create constantly evolving landscapes.

### Code

The architecture of the program is quite simple: we have a small `Cell` class to define the basic structure of the single cell, then a `ConwaysField` class that uses it to manage the graphical aspects of the entire field as well as the spatial interactions between cells, and finally `main.cpp`, which takes care of execution and controls.

The program underwent a series of graphical improvements before its first commit.  
At first the field was composed by a grid of `sf::RectangleShape` items with visible borders and the screen was constantly refreshed by redrawing the whole field from scratch, as a result the animation was quite sluggish. I fixed this by:  
1) using a buffer item to keep track of and redraw only those cells that had their status changed;  
2) using `sf::VertexArray` instead of `sf::RectangleShape` for cells, which boosted the performance quite a bit. That also meant I had to create and draw a dedicated `sf::VertexArray` item for cell borders as well.
