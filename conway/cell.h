#ifndef CONWAY_CELL_H
#define CONWAY_CELL_H

#include <iostream>

using std::ostream;

namespace conway {
    enum class Cell {
        Alive,
        Dead
    };

    void dumpCell(ostream &os, const Cell &cell);

    inline ostream &operator<<(ostream &os, const Cell &cell) {
        dumpCell(os, cell);
        return os;
    }
} // namespace conway

#endif /* CONWAY_CELL_H */
