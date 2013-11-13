#pragma once

#ifndef _GAME_H_
#define _GAME_H_

namespace model {
    class Game {
    private:
        int moveCount;
        int lastPlayerEliminationScore;
        int playerEliminationScore;
        int trooperEliminationScore;
        double trooperDamageScoreFactor;
        int stanceChangeCost;
        int standingMoveCost;
        int kneelingMoveCost;
        int proneMoveCost;
        int commanderAuraBonusActionPoints;
        double commanderAuraRange;
        int commanderRequestEnemyDispositionCost;
        int commanderRequestEnemyDispositionMaxOffset;
        int fieldMedicHealCost;
        int fieldMedicHealBonusHitpoints;
        int fieldMedicHealSelfBonusHitpoints;
        double sniperStandingStealthBonus;
        double sniperKneelingStealthBonus;
        double sniperProneStealthBonus;
        double sniperStandingShootingRangeBonus;
        double sniperKneelingShootingRangeBonus;
        double sniperProneShootingRangeBonus;
        double scoutStealthBonusNegation;
        int grenadeThrowCost;
        double grenadeThrowRange;
        int grenadeDirectDamage;
        int grenadeCollateralDamage;
        int medikitUseCost;
        int medikitBonusHitpoints;
        int medikitHealSelfBonusHitpoints;
        int fieldRationEatCost;
        int fieldRationBonusActionPoints;
    public:
        Game(int moveCount,
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
            int fieldRationEatCost, int fieldRationBonusActionPoints);

        int getMoveCount() const;
        int getLastPlayerEliminationScore() const;
        int getPlayerEliminationScore() const;
        int getTrooperEliminationScore() const;
        double getTrooperDamageScoreFactor() const;
        int getStanceChangeCost() const;
        int getStandingMoveCost() const;
        int getKneelingMoveCost() const;
        int getProneMoveCost() const;
        int getCommanderAuraBonusActionPoints() const;
        double getCommanderAuraRange() const;
        int getCommanderRequestEnemyDispositionCost() const;
        int getCommanderRequestEnemyDispositionMaxOffset() const;
        int getFieldMedicHealCost() const;
        int getFieldMedicHealBonusHitpoints() const;
        int getFieldMedicHealSelfBonusHitpoints() const;
        double getSniperStandingStealthBonus() const;
        double getSniperKneelingStealthBonus() const;
        double getSniperProneStealthBonus() const;
        double getSniperStandingShootingRangeBonus() const;
        double getSniperKneelingShootingRangeBonus() const;
        double getSniperProneShootingRangeBonus() const;
        double getScoutStealthBonusNegation() const;
        int getGrenadeThrowCost() const;
        double getGrenadeThrowRange() const;
        int getGrenadeDirectDamage() const;
        int getGrenadeCollateralDamage() const;
        int getMedikitUseCost() const;
        int getMedikitBonusHitpoints() const;
        int getMedikitHealSelfBonusHitpoints() const;
        int getFieldRationEatCost() const;
        int getFieldRationBonusActionPoints() const;
    };
}

#endif
