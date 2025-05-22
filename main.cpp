#include "conway/conway.h"
#include <chrono>
#include <csignal>
#include <iostream>
#include <memory>
#include <thread>

using namespace conway;

// Thanks to
// https://stackoverflow.com/a/17766999/133764
// for the handling of CTRL+C

volatile sig_atomic_t flag = 0;

void signal_handler(int) {
    flag = 1;
}

int32_t main(int, char **) {
    signal(SIGINT, signal_handler);

    auto alive = World::blinker({0, 1});
    alive.splice(alive.end(), World::beacon({10, 10}));
    alive.splice(alive.end(), World::glider({4, 5}));
    alive.splice(alive.end(), World::block({1, 10}));
    alive.splice(alive.end(), World::block({18, 3}));
    alive.splice(alive.end(), World::tub({6, 1}));

    auto world = std::make_unique<World>(30, alive);
    int32_t generation = 1;

    while (true) {
        if (flag == 1) break;
        system("clear");
        std::cout << *world << "\n";
        std::cout << "Generation " << generation++ << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        world = world->evolve();
    }
    system("clear");
    return 0;
}
