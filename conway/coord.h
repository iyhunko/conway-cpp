#ifndef CONWAY_COORD_H
#define CONWAY_COORD_H

#include <iostream>

namespace conway {
    struct Coord {
        int32_t x{0};
        int32_t y{0};

        Coord(int32_t, int32_t);

        Coord(const Coord &);

        void dump(std::ostream &os) const;

        Coord &operator=(const Coord &rhs) {
            if (this != &rhs) {
                x = rhs.x;
                y = rhs.y;
            }
            return *this;
        };

        // Courtesy of
        // https://stackoverflow.com/a/7204314/133764
        bool operator==(const Coord &rhs) const {
            return x == rhs.x && y == rhs.y;
        }

        bool operator!=(const Coord &rhs) const {
            return x != rhs.x || y != rhs.y;
        }

        bool operator<(const Coord &rhs) const {
            return x < rhs.x || (x == rhs.x && y < rhs.y);
        }

        friend std::ostream &operator<<(std::ostream &os, const Coord &c) {
            c.dump(os);
            return os;
        }
    };
} // namespace conway

// Hash function for Coord instances, to be used in a std::unordered_map
template <>
struct std::hash<conway::Coord> {
    size_t operator()(const conway::Coord &c) const {
        return std::hash<int32_t>()(c.x) ^ std::hash<int32_t>()(c.y);
    }
};

#endif /* CONWAY_COORD_H */
