#ifndef CONWAY_WORLD_H
#define CONWAY_WORLD_H

#include "cell.h"
#include "coord.h"
#include <iostream>
#include <unordered_map>
#include <memory>
#include <list>

using std::list;

namespace conway {
    class World {
      private:
        const int32_t size;
        const std::unique_ptr<std::unordered_map<Coord, Cell>> cells;

      public:
        World(int32_t, const list<Coord> &);

        [[nodiscard]] std::unique_ptr<World> evolve() const;

        [[nodiscard]] bool equals(const World &rhs) const;

        void dump(std::ostream &os) const;

        static list<Coord> blinker(const Coord &);

        static list<Coord> beacon(const Coord &);

        static list<Coord> glider(const Coord &);

        static list<Coord> block(const Coord &);

        static list<Coord> tub(const Coord &);

        bool operator==(const World &rhs) const {
            return equals(rhs);
        }

        friend std::ostream &operator<<(std::ostream &os, const World &w) {
            w.dump(os);
            return os;
        }
    };
} // namespace conway

#endif /* CONWAY_WORLD_H */
