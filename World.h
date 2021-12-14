// Copyright 2021 James Pretorius
#ifndef WORLD_H_
#define WORLD_H_
#include <cstdlib>

class World {
 public:
    World() {}

    virtual void PrintGrid() = 0;
    virtual void UpdateGrid() = 0;

 protected:
    int day;
    char grid[10][10];

    virtual void initGrid() = 0;
};

#endif  // WORLD_H_
