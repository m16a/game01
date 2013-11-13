#pragma once

#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>

#include "Bonus.h"
#include "Player.h"
#include "Trooper.h"

namespace model {
    enum CellType {
        UNKNOWN_CELL = -1,
        FREE = 0,
        LOW_COVER = 1,
        MEDIUM_COVER = 2,
        HIGH_COVER = 3
    };

    class World {
    private:
        int moveIndex;
        int width;
        int height;
        std::vector<Player> players;
        std::vector<Trooper> troopers;
        std::vector<Bonus> bonuses;
        const std::vector<std::vector<CellType> >& cells;
        const std::vector<bool>& cellVisibilities;
    public:
        World(int moveIndex, int width, int height, std::vector<Player> players,
            std::vector<Trooper> troopers, std::vector<Bonus> bonuses,
            const std::vector<std::vector<CellType> >& cells,
            const std::vector<bool>& cellVisibilities);

        int getMoveIndex() const;
        int getWidth() const;
        int getHeight() const;
        const std::vector<Player>& getPlayers() const;
        const std::vector<Trooper>& getTroopers() const;
        const std::vector<Bonus>& getBonuses() const;
        const std::vector<std::vector<CellType> >& getCells() const;
        bool isVisible(double maxRange,
            int viewerX, int viewerY, TrooperStance viewerStance,
            int objectX, int objectY, TrooperStance objectStance) const;
    };
}

#endif
