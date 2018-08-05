#include "Cell.h"

void Cell::toggle(){
  status = !status;
  for(unsigned i = 0; i < 4; i++)
    tile[i].color = sf::Color(200 * status + 30, 190 * status + 30, 180 * status + 30);
}
