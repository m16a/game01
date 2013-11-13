#include "Game.h"

using namespace model;

Game::Game(int moveCount,
           int lastPlayerEliminationScore, int playerEliminationScore,
           int trooperEliminationScore, double trooperDamageScoreFactor,
           int stanceChangeCost, int standingMoveCost, int kneelingMoveCost, int proneMoveCost,
           int commanderAuraBonusActionPoints, double commanderAuraRange,
           int commanderRequestEnemyDispositionCost, int commanderRequestEnemyDispositionMaxOffset,
           int fieldMedicHealCost, int fieldMedicHealBonusHitpoints, int fieldMedicHealSelfBonusHitpoints,
           double sniperStandingStealthBonus, double sniperKneelingStealthBonus, double sniperProneStealthBonus,
           double sniperStandingShootingRangeBonus, double sniperKneelingShootingRangeBonus,
           double sniperProneShootingRangeBonus, double scoutStealthBonusNegation,
           int grenadeThrowCost, double grenadeThrowRange, int grenadeDirectDamage, int grenadeCollateralDamage,
           int medikitUseCost, int medikitBonusHitpoints, int medikitHealSelfBonusHitpoints,
           int fieldRationEatCost, int fieldRationBonusActionPoints)
           : moveCount(moveCount),
           lastPlayerEliminationScore(lastPlayerEliminationScore),
           playerEliminationScore(playerEliminationScore),
           trooperEliminationScore(trooperEliminationScore), trooperDamageScoreFactor(trooperDamageScoreFactor),
           stanceChangeCost(stanceChangeCost), standingMoveCost(standingMoveCost),
           kneelingMoveCost(kneelingMoveCost), proneMoveCost(proneMoveCost),
           commanderAuraBonusActionPoints(commanderAuraBonusActionPoints),
           commanderAuraRange(commanderAuraRange),
           commanderRequestEnemyDispositionCost(commanderRequestEnemyDispositionCost),
           commanderRequestEnemyDispositionMaxOffset(commanderRequestEnemyDispositionMaxOffset),
           fieldMedicHealCost(fieldMedicHealCost),
           fieldMedicHealBonusHitpoints(fieldMedicHealBonusHitpoints),
           fieldMedicHealSelfBonusHitpoints(fieldMedicHealSelfBonusHitpoints),
           sniperStandingStealthBonus(sniperStandingStealthBonus),
           sniperKneelingStealthBonus(sniperKneelingStealthBonus),
           sniperProneStealthBonus(sniperProneStealthBonus),
           sniperStandingShootingRangeBonus(sniperStandingShootingRangeBonus),
           sniperKneelingShootingRangeBonus(sniperKneelingShootingRangeBonus),
           sniperProneShootingRangeBonus(sniperProneShootingRangeBonus),
           scoutStealthBonusNegation(scoutStealthBonusNegation),
           grenadeThrowCost(grenadeThrowCost), grenadeThrowRange(grenadeThrowRange),
           grenadeDirectDamage(grenadeDirectDamage), grenadeCollateralDamage(grenadeCollateralDamage),
           medikitUseCost(medikitUseCost), medikitBonusHitpoints(medikitBonusHitpoints),
           medikitHealSelfBonusHitpoints(medikitHealSelfBonusHitpoints),
           fieldRationEatCost(fieldRationEatCost),
           fieldRationBonusActionPoints(fieldRationBonusActionPoints) { }

int Game::getMoveCount() const {
    return moveCount;
}

int Game::getLastPlayerEliminationScore() const {
    return lastPlayerEliminationScore;
}

int Game::getPlayerEliminationScore() const {
    return playerEliminationScore;
}

int Game::getTrooperEliminationScore() const {
    return trooperEliminationScore;
}

double Game::getTrooperDamageScoreFactor() const {
    return trooperDamageScoreFactor;
}

int Game::getStanceChangeCost() const {
    return stanceChangeCost;
}

int Game::getStandingMoveCost() const {
    return standingMoveCost;
}

int Game::getKneelingMoveCost() const {
    return kneelingMoveCost;
}

int Game::getProneMoveCost() const {
    return proneMoveCost;
}

int Game::getCommanderAuraBonusActionPoints() const {
    return commanderAuraBonusActionPoints;
}

double Game::getCommanderAuraRange() const {
    return commanderAuraRange;
}

int Game::getCommanderRequestEnemyDispositionCost() const {
    return commanderRequestEnemyDispositionCost;
}

int Game::getCommanderRequestEnemyDispositionMaxOffset() const {
    return commanderRequestEnemyDispositionMaxOffset;
}

int Game::getFieldMedicHealCost() const {
    return fieldMedicHealCost;
}

int Game::getFieldMedicHealBonusHitpoints() const {
    return fieldMedicHealBonusHitpoints;
}

int Game::getFieldMedicHealSelfBonusHitpoints() const {
    return fieldMedicHealSelfBonusHitpoints;
}

double Game::getSniperStandingStealthBonus() const {
    return sniperStandingStealthBonus;
}

double Game::getSniperKneelingStealthBonus() const {
    return sniperKneelingStealthBonus;
}

double Game::getSniperProneStealthBonus() const {
    return sniperProneStealthBonus;
}

double Game::getSniperStandingShootingRangeBonus() const {
    return sniperStandingShootingRangeBonus;
}

double Game::getSniperKneelingShootingRangeBonus() const {
    return sniperKneelingShootingRangeBonus;
}

double Game::getSniperProneShootingRangeBonus() const {
    return sniperProneShootingRangeBonus;
}

double Game::getScoutStealthBonusNegation() const {
    return scoutStealthBonusNegation;
}

int Game::getGrenadeThrowCost() const {
    return grenadeThrowCost;
}

double Game::getGrenadeThrowRange() const {
    return grenadeThrowRange;
}

int Game::getGrenadeDirectDamage() const {
    return grenadeDirectDamage;
}

int Game::getGrenadeCollateralDamage() const {
    return grenadeCollateralDamage;
}

int Game::getMedikitUseCost() const {
    return medikitUseCost;
}

int Game::getMedikitBonusHitpoints() const {
    return medikitBonusHitpoints;
}

int Game::getMedikitHealSelfBonusHitpoints() const {
    return medikitHealSelfBonusHitpoints;
}

int Game::getFieldRationEatCost() const {
    return fieldRationEatCost;
}

int Game::getFieldRationBonusActionPoints() const {
    return fieldRationBonusActionPoints;
}
