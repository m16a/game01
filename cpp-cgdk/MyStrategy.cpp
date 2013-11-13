#include "MyStrategy.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>

using namespace model;
using namespace std;

MyStrategy::MyStrategy() { }

void MyStrategy::move(const Trooper& self, const World& world, const Game& game, Move& move) {
    if (self.getActionPoints() < game.getStandingMoveCost()) {
        return;
    }

    move.setAction(MOVE);

    if (rand() % 2 == 0) {
        move.setDirection(rand() % 2 == 0 ? NORTH : SOUTH);
    } else {
        move.setDirection(rand() % 2 == 0 ? WEST : EAST);
    }
}
