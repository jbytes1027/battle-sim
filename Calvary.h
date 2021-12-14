// Copyright 2021 James Pretorius
#ifndef CALVARY_H_
#define CALVARY_H_

#include "./Unit.h"

class Calvary : public Unit {
 protected:
    static const int attackRange = 1;
    float getDefense(const Unit*);

 public:
    explicit Calvary(char, Sim*, int x, int y);
    void takeTurn();
    void takeHit();
};
#endif  // CALVARY_H_
