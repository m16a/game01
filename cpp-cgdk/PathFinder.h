#pragma once

#include <list>
#include "Strategy.h"
class Vector2d;

class PathFinder
{
public:
	PathFinder(void){};
	virtual ~PathFinder(void){};

	std::list<Vector2d> calcOptimalPath(const model::World& world, const Vector2d& start, const Vector2d& finish);
	bool test();

};
