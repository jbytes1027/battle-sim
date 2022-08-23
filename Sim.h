// Copyright 2021 James Pretorius
#ifndef SIM_H_
#define SIM_H_

#include <random>
#include <vector>
using std::vector;

#include "./Unit.h"
#include "./World.h"
class Unit;

class Sim : public World {
 private:
    int maxUnits = 15;
    int minUnits = 10;
    std::mt19937 randGen;
    vector<Unit*> lowerCaseUnits;
    vector<Unit*> upperCaseUnits;
    bool isComplete = false;

    void UpdateGrid();
    void initGrid();

 public:
    static const int SIZE = 10;
    static const char ARCHERS_LETTER = 'a';
    static const char INFANTRY_LETTER = 'i';
    static const char CALVARY_LETTER = 'c';
    static const char RIDER_LETTER = 'r';
    static const char NONE_SYMBOL = '.';

    explicit Sim(int seed = std::random_device{}());
    ~Sim();
    bool isOver();
    bool isEmpty(int x, int y);
    void PrintGrid();
    void forward();
    void add(Unit*);
    const vector<Unit*> getLowerCaseUnits();
    const vector<Unit*> getUpperCaseUnits();
    int random();
};
#endif  // SIM_H_
