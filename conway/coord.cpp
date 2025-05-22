#include "coord.h"

using namespace conway;

Coord::Coord(int32_t x, int32_t y) : x{x}, y{y} {}

Coord::Coord(const Coord &rhs) : x{rhs.x}, y{rhs.y} {}

void Coord::dump(std::ostream &os) const {
    os << x << ":" << y;
}
