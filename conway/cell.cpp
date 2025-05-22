#include "cell.h"

using namespace conway;

void conway::dumpCell(ostream &os, const Cell &cell) {
    os << ((cell == Cell::Alive)? " x |" : "   |");
}
