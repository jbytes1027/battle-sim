// Copyright 2021 James Pretorius
#ifndef RIDERS_H_
#define RIDERS_H_

#include "./Unit.h"

class Riders : public Unit {
 protected:
    static const int attackRange = 1;
    float getDefense(const Unit*);

 public:
    Riders(char, Sim*, int x, int y);
};
#endif  // RIDERS_H_
