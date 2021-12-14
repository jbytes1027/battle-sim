// Copyright 2021 James Pretorius
#include "./Infantry.h"

Infantry::Infantry(char symbol, Sim* sim, int x, int y)
    : Unit(symbol, sim, x, y, attackRange) {
    this->symbol = symbol;
    this->sim = sim;
    this->x = x;
    this->y = y;
}

float Infantry::getDefense(const Unit* attacker) {
    float defense = .5;

    // increase defense when next to other infantry
    for (auto ally : getAllies()) {
        if (ally->getSymbol() == symbol && distanceTo(ally) == 1) {
            defense *= 1.2;
        }
    }

    char attackerType = tolower(attacker->getSymbol());

    if (attackerType == sim->ARCHERS_LETTER) defense *= 1.3;
    if (attackerType == sim->CALVARY_LETTER) defense *= 0.7;

    return defense;
}

void Infantry::takeHit() { isHit = true; }

void Infantry::takeTurn() {
    if (!isAlive) return;

    for (int i = 0; i < 2; i++) {
        Unit* enemy = closestEnemy();
        if (closestEnemy() == nullptr) return;
        if (distanceTo(enemy) > attackRange) {
            *this >> enemy;
            break;
        } else if (distanceTo(enemy) <= attackRange) {
            attack(enemy);
            enemy = closestEnemy();
        }
    }

    if (isHit) {
        printf("[unit] %c (%i, %i) fell\n", symbol, x, y);
        isAlive = false;
    }
}
