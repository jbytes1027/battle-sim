// Copyright 2021 James Pretorius
#include "./Unit.h"

#include "./Sim.h"

int distanceBetween(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

Unit::Unit(char symbol, Sim* sim, int x, int y, int attackRange) {
    this->symbol = symbol;
    this->sim = sim;
    this->x = x;
    this->y = y;
    this->attackRange = attackRange;
}

void Unit::takeTurn() {
    if (!isAlive) return;

    Unit* enemy = closestEnemy();
    if (closestEnemy() == nullptr) return;

    if (distanceTo(enemy) <= attackRange)
        attack(enemy);
    else
        *this >> enemy;
}

Unit* Unit::operator++() {
    takeTurn();
    return this;
}

Unit* Unit::operator>>(const Unit* unitTo) {
    moveTowards(unitTo->x, unitTo->y);
    return this;
}

void Unit::moveTo(int x, int y) {
    printf("[move] %c (%i, %i) -> (%i, %i)\n", symbol, this->x, this->y, x, y);

    this->x = x;
    this->y = y;
}

void Unit::moveTowards(int x, int y) {
    int newX = this->x;
    int newY = this->y;

    if (this->x < x)
        newX++;
    else if (this->x > x)
        newX--;
    else if (this->y < y)
        newY++;
    else if (this->y > y)
        newY--;

    if (sim->isEmpty(newX, newY)) moveTo(newX, newY);
}

vector<Unit*> Unit::getEnemies() {
    if (isUpperCase())
        return sim->getLowerCaseUnits();
    else
        return sim->getUpperCaseUnits();
}

vector<Unit*> Unit::getAllies() {
    if (!isUpperCase())
        return sim->getLowerCaseUnits();
    else
        return sim->getUpperCaseUnits();
}

Unit* Unit::closestEnemy() {
    Unit* closestEnemy = nullptr;

    for (auto enemy : getEnemies()) {
        if (!enemy->isDead() &&
            (closestEnemy == nullptr ||
             distanceTo(enemy) < distanceTo(closestEnemy))) {
            closestEnemy = enemy;
        }
    }

    return closestEnemy;
}

void Unit::attack(Unit* enemy) {
    int attackSuccessProbability =
        (1 - enemy->getDefense(this)) * getAttack() * 100;

    const char* outcome = "missed";
    if (sim->random() % 100 <= attackSuccessProbability) {
        outcome = "landed";
        enemy->takeHit();
    }
    printf(
        "[attack] %c (%i, %i) -> %c (%i, %i) with %i%% success probability "
        "%s\n",
        symbol, this->x, this->y, enemy->getSymbol(), enemy->x, enemy->y,
        attackSuccessProbability, outcome);
}

void Unit::takeHit() { isAlive = false; }

float Unit::getAttack() { return 1.0; }

bool Unit::isEnemy(Unit* unit) {
    if (unit->getSymbol() == sim->NONE_SYMBOL) return false;

    return isUpperCase() != unit->isUpperCase();
}

bool Unit::isUpperCase() {
    return static_cast<char>(toupper(symbol)) == symbol;
}

bool Unit::isDead() { return !isAlive; }

char Unit::getSymbol() const { return symbol; }

int Unit::getX() const { return x; }

int Unit::getY() const { return y; }

int Unit::distanceTo(const Unit* unit) const {
    return distanceBetween(this->x, this->y, unit->x, unit->y);
}
