#include "PlayerContext.h"

using namespace model;

PlayerContext::PlayerContext(Trooper trooper, World world)
: trooper(trooper), world(world) { }

const Trooper& PlayerContext::getTrooper() const {
    return trooper;
}

const World& PlayerContext::getWorld() const {
    return world;
}
