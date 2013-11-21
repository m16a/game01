#pragma once

#include <list>
#include "Strategy.h"
class Vector2d;

class PathFinder
{
public:
	PathFinder(void){};
	virtual ~PathFinder(void){};

	std::list<Vector2d> calcOptimalPath(const model::World& world, const Vector2d& start, const Vector2d& finish, bool ignorePlayers = false);
	bool test();
	static bool isTropperInCell(const model::World& w, const Vector2d& v);

};

std::list<Vector2d> grabNeighbors(const model::World& w, const Vector2d& v, bool ignoreTroopers = false);