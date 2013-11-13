#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>

namespace model {
    class Player {
    private:
        long long id;
        std::string name;
        int score;
        bool strategyCrashed;
        int approximateX;
        int approximateY;
    public:
        Player(long long id, std::string name, int score, bool strategyCrashed, int approximateX, int approximateY);

        long long getId() const;
        std::string getName() const;
        int getScore() const;
        bool isStrategyCrashed() const;
        int getApproximateX() const;
        int getApproximateY() const;
    };
}

#endif
