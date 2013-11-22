#include "MyStrategy.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include<time.h>

#include "PathFinder.h"
#include "GeomMisc.h"
#include "ActionQueue.h"

using namespace model;
using namespace std;

ActionQueue gActionQueue;

MyStrategy::MyStrategy() { }

const int kMAX_TIME = 30; //0.200 * 50 * 3

float gAllTime = 0;
float gMaxStep = 0;

void MyStrategy::move(const Trooper& self, const World& world, const Game& game, Move& move) {
	if (self.getActionPoints() < game.getStandingMoveCost()) {
		return;
	}
//#ifdef _DEBUG  
	clock_t startTime = clock();
//#endif

	static bool once = false;

	if (!once){
		srand(time(NULL));
		once = true;
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
//#ifdef _DEBUG  
	clock_t endTime = clock();	
	float diff = (endTime - startTime) / float(CLOCKS_PER_SEC);
	gAllTime += diff;

	if (diff > gMaxStep)
		gMaxStep = diff;
	printf("%f\t%f\t%f\n ", gAllTime, diff, gMaxStep);
//#endif
}