#include "Unit.h"

#define _USE_MATH_DEFINES
#include <cmath>

using namespace model;

Unit::Unit(long long id, int x, int y)
: id(id), x(x), y(y) { }

Unit::~Unit() { }

long long Unit::getId() const {
    return id;
}

int Unit::getX() const {
    return x;
}

int Unit::getY() const {
    return y;
}

double Unit::getDistanceTo(int x, int y) const {
    int xRange = x - this->x;
    int yRange = y - this->y;
    return sqrt((double) (xRange * xRange + yRange * yRange));
}

double Unit::getDistanceTo(const Unit& unit) const {
    return this->getDistanceTo(unit.x, unit.y);
}
