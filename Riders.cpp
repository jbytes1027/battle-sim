// Copyright 2021 James Pretorius
#include "./Riders.h"

Riders::Riders(char symbol, Sim* sim, int x, int y)
    : Unit(symbol, sim, x, y, attackRange) {
    this->symbol = symbol;
    this->sim = sim;
    this->x = x;
    this->y = y;
}

float Riders::getDefense(const Unit*) { return 0.2; }
