#include "Bonus.h"

using namespace model;

Bonus::Bonus()
: Unit(-1, -1, -1), type(UNKNOWN_BONUS) { }

Bonus::Bonus(long long id, int x, int y, BonusType type)
: Unit(id, x, y), type(type) { }

BonusType Bonus::getType() const {
    return type;
}
