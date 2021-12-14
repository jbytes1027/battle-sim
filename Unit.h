// Copyright 2021 James Pretorius
#ifndef UNIT_H_
#define UNIT_H_

class Sim;
#include <vector>

#include "./Sim.h"
using std::vector;

class Unit {
 protected:
    int attackRange;
    Sim* sim;
    char symbol;

    void moveTo(int x, int y);
    void moveTowards(int x, int y);
    void attack(Unit* enemy);
    vector<Unit*> getEnemies();
    vector<Unit*> getAllies();
    Unit* closestEnemy();
    float getAttack();
    int distanceTo(const Unit*) const;
    int x, y;
    bool isAlive = true;

 public:
    Unit(char, Sim*, int x, int y, int attackRange);
    virtual void takeTurn();
    virtual void takeHit();
    Unit* operator++();
    Unit* operator>>(const Unit*);
    bool isEnemy(Unit*);
    bool isUpperCase();
    bool isDead();
    virtual float getDefense(const Unit* attacker) = 0;
    char getSymbol() const;
    int getX() const;
    int getY() const;
};
#endif  // UNIT_H_
