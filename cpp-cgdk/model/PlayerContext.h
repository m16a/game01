#pragma once

#ifndef _PLAYER_CONTEXT_H_
#define _PLAYER_CONTEXT_H_

#include "Trooper.h"
#include "World.h"

namespace model {
    class PlayerContext {
    private:
        Trooper trooper;
        World world;
    public:
        PlayerContext(Trooper trooper, World world);

        const Trooper& getTrooper() const;
        const World& getWorld() const;
    };
}

#endif
