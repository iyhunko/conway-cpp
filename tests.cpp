#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file

#include "conway/conway.h"
#include <catch2/catch_all.hpp>
#include <list>

using namespace conway;

TEST_CASE("Block") {
    auto alive = World::block({0, 0});
    auto original = std::make_unique<World>(5, alive);
    auto next = original->evolve();
    REQUIRE(*next == *original);
}

TEST_CASE("Tub") {
    auto alive = World::tub({0, 0});
    auto original = std::make_unique<World>(5, alive);
    auto next = original->evolve();
    REQUIRE(*next == *original);
}

TEST_CASE("Blinker") {
    auto alive = World::blinker({0, 1});
    auto original = std::make_unique<World>(3, alive);
    auto gen1 = original->evolve();
    std::list<Coord> expectedAlive = {{1, 0}, {1, 1}, {1, 2}};
    auto expected = std::make_unique<World>(3, expectedAlive);
    REQUIRE(*gen1 == *expected);
    auto gen2 = gen1->evolve();
    REQUIRE(*gen2 == *original);
}
