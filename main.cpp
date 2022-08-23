// Copyright 2021 James Pretorius
#include <chrono>
#include <iostream>
#include <thread>

#include "./Sim.h"

void clearScreen() { std::cout << "\033[2J\033[1;1H"; }

int main(int argc, char **argv) {
    clearScreen();
    Sim sim = Sim();

    bool isAutoMode = argc == 2;

    while (!sim.isOver()) {
        clearScreen();
        sim.PrintGrid();
        sim.forward();

        if (isAutoMode) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        } else {
            char input;
            std::cout << "\n[choose] next or stop (n/s): ";
            std::cin >> input;

            if (input == 'n') {
                std::cout << '\n';
            } else {
                return 0;
            }
        }
    }
}
