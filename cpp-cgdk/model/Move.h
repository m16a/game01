#pragma once

#ifndef _MOVE_H_
#define _MOVE_H_

namespace model {
    enum ActionType {
        UNKNOWN_ACTION = -1,
        END_TURN = 0,
        MOVE = 1,
        SHOOT = 2,
        RAISE_STANCE = 3,
        LOWER_STANCE = 4,
        THROW_GRENADE = 5,
        USE_MEDIKIT = 6,
        EAT_FIELD_RATION = 7,
        HEAL = 8,
        REQUEST_ENEMY_DISPOSITION = 9
    };

    enum Direction {
        UNKNOWN_DIRECTION = -1,
        CURRENT_POINT = 0,
        NORTH = 1,
        EAST = 2,
        SOUTH = 3,
        WEST = 4
    };

    class Move {
    private:
        ActionType action;
        Direction direction;
        int x;
        int y;
    public:
        Move();
    
        ActionType getAction() const;
        Direction getDirection() const;
        int getX() const;
        int getY() const;

        void setAction(ActionType action);
        void setDirection(Direction direction);
        void setX(int x);
        void setY(int y);
    };
}

#endif
