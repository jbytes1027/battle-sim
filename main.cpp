// Copyright 2021 James Pretorius
#include <iostream>

#include "./Sim.h"

int main() {
    Sim sim = Sim();

    while (!sim.isOver()) {
        sim.PrintGrid();

        char input;
        std::cout << "\n[choose] next or stop (n/s): ";
        std::cin >> input;

        if (input == 'n') {
            sim.forward();
            std::cout << '\n';
        } else {
            return 0;
        }
    }

    std::cout << '\n';
    sim.PrintGrid();
}
