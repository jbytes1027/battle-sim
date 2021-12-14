// Copyright 2021 James Pretorius
#ifndef ARCHERS_H_
#define ARCHERS_H_

#include "./Unit.h"

class Archers : public Unit {
 protected:
    static const int attackRange = 4;
    float getDefense(const Unit*);

 public:
    Archers(char, Sim*, int x, int y);
};
#endif  // ARCHERS_H_
