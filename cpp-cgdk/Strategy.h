#pragma once

#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include "model/Game.h"
#include "model/Move.h"
#include "model/Trooper.h"
#include "model/World.h"

class Strategy {
public:
    virtual ~Strategy();
    virtual void move(const model::Trooper& self, const model::World& world, const model::Game& game, model::Move& move) = 0;
};

#endif
