# Battle Sim

Battle sim is a chess-like automatic battlefield simulation in **C++** as a class final project to show **OOP concepts** and **C memory management**.

## Gameplay Overview

There are two sides, upper case and lower case, units in the upper case army are distinguishable by being upper case and units in the lower case army are lower case. **To start**, each army is created semi-randomly with each type of unit is lined up in its own row but each row has a semi-random number of units. In every simulation iteration, every unit takes a turn in a random order. There are four types of units Archers, Infantry, Calvery and Riders. A unit's turn consists of moving and attacking. Attacks are probability based and depend on what type of unit is being attacked - the higher a unit's defense is, the less likely the attack is to land. **The sim ends** when all the units on one side have died.

## Example Battle

![](https://github.com/jbytes1027/battle-sim/raw/492c2bce1968c1cacc3d2e1d050029f7da6e8f26/Running%20Example.gif)

## Gameplay rules

1. By default units either move towards or attack the closest enemy every turn - a unit attacks if an enemy is in range to be attacked, otherwise the unit moves towards the closest enemy. (see Unit::takeTurn)
2. All unit movement is limited to 1 space non-diagonally. (see Unit::moveTowards)
3. Calvary units can move then attack in one turn. (see Calvary::takeTurn)
4. Infantry can attack twice in one round. (see Infantry::takeTurn)
5. Infantry take one more turn after they are hit, then they die. (track isHit in Infantry - see Infantry::takeHit and Infantry::takeTurn)
6. If an attack is lands on a Rider or Archer they die. (see Unit::attack)
7. Calvary have increased defense against archers and infantry. (see Calvary::getDefense)
8. Infantry have higher defense against archers and decreased defense against calvary. (see Infantry::getDefense)
9. Infantry have their defense increased when they are next to other infantry. (see Infantry::getDefense)
10. When Calvary are hit they are replaced by a Rider unit in the same position. (see Calvary::takeHit)

## To run

Use the vscode debug config, or compile all the .cpp files together

`g++ *.cpp -g -lgtest -lpthread -o build/main`

and run the result

`./build/main`
