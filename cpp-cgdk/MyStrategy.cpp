#include "MyStrategy.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>

#include "PathFinder.h"
#include "GeomMisc.h"

using namespace model;
using namespace std;

MyStrategy::MyStrategy() { }

std::list<Vector2d> gQueue;

void calc(const World& world, const Vector2d& src, const Vector2d& dst){
	PathFinder pf;
	gQueue = pf.calcOptimalPath(world, src, dst);
	gQueue.pop_front();
}

void MyStrategy::move(const Trooper& self, const World& world, const Game& game, Move& move) {
    if (self.getActionPoints() < game.getStandingMoveCost()) {
		gQueue.clear();
        return;
    }

	
	Vector2d dst(1, 1);
	Vector2d src(self.getX(), self.getY());

	//std::list<Vector2d> queue = pf.calcOptimalPath(world, src, dst);
	
	if (gQueue.empty())
		calc(world, src, dst);

	move.setAction(MOVE);
	move.setX(gQueue.begin()->x());
	move.setY(gQueue.begin()->y());
	gQueue.pop_front();

	if (self.getActionPoints() == 2)
		gQueue.clear();
}
