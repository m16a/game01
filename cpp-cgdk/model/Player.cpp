#include "Player.h"

using namespace model;
using namespace std;

Player::Player(long long id, string name, int score, bool strategyCrashed, int approximateX, int approximateY)
: id(id), name(name), score(score), strategyCrashed(strategyCrashed),
approximateX(approximateX), approximateY(approximateY) { }

long long Player::getId() const {
    return id;
}

string Player::getName() const {
    return name;
}

int Player::getScore() const {
    return score;
}

bool Player::isStrategyCrashed() const {
    return strategyCrashed;
}

int Player::getApproximateX() const {
    return approximateX;
}

int Player::getApproximateY() const {
    return approximateY;
}
