#include "World.h"

#define _USE_MATH_DEFINES
#include <algorithm>
#include <cmath>

using namespace model;
using namespace std;

World::World(int moveIndex, int width, int height, vector<Player> players,
             vector<Trooper> troopers, vector<Bonus> bonuses,
             const vector<vector<CellType> >& cells,
             const vector<bool>& cellVisibilities)
             : moveIndex(moveIndex), width(width), height(height), players(players),
             troopers(troopers), bonuses(bonuses), cells(cells), cellVisibilities(cellVisibilities) { }

int World::getMoveIndex() const {
    return moveIndex;
}

int World::getWidth() const {
    return width;
}

int World::getHeight() const {
    return height;
}

const vector<Player>& World::getPlayers() const {
    return players;
}

const vector<Trooper>& World::getTroopers() const {
    return troopers;
}

const vector<Bonus>& World::getBonuses() const {
    return bonuses;
}

const vector<vector<CellType> >& World::getCells() const {
    return cells;
}

bool World::isVisible(double maxRange,
               int viewerX, int viewerY, TrooperStance viewerStance,
               int objectX, int objectY, TrooperStance objectStance) const {
    int minStanceIndex = min(viewerStance, objectStance);
    int xRange = objectX - viewerX;
    int yRange = objectY - viewerY;
    
    return xRange * xRange + yRange * yRange <= maxRange * maxRange
        && cellVisibilities[
            viewerX * height * width * height * _TROOPER_STANCE_COUNT_
                + viewerY * width * height * _TROOPER_STANCE_COUNT_
                + objectX * height * _TROOPER_STANCE_COUNT_
                + objectY * _TROOPER_STANCE_COUNT_
                + minStanceIndex
        ];
}
