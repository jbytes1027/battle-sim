// Copyright 2021 James Pretorius
#include "./Sim.h"

#include <iostream>
#include <random>
#include <vector>

using std::vector;

#include "./Archers.h"
#include "./Calvary.h"
#include "./Infantry.h"

Sim::Sim(int seed) {
    randGen.seed(seed);
    day = 0;
    printf("[seed] %i\n\n", seed);

    initGrid();
}

int Sim::random() { return randGen(); }

void Sim::initGrid() {
    lowerCaseUnits.reserve(60);
    upperCaseUnits.reserve(60);
    int numUnits = minUnits + (random() % (maxUnits - minUnits));
    char unitTypes[10] = {ARCHERS_LETTER,
                          INFANTRY_LETTER,
                          CALVARY_LETTER,
                          NONE_SYMBOL,
                          NONE_SYMBOL,
                          NONE_SYMBOL,
                          NONE_SYMBOL,
                          static_cast<char>(toupper(CALVARY_LETTER)),
                          static_cast<char>(toupper(INFANTRY_LETTER)),
                          static_cast<char>(toupper(ARCHERS_LETTER))};
    int unitNums[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = numUnits; i > 0; i--) {
        int unitLC = random() % 3;

        if (unitNums[unitLC] <= 10) unitNums[unitLC]++;

        int unitUC = (random() % 3) + SIZE - 3;

        if (unitNums[unitUC] <= 10) unitNums[unitUC]++;
    }

    for (int x = 0; x < SIZE; x++) {
        int startY = ((SIZE - 1) - unitNums[x]) / 2;
        int endY = (SIZE - 1) - startY;

        for (int y = startY; y <= endY; y++) {
            Unit* unit;

            if (tolower(unitTypes[x]) == NONE_SYMBOL) continue;
            if (tolower(unitTypes[x]) == ARCHERS_LETTER)
                unit = new Archers(unitTypes[x], this, x, y);
            if (tolower(unitTypes[x]) == INFANTRY_LETTER)
                unit = new Infantry(unitTypes[x], this, x, y);
            if (tolower(unitTypes[x]) == CALVARY_LETTER)
                unit = new Calvary(unitTypes[x], this, x, y);

            add(unit);
        }
    }
}

void Sim::PrintGrid() {
    UpdateGrid();

    std::cout << "  0 1 2 3 4 5 6 7 8 9\n";
    for (int y = 0; y < SIZE; y++) {
        std::cout << y << " ";
        for (int x = 0; x < SIZE; x++) {
            std::cout << grid[y][x] << ' ';
        }
        std::cout << "\n";
    }
}

void Sim::UpdateGrid() {
    // reset grid to blank
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            grid[y][x] = NONE_SYMBOL;
        }
    }

    // redraw lower case units
    for (auto unit : lowerCaseUnits) {
        if (!unit->isDead())
            grid[unit->getY()][unit->getX()] = unit->getSymbol();
    }

    // redraw upper case units
    for (auto unit : upperCaseUnits) {
        if (!unit->isDead())
            grid[unit->getY()][unit->getX()] = unit->getSymbol();
    }
}

bool Sim::isOver() {
    bool isLowerCaseUnitsLeft = false;
    for (auto& unit : lowerCaseUnits) {
        if (!unit->isDead()) isLowerCaseUnitsLeft = true;
    }

    bool isUpperCaseUnitsLeft = false;
    for (auto& unit : upperCaseUnits) {
        if (!unit->isDead()) isUpperCaseUnitsLeft = true;
    }

    if (!isLowerCaseUnitsLeft) {
        printf("The Upper Case was victorious!\n");
        return true;
    }

    if (!isUpperCaseUnitsLeft) {
        printf("The Lower Case was victorious!\n");
        return true;
    }

    return false;
}

void Sim::add(Unit* unit) {
    if (unit->isUpperCase())
        upperCaseUnits.push_back(unit);
    else
        lowerCaseUnits.push_back(unit);
}

void Sim::forward() {
    day++;
    printf("\n[turn] %i\n", day);

    vector<Unit*> allUnits;
    allUnits.insert(allUnits.end(), lowerCaseUnits.begin(),
                    lowerCaseUnits.end());
    allUnits.insert(allUnits.end(), upperCaseUnits.begin(),
                    upperCaseUnits.end());

    while (allUnits.size() > 0) {
        int i = random() % allUnits.size();

        ++*allUnits[i];
        allUnits.erase(allUnits.begin() + i);
    }
}

bool Sim::isEmpty(int x, int y) {
    for (auto unit : lowerCaseUnits) {
        if (!unit->isDead() && unit->getX() == x && unit->getY() == y)
            return false;
    }
    for (auto unit : upperCaseUnits) {
        if (!unit->isDead() && unit->getX() == x && unit->getY() == y)
            return false;
    }

    return true;
}

const vector<Unit*> Sim::getLowerCaseUnits() { return lowerCaseUnits; }
const vector<Unit*> Sim::getUpperCaseUnits() { return upperCaseUnits; }

Sim::~Sim() {
    for (auto unit : lowerCaseUnits) delete unit;
    for (auto unit : upperCaseUnits) delete unit;
}
