#include "MyStrategy.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>

#include "PathFinder.h"
#include "GeomMisc.h"
#include "ActionQueue.h"

using namespace model;
using namespace std;

ActionQueue gActionQueue;

MyStrategy::MyStrategy() { }


void MyStrategy::move(const Trooper& self, const World& world, const Game& game, Move& move) {
	if (self.getActionPoints() < game.getStandingMoveCost()) {
		return;
	}
	gActionQueue.createQueue(world, game, self);

	if (gActionQueue.m_chain && !(gActionQueue.m_chain->chain.empty())){
		ActionChunk chunk = *(gActionQueue.m_chain->chain.begin());

		move.setAction(chunk.action_type);

		if (!(chunk.target == Vector2d(-1, -1))){
			move.setX(chunk.target.x());
			move.setY(chunk.target.y());
		}
	}
}