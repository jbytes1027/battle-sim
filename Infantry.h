// Copyright 2021 James Pretorius
#ifndef INFANTRY_H_
#define INFANTRY_H_

#include "./Unit.h"

class Infantry : public Unit {
 protected:
    static const int attackRange = 1;
    int isHit = false;
    float getDefense(const Unit*);

 public:
    explicit Infantry(char, Sim*, int x, int y);
    void takeTurn();
    void takeHit();
};
#endif  // INFANTRY_H_
