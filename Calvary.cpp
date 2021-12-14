// Copyright 2021 James Pretorius
#include "./Calvary.h"

#include "./Riders.h"

Calvary::Calvary(char symbol, Sim* sim, int x, int y)
    : Unit(symbol, sim, x, y, attackRange) {
    this->symbol = symbol;
    this->sim = sim;
    this->x = x;
    this->y = y;
}

void Calvary::takeTurn() {
    if (!isAlive) return;

    Unit* enemy = closestEnemy();
    if (closestEnemy() == nullptr) return;

    *this >> enemy;
    if (distanceTo(enemy) <= attackRange) attack(enemy);
}

float Calvary::getDefense(const Unit* attacker) {
    float defense = 0.8;

    char attackerType = tolower(attacker->getSymbol());

    if (attackerType == sim->ARCHERS_LETTER) defense = 0.95;
    if (attackerType == sim->INFANTRY_LETTER) defense *= 0.9;

    return defense;
}

void Calvary::takeHit() {
    if (this->isUpperCase())
        sim->add(new Riders(static_cast<char>(toupper(sim->RIDER_LETTER)), sim,
                            x, y));
    else
        sim->add(new Riders(sim->RIDER_LETTER, sim, x, y));

    printf("[unit] %c (%i, %i) dismounted\n", symbol, x, y);

    isAlive = false;
}
