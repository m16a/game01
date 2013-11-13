#pragma once

#ifndef _TROOPER_H_
#define _TROOPER_H_

#include "Unit.h"

namespace model {
    enum TrooperType {
        UNKNOWN_TROOPER = -1,
        COMMANDER = 0,
        FIELD_MEDIC = 1,
        SOLDIER = 2,
        SNIPER = 3,
        SCOUT = 4
    };

    enum TrooperStance {
        UNKNOWN_STANCE = -1,
        PRONE = 0,
        KNEELING = 1,
        STANDING = 2,
        _TROOPER_STANCE_COUNT_ = 3
    };

    class Trooper : public Unit {
    private:
        long long playerId;
        int teammateIndex;
        bool teammate;
        TrooperType type;
        TrooperStance stance;
        int hitpoints;
        int maximalHitpoints;
        int actionPoints;
        int initialActionPoints;
        double visionRange;
        double shootingRange;
        int shootCost;
        int standingDamage;
        int kneelingDamage;
        int proneDamage;
        int damage;
        bool holdingGrenade;
        bool holdingMedikit;
        bool holdingFieldRation;
    public:
        Trooper();
        Trooper(long long id, int x, int y, long long playerId,
            int teammateIndex, bool teammate, TrooperType type, TrooperStance stance,
            int hitpoints, int maximalHitpoints, int actionPoints, int initialActionPoints,
            double visionRange, double shootingRange, int shootCost,
            int standingDamage, int kneelingDamage, int proneDamage, int damage,
            bool holdingGrenade, bool holdingMedikit, bool holdingFieldRation);

        long long getPlayerId() const;
        int getTeammateIndex() const;
        bool isTeammate() const;
        TrooperType getType() const;
        TrooperStance getStance() const;
        int getHitpoints() const;
        int getMaximalHitpoints() const;
        int getActionPoints() const;
        int getInitialActionPoints() const;
        double getVisionRange() const;
        double getShootingRange() const;
        int getShootCost() const;
        int getStandingDamage() const;
        int getKneelingDamage() const;
        int getProneDamage() const;
        int getDamage(TrooperStance stance) const;
        int getDamage() const;
        bool isHoldingGrenade() const;
        bool isHoldingMedikit() const;
        bool isHoldingFieldRation() const;
    };
}

#endif
