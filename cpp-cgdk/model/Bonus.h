#pragma once

#ifndef _BONUS_H_
#define _BONUS_H_

#include "Unit.h"

namespace model {
    enum BonusType {
        UNKNOWN_BONUS = -1,
        GRENADE = 0,
        MEDIKIT = 1,
        FIELD_RATION = 2
    };

    class Bonus : public Unit {
    private:
        BonusType type;
    public:
        Bonus();
        Bonus(long long id, int x, int y, BonusType type);

        BonusType getType() const;
    };
}

#endif
