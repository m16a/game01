#include "Trooper.h"

#define _USE_MATH_DEFINES
#include <algorithm>
#include <cmath>

using namespace model;
using namespace std;

Trooper::Trooper()
              : Unit(-1, -1, -1), playerId(-1),
              teammateIndex(-1), teammate(false), type(UNKNOWN_TROOPER), stance(UNKNOWN_STANCE),
              hitpoints(-1), maximalHitpoints(-1),
              actionPoints(-1), initialActionPoints(-1),
              visionRange(0.0), shootingRange(0.0), shootCost(-1),
              standingDamage(-1), kneelingDamage(-1), proneDamage(-1),
              damage(-1), holdingGrenade(false),
              holdingMedikit(false), holdingFieldRation(false) { }

Trooper::Trooper(long long id, int x, int y, long long playerId,
              int teammateIndex, bool teammate, TrooperType type, TrooperStance stance,
              int hitpoints, int maximalHitpoints, int actionPoints, int initialActionPoints,
              double visionRange, double shootingRange, int shootCost,
              int standingDamage, int kneelingDamage, int proneDamage, int damage,
              bool holdingGrenade, bool holdingMedikit, bool holdingFieldRation)
              : Unit(id, x, y), playerId(playerId),
              teammateIndex(teammateIndex), teammate(teammate), type(type), stance(stance),
              hitpoints(hitpoints), maximalHitpoints(maximalHitpoints),
              actionPoints(actionPoints), initialActionPoints(initialActionPoints),
              visionRange(visionRange), shootingRange(shootingRange), shootCost(shootCost),
              standingDamage(standingDamage), kneelingDamage(kneelingDamage), proneDamage(proneDamage),
              damage(damage), holdingGrenade(holdingGrenade),
              holdingMedikit(holdingMedikit), holdingFieldRation(holdingFieldRation) { }

long long Trooper::getPlayerId() const {
    return playerId;
}

int Trooper::getTeammateIndex() const {
    return teammateIndex;
}

bool Trooper::isTeammate() const {
    return teammate;
}

TrooperType Trooper::getType() const {
    return type;
}

TrooperStance Trooper::getStance() const {
    return stance;
}

int Trooper::getHitpoints() const {
    return hitpoints;
}

int Trooper::getMaximalHitpoints() const {
    return maximalHitpoints;
}

int Trooper::getActionPoints() const {
    return actionPoints;
}

int Trooper::getInitialActionPoints() const {
    return initialActionPoints;
}

double Trooper::getVisionRange() const {
    return visionRange;
}

double Trooper::getShootingRange() const {
    return shootingRange;
}

int Trooper::getShootCost() const {
    return shootCost;
}

int Trooper::getStandingDamage() const {
    return standingDamage;
}

int Trooper::getKneelingDamage() const {
    return kneelingDamage;
}

int Trooper::getProneDamage() const {
    return proneDamage;
}

int Trooper::getDamage(TrooperStance stance) const {
    switch (stance) {
        case PRONE:
            return proneDamage;
        case KNEELING:
            return kneelingDamage;
        case STANDING:
            return standingDamage;
        default:
            exit(10030);
    }
}

int Trooper::getDamage() const {
    return damage;
}

bool Trooper::isHoldingGrenade() const {
    return holdingGrenade;
}

bool Trooper::isHoldingMedikit() const {
    return holdingMedikit;
}

bool Trooper::isHoldingFieldRation() const {
    return holdingFieldRation;
}
