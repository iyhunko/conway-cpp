#include "world.h"
#include <algorithm>
#include <iomanip>
#include <ranges>

using namespace conway;
using std::make_unique;
using std::unordered_map;
using std::ranges::views::iota;

World::World(const int32_t size, const list<Coord> &aliveCells) : size(size),
                                                                  cells(make_unique<unordered_map<Coord, Cell>>()) {
    for (int32_t a : iota(0, size)) {
        for (int32_t b : iota(0, size)) {
            Coord coord = {a, b};
            if (std::find(aliveCells.begin(), aliveCells.end(), coord) != aliveCells.end()) {
                cells->insert(std::make_pair(coord, Cell::Alive));
            } else {
                cells->insert(std::make_pair(coord, Cell::Dead));
            }
        }
    }
}

std::unique_ptr<World> World::evolve() const {
    list<Coord> alive;
    for (auto const &[coord, cell] : *cells) {
        int32_t count = 0;

        for (int32_t a : {-1, 0, 1}) {
            for (int32_t b : {-1, 0, 1}) {
                const Coord currentCoord = {coord.x + a, coord.y + b};
                if (currentCoord != coord &&
                    cells->find(currentCoord) != cells->end() && // https://stackoverflow.com/a/3886599/133764
                    cells->at(currentCoord) == Cell::Alive) {
                    count += 1;
                }
            }
        }

        switch (cell) {
            case Cell::Alive:
                if (count == 2 || count == 3) {
                    alive.push_back(coord);
                }
                break;

            case Cell::Dead:
                if (count == 3) {
                    alive.push_back(coord);
                }
                break;
        }
    }
    return make_unique<World>(size, alive);
}

void World::dump(ostream &os) const {
    os << "\n";

    for (int32_t a : iota(0, size)) {
        if (a == 0) {
            // First line with coordinates
            os << "    ";
            for (int32_t b : iota(0, size)) {
                os << std::setw(3) << b << "|";
            }
            os << "\n";
        }
        os << std::setw(3) << a << "|";
        for (int32_t b : iota(0, size)) {
            os << cells->at({b, a});
        }
        os << "\n";
    }
}

bool World::equals(const World &rhs) const {
    return this->size == rhs.size && std::equal(this->cells->begin(), this->cells->end(), rhs.cells->begin());
}

list<Coord> World::blinker(const Coord &coord) {
    return {
        {coord.x, coord.y},
        {coord.x + 1, coord.y},
        {coord.x + 2, coord.y}
    };
}

list<Coord> World::beacon(const Coord &coord) {
    return {
        {coord.x, coord.y},
        {coord.x + 1, coord.y},
        {coord.x, coord.y + 1},
        {coord.x + 1, coord.y + 1},
        {coord.x + 2, coord.y + 2},
        {coord.x + 3, coord.y + 2},
        {coord.x + 2, coord.y + 3},
        {coord.x + 3, coord.y + 3}
    };
}

list<Coord> World::glider(const Coord &coord) {
    return {
        {coord.x + 2, coord.y + 2},
        {coord.x + 1, coord.y + 2},
        {coord.x, coord.y + 2},
        {coord.x + 2, coord.y + 1},
        {coord.x + 1, coord.y},
    };
}

list<Coord> World::block(const Coord &coord) {
    return {
        {coord.x, coord.y},
        {coord.x + 1, coord.y},
        {coord.x, coord.y + 1},
        {coord.x + 1, coord.y + 1}
    };
}

list<Coord> World::tub(const Coord &coord) {
    return {
        {coord.x + 1, coord.y},
        {coord.x, coord.y + 1},
        {coord.x + 2, coord.y + 1},
        {coord.x + 1, coord.y + 2}
    };
}
