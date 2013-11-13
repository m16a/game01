#include "Move.h"

using namespace model;

Move::Move() : action(END_TURN), direction(UNKNOWN_DIRECTION), x(-1), y(-1) {
}

ActionType Move::getAction() const {
    return action;
}

Direction Move::getDirection() const {
    return direction;
}

int Move::getX() const {
    return x;
}

int Move::getY() const {
    return y;
}

void Move::setAction(ActionType action) {
    this->action = action;
}

void Move::setDirection(Direction direction) {
    this->direction = direction;
}

void Move::setX(int x) {
    this->x = x;
}

void Move::setY(int y) {
    this->y = y;
}
